// SPDX-License-Identifier: GPL-3.0-or-later
#include "always.h"
#ifdef __ANDROID__
#include "android_lan_game.h"
#include "addon.h"
#include "ccfile.h"
#include "conquer.h"
#include "dbgprint.h"
#include "desyncdlg.h"
#include "enviro.h"
#include "globals.h"
#include "goptions.h"
#include "house.h"
#include "houstype.h"
#include "ipxmgr.h"
#include "netshare.h"
#include "nettime.h"
#include "queue.h"
#include "rules.h"
#include "savemgr.h"
#include "scenario.h"
#include "session.h"
#include "sha.h"
#include "_rand.h"
#include <chrono>

namespace {
constexpr unsigned short GAME_PORT = 49153;
std::unique_ptr<AndroidLanProbe> ActiveLobby;
std::string NetworkError;
bool TransportOpen = false, TransportSeen = false;
uint64_t LastTransportSend = 0;

uint64_t Milliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

IPXAddressClass Game_Address(AndroidLanProbe const & lobby)
{
	return IPXAddressClass(lobby.Peer_Address().Get_IP(), Socket_Network_Port(GAME_PORT));
}
}

std::array<unsigned char, 20> Android_LAN_Content(std::string const & map)
{
	std::array<unsigned char, 20> digest{};
	CCFileClass file(map.c_str());
	if (!file.Open(FileClass::READ)) return digest;
	SHAEngine sha;
	char buffer[16384];
	int remaining = file.Size();
	if (remaining <= 0) return digest;
	while (remaining > 0) {
		int count = file.Read(buffer, std::min(remaining, int(sizeof(buffer))));
		if (count <= 0) return digest;
		sha.Hash(buffer, count); remaining -= count;
	}
	uint32_t const compatibility[] = {3, uint32_t(sizeof(EventClass)), uint32_t(sizeof(GlobalPacketType)),
		uint32_t(Addon_Enabled(ADDON_FIRESTORM)), uint32_t(RulesClass::Get_Rule_Unique_ID()),
		uint32_t(RulesClass::Get_Art_Unique_ID()), uint32_t(RulesClass::Get_AI_Unique_ID())};
	sha.Hash(compatibility, sizeof(compatibility));
	sha.Result(digest.data());
	return digest;
}

bool Android_LAN_Open_Transport(AndroidLanProbe const & lobby)
{
	Ipx.Configure_Direct_Peers(GAME_PORT);
	Ipx.Add_Peer(Game_Address(lobby));
	TransportSeen = false; LastTransportSend = 0;
	TransportOpen = Ipx.Init() != 0;
	if (!TransportOpen) Ipx.Shutdown();
	else Ipx.Set_Timing(TIMER_SECOND, unsigned(-1), 10 * TIMER_SECOND);
	return TransportOpen;
}

bool Android_LAN_Check_Transport(AndroidLanProbe const & lobby, uint64_t now)
{
	if (!TransportOpen) return false;
	unsigned char expected[12] = {'O','T','G','A','M','E','3',0};
	for (int i = 0; i < 4; ++i) expected[8 + i] = static_cast<unsigned char>(lobby.Seed >> (24 - i * 8));
	IPXAddressClass peer = Game_Address(lobby);
	if (LastTransportSend == 0 || now - LastTransportSend >= 500) {
		Ipx.Send_Global_Message(expected, sizeof(expected), 0, &peer);
		LastTransportSend = now;
	}
	Ipx.Service();
	unsigned char bytes[sizeof(GlobalPacketType)];
	int length; unsigned short product; IPXAddressClass from;
	for (int i = 0; i < 32 && Ipx.Get_Global_Message(bytes, sizeof(bytes), &length, &from, &product); ++i) {
		if (length == sizeof(expected) && !memcmp(bytes, expected, sizeof(expected))
			&& from.Get_IP() == peer.Get_IP() && from.Get_Port() == peer.Get_Port()
			&& product == IPXGlobalConnClass::COMMAND_AND_CONQUER2) TransportSeen = true;
	}
	return TransportSeen;
}

bool Android_LAN_Launch(std::unique_ptr<AndroidLanProbe> lobby)
{
	if (!lobby || !lobby->Launch_Ready() || !TransportOpen || !TransportSeen) return false;
	int map = -1;
	for (int i = 0; i < Session.Scenarios.Count(); ++i)
		if (lobby->Map == Session.Scenarios[i]->Get_Filename()) map = i;
	if (map < 0) return false;
	int const localSide = HouseTypeClass::From_Name(lobby->Local.Side.c_str());
	int const remoteSide = HouseTypeClass::From_Name(lobby->Remote.Side.c_str());
	if (localSide < 0 || remoteSide < 0) return false;
	Session.Options = {};
	if (!Set_Scenario_Info_From_Index(map)) return false;
	Session.Options.ScenarioIndex = map;
	Session.Options.Bases = true; Session.Options.Credits = lobby->Credits;
	Session.Options.BridgeDestruction = true; Session.Options.ShortGame = true;
	Session.Options.GameSpeed = 2; Session.Options.UnitCount = 1;
	Session.Options.AIDifficulty = DIFF_NORMAL; Session.Options.MCVRedeploy = true;
	Session.Options.AlliesAllowed = true;
	BuildLevel = 10; Options.GameSpeed = 2; Options.Difficulty = DIFF_NORMAL;
	for (int i = 0; i < Session.Players.Count(); ++i) delete Session.Players[i];
	Session.Players.Clear();
	for (int i = 0; i < Session.Computers.Count(); ++i) delete Session.Computers[i];
	Session.Computers.Clear();
	for (int i = 0; i < 2; ++i) {
		bool host = i == 0 ? lobby->Is_Host() : !lobby->Is_Host();
		auto const & player = i == 0 ? lobby->Local : lobby->Remote;
		auto * node = new NodeNameType;
		snprintf(node->Name, sizeof(node->Name), "%s %s", host ? "H:" : "G:", player.Name.c_str());
		node->Player.Color = host ? 0 : 1;
		node->Player.House = i == 0 ? localSide : remoteSide;
		node->Player.ProcessTime = -1;
		if (i == 1) node->Address = Game_Address(*lobby);
		else node->Address.Set_Address(0, Socket_Network_Port(GAME_PORT));
		Session.Players.Add(node);
		if (host) snprintf(Session.MasterPlayerName, sizeof(Session.MasterPlayerName), "%s", node->Name);
	}
	snprintf(Session.Handle, sizeof(Session.Handle), "%s", Session.Players[0]->Name);
	Session.House = HousesType(localSide); Session.ColorIdx = lobby->Is_Host() ? 0 : 1;
	Session.PrefColor = Session.ColorIdx; Session.MasterPlayerID = -1;
	Session.NumPlayers = Session.MaxPlayers = 2;
	Session.Type = GAME_IPX; Session.CommProtocol = COMM_PROTOCOL_MULTI_E_COMP;
	Session.NetOpen = false; Session.LoadGame = Session.Suspended = Session.Play = false;
	Session.IsWDT = false; Session.SquadAlliances = false; Session.Solo = false;
	Session.FrameSendRate = DEFAULT_FRAME_SEND_RATE; Session.MaxAhead = Session.FrameSendRate * 3;
	Session.MaxMaxAhead = Session.MaxAhead; Session.ConnTimeout = 120 * TIMER_SECOND;
	Session.ReconnectTimeout = 40 * TIMER_SECOND;
	snprintf(Session.GameName, sizeof(Session.GameName), "Android LAN");
	Seed = lobby->Seed;
	new (&Environment) EnvironmentClass;
	DebugString("Android LAN launch: map=%s seed=%u local=%s remote=%s endpoint=%s\n",
		lobby->Map.c_str(), unsigned(Seed), Session.Players[0]->Name, Session.Players[1]->Name,
		Session.Players[1]->Address.As_String());
	ActiveLobby = std::move(lobby);
	return true;
}

void Android_LAN_Service()
{
	if (ActiveLobby) ActiveLobby->Tick(Milliseconds());
}

bool Android_LAN_Active() { return ActiveLobby != nullptr; }

void Android_LAN_Reset()
{
	ActiveLobby.reset();
	if (TransportOpen) Ipx.Shutdown();
	TransportOpen = TransportSeen = false;
}

std::string Android_LAN_Take_Error()
{
	std::string error = std::move(NetworkError); NetworkError.clear(); return error;
}

void Shutdown_Network()
{
	Session.GameName[0] = 0;
	Android_LAN_Reset();
	Ipx.Shutdown();
}

void Destroy_Connection(int id, int error)
{
	if (id < 0 || id >= Houses.Count() || !Houses[id] || !Houses[id]->IsHuman) return;
	SaveManager.Disable_Multiplayer_Saving();
	DebugString("Android LAN peer left: house=%d error=%d\n", id, error);
	for (int i = Session.Players.Count() - 1; i >= 0; --i) {
		if (Session.Players[i]->Player.ID == id) {
			delete Session.Players[i]; Session.Players.Delete_Index(i);
		}
	}
	Ipx.Delete_Connection(id);
	Session.NumPlayers = Session.Players.Count();
	if (PlayerPtr) OutList.push_back(EventClass(PlayerPtr->HeapID, EventClass::REMOVEPLAYER, id));
	if (ActiveLobby) NetworkError = "The other player disconnected.";
}

void Sign_Off_Match()
{
	if (TransportOpen) {
		GlobalPacketType packet{}; packet.Command = NET_SIGN_OFF;
		Ipx.Send_Global_Message(&packet, sizeof(packet), 1);
		uint64_t until = Milliseconds() + 500;
		while (Ipx.Global_Num_Send() && Milliseconds() < until) { Ipx.Service(); Sleep(10); }
	}
	GameActive = false;
}

DesyncDialogClass DesyncDialog;
DesyncDialogClass::OutcomeType DesyncDialogClass::Run()
{
	NetworkError = "LAN test stopped: the games went out of sync.";
	DebugString("Android LAN: desync detected; ending match.\n");
	return OutcomeType::Quit;
}
void DesyncDialogClass::Service() {}
void DesyncDialogClass::Notify_Chat(char const *, char const *) {}
void DesyncDialogClass::Notify_Heartbeat(int) {}
void DesyncDialogClass::Notify_Continue() {}
void DesyncDialogClass::Notify_Player_Left(int, char const *) {}
void DesyncDialogClass::Notify_Master_Changed() {}
#endif
