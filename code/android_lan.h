// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 OpenTS contributors
#pragma once

#include <cstdint>
#include "netsocket.h"
#include <array>
#include <string>

// Lobby packets never enter the gameplay event queues.
class AndroidLanProbe {
public:
	static constexpr unsigned short PORT = 49152;
	struct Host { IPXAddressClass Address; uint64_t Seen; };
	explicit AndroidLanProbe(std::unique_ptr<SocketClass> socket);
	bool Open(bool host, uint32_t nonce, bool discovery = true);
	bool Join_Address(std::string const & address);
	void Tick(uint64_t now);
	void Join(size_t index);
	bool Set_Player(std::string const & name, std::string const & side);
	bool Set_Map(std::string const & map, uint32_t seed);
	void Set_Available(bool available);
	void Set_Ready(bool ready);
	struct Player {
		std::string Name, Side;
		bool Ready = false, Available = false;
	};
	Player Local, Remote;
	std::string Map;
	uint32_t Seed = 0, Revision = 0;
	uint32_t Credits = 10000;
	bool Set_Credits(uint32_t credits);
	bool Both_Ready() const;
	void Set_Content(std::array<unsigned char, 20> const & digest);
	bool Compatible() const;
	bool Request_Start();
	bool Starting() const { return LaunchStage != 0; }
	bool Launch_Ready() const { return LaunchStage == 4; }
	IPXAddressClass Peer_Address() const { return Peer; }
	bool Is_Host() const { return Hosting; }
	std::vector<Host> Hosts;
	std::string Status;
	bool Connected = false;
private:
	std::unique_ptr<SocketClass> Socket;
	std::vector<IPXAddressClass> Broadcasts;
	IPXAddressClass Peer;
	bool Hosting = false, Joining = false, Active = false, Discovery = true;
	uint32_t Nonce = 0, PeerNonce = 0;
	uint64_t LastSend = 0, LastPeer = 0, Now = 0;
	uint64_t LastLobby = 0;
	uint32_t Sequence = 0, RemoteSequence = 0;
	uint32_t AcknowledgedSequence = 0;
	std::array<unsigned char, 20> Content{}, RemoteContent{};
	unsigned char LaunchStage = 0;
	void Invalidate();
	void Send_Lobby();
	void Receive_Lobby(unsigned char const * bytes);
	bool Send(unsigned char type, uint32_t nonce, IPXAddressClass const & to);
};
