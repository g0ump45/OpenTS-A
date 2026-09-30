// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 OpenTS contributors
#include "android_lan.h"
#include <algorithm>
#include <cstring>

namespace {
bool Same(IPXAddressClass const & a, IPXAddressClass const & b)
{
	return a.Get_IP() == b.Get_IP() && a.Get_Port() == b.Get_Port();
}

uint32_t Read32(unsigned char const * p)
{
	return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3];
}

void Write32(unsigned char * p, uint32_t value)
{
	for (int i = 0; i < 4; ++i) p[i] = static_cast<unsigned char>(value >> (24 - 8 * i));
}

bool Valid_Text(std::string const & value, size_t capacity)
{
	return !value.empty() && value.size() < capacity
		&& std::all_of(value.begin(), value.end(), [](unsigned char c) { return c >= 32 && c <= 126; });
}

bool Read_Text(unsigned char const * p, size_t capacity, std::string & out)
{
	auto end = std::find(p, p + capacity, 0);
	if (end == p + capacity) return false;
	out.assign(reinterpret_cast<char const *>(p), size_t(end - p));
	return Valid_Text(out, capacity);
}
}

AndroidLanProbe::AndroidLanProbe(std::unique_ptr<SocketClass> socket) : Socket(std::move(socket)) {}

bool AndroidLanProbe::Open(bool host, uint32_t nonce, bool discovery)
{
	if (!Socket) { Status = "LAN transport is unavailable."; return false; }
	Socket->Close();
	Hosts.clear(); Broadcasts.clear(); Connected = Joining = Active = false;
	Discovery = discovery; Hosting = host; Nonce = nonce; LastSend = LastPeer = Now = 0;
	LastLobby = 0; Revision = host ? 1 : 0; Sequence = RemoteSequence = AcknowledgedSequence = 0;
	Local = {}; Remote = {}; Map.clear(); Seed = 0; Credits = 10000;
	Content = {}; RemoteContent = {}; LaunchStage = 0;
	if (!Socket->Open(host ? PORT : 0) || (Discovery && !Socket->Set_Broadcast(true))) {
		Socket->Close(); Status = "Cannot open LAN socket."; return false;
	}
	std::vector<InterfaceType> interfaces;
	if (Discovery) Socket->Local_Interfaces(interfaces);
	for (auto const & entry : interfaces) {
		if (entry.Broadcast) Broadcasts.emplace_back(entry.Broadcast, Socket_Network_Port(PORT));
	}
	if (Broadcasts.empty()) Broadcasts.emplace_back(0xffffffffU, Socket_Network_Port(PORT));
	Active = true;
	Status = host ? "Waiting for a player..." : Discovery ? "Searching local Wi-Fi..." : "Enter the host IPv4 address.";
	return true;
}

bool AndroidLanProbe::Send(unsigned char type, uint32_t nonce, IPXAddressClass const & to)
{
	unsigned char bytes[12] = {'O','T','L','P',4,type,0,0,0,0,0,0};
	for (int i = 0; i < 4; ++i) bytes[8+i] = static_cast<unsigned char>(nonce >> (24 - 8*i));
	auto const result = Socket->Send_To(bytes, sizeof(bytes), to);
	return result.Error == SocketError::NONE && result.Length == sizeof(bytes);
}

void AndroidLanProbe::Join(size_t index)
{
	if (!Active || Hosting || index >= Hosts.size()) return;
	Peer = Hosts[index].Address; Joining = true; Connected = false;
	LastPeer = Now; LastSend = 0;
	Status = "Connecting to " + std::string(Peer.As_String());
}

bool AndroidLanProbe::Join_Address(std::string const & address)
{
	if (!Active || Hosting || Connected || Joining) return false;
	unsigned char octets[4]{};
	size_t pos = 0;
	for (int i = 0; i < 4; ++i) {
		unsigned value = 0, digits = 0;
		while (pos < address.size() && address[pos] >= '0' && address[pos] <= '9') {
			value = value * 10 + unsigned(address[pos++] - '0');
			if (++digits > 3 || value > 255) return false;
		}
		if (!digits) return false;
		octets[i] = static_cast<unsigned char>(value);
		if (i != 3 && (pos == address.size() || address[pos++] != '.')) return false;
	}
	if (pos != address.size() || octets[0] == 0 || octets[0] == 127 || octets[0] >= 224 || octets[3] == 255) return false;
	uint32_t ip;
	memcpy(&ip, octets, sizeof(ip));
	Hosts = {{IPXAddressClass(ip, Socket_Network_Port(PORT)), Now}};
	Join(0);
	Hosts.clear();
	return true;
}

void AndroidLanProbe::Tick(uint64_t now)
{
	if (!Active) return;
	Now = now;
	if (Joining && LastPeer == 0) LastPeer = now;
	if (!Hosting && (LastSend == 0 || now - LastSend >= 1000)) {
		if (Joining) Send(3, Nonce, Peer);
		else if (Discovery) for (auto const & address : Broadcasts) Send(1, Nonce, address);
		LastSend = now;
	}
	// Bound work even when another host floods the socket.
	for (int count = 0; count < 32; ++count) {
		unsigned char bytes[256]; IPXAddressClass from;
		auto const result = Socket->Receive_From(bytes, sizeof(bytes), from);
		if (result.Error == SocketError::WOULD_BLOCK) break;
		if (result.Error != SocketError::NONE) { Socket->Clear_Error(); break; }
		if (result.Length < 12 || memcmp(bytes, "OTLP", 4) || bytes[4] != 4 || bytes[6] || bytes[7]) continue;
		uint32_t nonce = 0;
		for (int i = 8; i < 12; ++i) nonce = (nonce << 8) | bytes[i];
		if (bytes[5] == (Hosting ? 5 : 6)) {
			if (result.Length == 176 && Connected && Same(Peer, from)
				&& nonce == (Hosting ? PeerNonce : Nonce)) Receive_Lobby(bytes);
			continue;
		}
		if (result.Length != 12) continue;
		if (Hosting) {
			if (bytes[5] == 1 && !Connected) Send(2, nonce, from);
			else if (bytes[5] == 3 && (!Connected || (Same(Peer, from) && PeerNonce == nonce))) {
				if (Send(4, nonce, from)) {
					Peer = from; PeerNonce = nonce; Connected = true; LastPeer = now;
					Status = "Connected: " + std::string(Peer.As_String());
				}
			}
		} else if (nonce == Nonce) {
			if (bytes[5] == 2 && Discovery && !Joining && from.Get_Port() == Socket_Network_Port(PORT)) {
				auto found = std::find_if(Hosts.begin(), Hosts.end(), [&](Host const & h) { return Same(h.Address, from); });
				if (found != Hosts.end()) found->Seen = now;
				else if (Hosts.size() < 5) Hosts.push_back({from, now});
			} else if (bytes[5] == 4 && Joining && Same(Peer, from)) {
				Connected = true; LastPeer = now;
				Status = "Connected: " + std::string(Peer.As_String());
			}
		}
	}
	Hosts.erase(std::remove_if(Hosts.begin(), Hosts.end(), [&](Host const & h) { return now - h.Seen > 5000; }), Hosts.end());
	if ((Connected || Joining) && now - LastPeer > (LaunchStage == 4 ? 120000u : 5000u)) {
		Connected = Joining = false;
		Remote = {}; RemoteSequence = AcknowledgedSequence = 0; Local.Ready = false;
		RemoteContent = {}; LaunchStage = 0;
		if (Hosting) Invalidate();
		else { Revision = 0; Map.clear(); Local.Available = false; }
		Status = Hosting ? "Player disconnected. Waiting..." : (Discovery ? "Connection timed out. Searching..." : "Timed out. Back and check IP / port forwarding.");
	}
	if (Connected && (LastLobby == 0 || now - LastLobby >= 250)) {
		Send_Lobby(); LastLobby = now;
	}
}


void AndroidLanProbe::Invalidate()
{
	LaunchStage = 0;
	if (Hosting) ++Revision;
	Local.Ready = Remote.Ready = false;
	++Sequence; LastLobby = 0;
}


bool AndroidLanProbe::Set_Player(std::string const & name, std::string const & side)
{
	if (Starting()) return false;
	if (!Valid_Text(name, 24) || !Valid_Text(side, 32)) return false;
	if (Local.Name != name || Local.Side != side) {
		Local.Name = name; Local.Side = side; Invalidate();
	}
	return true;
}


bool AndroidLanProbe::Set_Map(std::string const & map, uint32_t seed)
{
	if (Starting()) return false;
	if (!Hosting || !Valid_Text(map, 64)) return false;
	if (Map != map || Seed != seed) {
		Map = map; Seed = seed; Local.Available = false; Remote.Available = false; Invalidate();
	}
	return true;
}


bool AndroidLanProbe::Set_Credits(uint32_t credits)
{
	if (Starting() || !Hosting) return false;
	if (credits < 2500 || credits > 10000 || credits % 500 != 0) return false;

	if (Credits != credits) {
		Credits = credits;
		Invalidate();
	}
	return true;
}

void AndroidLanProbe::Set_Available(bool available)
{
	if (Starting()) return;
	if (Local.Available != available) {
		Local.Available = available; Invalidate();
	}
}


void AndroidLanProbe::Set_Ready(bool ready)
{
	if (Starting()) return;
	ready = ready && Connected && Local.Available && Compatible() && !Map.empty() && Revision != 0;
	if (Local.Ready != ready) { Local.Ready = ready; ++Sequence; LastLobby = 0; }
}


bool AndroidLanProbe::Both_Ready() const
{
	return Connected && Local.Ready && Remote.Ready && Local.Available && Remote.Available
		&& Compatible() && AcknowledgedSequence == Sequence;
}


void AndroidLanProbe::Set_Content(std::array<unsigned char, 20> const & digest)
{
	if (!Starting() && Content != digest) { Content = digest; Invalidate(); }
}


bool AndroidLanProbe::Compatible() const
{
	return Content != std::array<unsigned char, 20>{} && Content == RemoteContent;
}


bool AndroidLanProbe::Request_Start()
{
	if (!Hosting || Starting() || !Both_Ready()) return false;
	LaunchStage = 1; ++Sequence; LastLobby = 0;
	return true;
}


void AndroidLanProbe::Send_Lobby()
{
	unsigned char bytes[176] = {'O','T','L','P',4,static_cast<unsigned char>(Hosting ? 6 : 5)};
	Write32(bytes + 8, Hosting ? PeerNonce : Nonce);
	Write32(bytes + 12, Revision); Write32(bytes + 16, Sequence);
	bytes[20] = Local.Ready; bytes[21] = Local.Available;
	memcpy(bytes + 22, Local.Name.data(), Local.Name.size());
	memcpy(bytes + 46, Local.Side.data(), Local.Side.size());
	memcpy(bytes + 78, Map.data(), Map.size()); Write32(bytes + 142, Seed);
	Write32(bytes + 148, RemoteSequence);
	bytes[146] = LaunchStage;
	std::copy(Content.begin(), Content.end(), bytes + 152);
	Write32(bytes + 172, Credits);
	Socket->Send_To(bytes, sizeof(bytes), Peer);
}


void AndroidLanProbe::Receive_Lobby(unsigned char const * bytes)
{
	Player player;
	std::string map;
	uint32_t const credits = Read32(bytes + 172);
	if (credits < 2500 || credits > 10000 || credits % 500 != 0
		|| bytes[20] > 1 || bytes[21] > 1 || bytes[146] > 4 || bytes[147]
		|| !Read_Text(bytes + 22, 24, player.Name) || !Read_Text(bytes + 46, 32, player.Side)
		|| !Read_Text(bytes + 78, 64, map)) return;
	uint32_t const revision = Read32(bytes + 12), sequence = Read32(bytes + 16);
	if (sequence < RemoteSequence || revision == 0 || Read32(bytes + 148) > Sequence) return;
	if (Hosting) {
		if (revision > Revision) return;
		if (player.Name != Remote.Name || player.Side != Remote.Side) Invalidate();
		player.Available = bytes[21] && revision == Revision && map == Map && Read32(bytes + 142) == Seed && credits == Credits;
		player.Ready = bytes[20] && player.Available;
	} else {
		if (revision < Revision) return;
		if (revision != Revision) {
			Local.Ready = false; ++Sequence; LastLobby = 0;
			if (map != Map) Local.Available = false;
		}
		Revision = revision; Map = map; Seed = Read32(bytes + 142); Credits = credits;
		player.Available = bytes[21]; player.Ready = bytes[20] && player.Available;
	}
	Remote = std::move(player); RemoteSequence = sequence;
	AcknowledgedSequence = std::max(AcknowledgedSequence, Read32(bytes + 148));
	std::array<unsigned char, 20> digest;
	std::copy(bytes + 152, bytes + 172, digest.begin());
	if (RemoteContent != digest) {
		RemoteContent = digest;
		Invalidate();
	}
	if (!Compatible()) { Local.Ready = Remote.Ready = false; LaunchStage = 0; }
	bool const ready = Connected && Local.Ready && Remote.Ready && Local.Available && Remote.Available && Compatible();
	if (Starting() && !Launch_Ready() && !ready) { Invalidate(); return; }
	unsigned char next = LaunchStage;
	if (Hosting) {
		if (LaunchStage == 1 && bytes[146] == 2 && ready) next = 3;
		if (LaunchStage == 3 && bytes[146] == 4 && ready) next = 4;
	} else {
		if (LaunchStage == 0 && bytes[146] == 1 && ready) next = 2;
		if (LaunchStage == 2 && bytes[146] == 3 && ready) next = 4;
		if (LaunchStage == 2 && bytes[146] == 0) { next = 0; Local.Ready = false; }
	}
	if (next != LaunchStage) { LaunchStage = next; ++Sequence; LastLobby = 0; }
}
