#include "android_lan.h"
#include <cassert>
#include <cstdio>
#include <deque>

IPXAddressClass::IPXAddressClass() : IP(0xffffffffU), Port(0) {}
IPXAddressClass::IPXAddressClass(uint32_t ip, uint16_t port) : IP(ip), Port(port) {}
void IPXAddressClass::Set_Address(uint32_t ip, uint16_t port) { IP=ip; Port=port; }
char const * IPXAddressClass::As_String() { return "test-peer"; }

struct Mock : SocketClass {
	struct Packet { std::vector<unsigned char> Data; IPXAddressClass From; };
	Mock * Other = nullptr;
	std::deque<Packet> Inbox;
	IPXAddressClass Address;
	bool FailOpen = false, Drop = false, Opened = false;
	int DropStage = -1;
	int Sends = 0;
	IPXAddressClass LastDestination;
	bool Open(unsigned short port) override { Address.Set_Address(port ? 1 : 2, Socket_Network_Port(port ? port : 50000)); return Opened = !FailOpen; }
	void Close() override { Opened=false; }
	bool Is_Open() const override { return Opened; }
	bool Set_Broadcast(bool) override { return true; }
	bool Set_Buffer_Sizes(int,int) override { return true; }
	void Clear_Error() override {}
	bool Local_Interfaces(std::vector<InterfaceType>&) override { return false; }
	TransferResult Send_To(void const * data,int size,IPXAddressClass const & to) override {
		++Sends; LastDestination = to;
		auto p=static_cast<unsigned char const *>(data);
		if (!Drop && Other && !(size > 146 && p[146] == DropStage)) Other->Inbox.push_back({{p,p+size},Address});
		return {SocketError::NONE,size};
	}
	TransferResult Receive_From(void * data,int size,IPXAddressClass & from) override {
		if(Inbox.empty()) return {SocketError::WOULD_BLOCK,0};
		auto p=Inbox.front(); Inbox.pop_front();
		int n=std::min(size,int(p.Data.size())); memcpy(data,p.Data.data(),n); from=p.From;
		return {SocketError::NONE,n};
	}
};

int main() {
	auto h=std::make_unique<Mock>(), c=std::make_unique<Mock>();
	auto * host=h.get(); auto * client=c.get(); host->Other=client; client->Other=host;
	AndroidLanProbe server(std::move(h)), browser(std::move(c));
	assert(server.Open(true,10)); assert(browser.Open(false,20));
	assert(server.Set_Player("Host", "GDI")); assert(browser.Set_Player("Guest", "Nod"));
	assert(server.Set_Map("map01.map", 123)); server.Set_Available(true);
	std::array<unsigned char, 20> content{}; content[0] = 42;
	server.Set_Content(content); browser.Set_Content(content);
	client->Inbox.push_back({{'b','a','d'},host->Address});
	browser.Tick(100); server.Tick(100); browser.Tick(101);
	assert(browser.Hosts.size()==1); assert(!browser.Connected);
	browser.Join(0);
	host->Drop=true; browser.Tick(200); server.Tick(200); browser.Tick(201);
	assert(!browser.Connected && server.Connected);
	host->Drop=false; browser.Tick(1200); server.Tick(1200); browser.Tick(1201);
	assert(browser.Connected && server.Connected);
	client->Inbox.push_back({{'O','T','L','P',3,4,0,0,0,0,0,20},IPXAddressClass(99,Socket_Network_Port(AndroidLanProbe::PORT))});
	uint64_t time = 1500;
	auto settle = [&](int count = 8) {
		for (int i = 0; i < count; ++i) { browser.Tick(time); server.Tick(time); browser.Tick(time + 1); time += 300; }
	};
	settle();
	assert(browser.Map == "map01.map" && browser.Seed == 123);
	browser.Set_Available(true); settle();
	assert(server.Remote.Name == "Guest" && browser.Remote.Name == "Host");
	server.Set_Ready(true); browser.Set_Ready(true); settle();
	assert(server.Both_Ready() && browser.Both_Ready());
	browser.Set_Ready(false); browser.Set_Ready(true);
	assert(!browser.Both_Ready()); settle(); assert(browser.Both_Ready());
	assert(!browser.Set_Map("forbidden.map", 99));
	assert(!server.Set_Player(std::string(24, 'X'), "GDI"));
	assert(server.Set_Map("map02.map", 456)); server.Set_Available(true); settle();
	assert(!server.Both_Ready() && !browser.Local.Ready && !browser.Local.Available);
	browser.Set_Ready(true); assert(!browser.Local.Ready);
	browser.Set_Available(true); settle();
	server.Set_Ready(true); browser.Set_Ready(true); settle();
	assert(server.Both_Ready());
	assert(browser.Set_Player("Guest2", "GDI")); settle();
	assert(!server.Local.Ready && !browser.Local.Ready && server.Remote.Name == "Guest2");
	server.Set_Ready(true); browser.Set_Ready(true); settle();
	assert(browser.Both_Ready());
	// Reordered state must not undo a newer profile or setup.
	server.Tick(time + 300); auto stale = client->Inbox.back();
	server.Set_Map("map03.map", 789); server.Set_Available(true); settle();
	client->Inbox.push_back(stale); browser.Tick(time);
	assert(browser.Map == "map03.map" && !browser.Local.Ready);
	// Version one peers and malformed lobby packets are ignored.
	auto malformed = stale; malformed.Data[4] = 1; client->Inbox.push_back(malformed);
	malformed = stale; malformed.Data[20] = 2; client->Inbox.push_back(malformed);
	browser.Tick(time); assert(browser.Map == "map03.map");
	content[0] = 99; browser.Set_Content(content); settle();
	assert(!server.Compatible() && !browser.Compatible());
	browser.Set_Ready(true); assert(!browser.Local.Ready); assert(!server.Request_Start());
	content[0] = 42; browser.Set_Content(content); browser.Set_Available(true); settle();
	server.Set_Ready(true); browser.Set_Ready(true); settle();
	assert(server.Both_Ready() && browser.Both_Ready());
	assert(server.Request_Start()); browser.Set_Ready(false); settle();
	assert(!server.Starting() && !browser.Starting());
	server.Set_Ready(true); browser.Set_Ready(true); settle();
	assert(!browser.Request_Start()); assert(server.Request_Start());
	assert(!server.Set_Map("locked.map", 1)); assert(!server.Set_Player("Changed", "Nod"));
	host->DropStage = 1; settle(3); assert(!browser.Launch_Ready() && !server.Launch_Ready());
	host->DropStage = 3; settle(3); assert(!browser.Launch_Ready() && !server.Launch_Ready());
	// The guest keeps acknowledging commit while loading, until the host can leave its lobby.
	host->DropStage = -1; client->DropStage = 4; settle(3);
	assert(browser.Launch_Ready() && !server.Launch_Ready());
	client->DropStage = -1; settle();
	assert(server.Launch_Ready() && browser.Launch_Ready());
	client->Drop=true; host->Drop=true; browser.Tick(time + 121000); server.Tick(time + 122000); browser.Tick(time + 122001);
	assert(!server.Connected && !browser.Connected);
	assert(browser.Hosts.empty());
	assert(browser.Open(false,30));
	client->Inbox.push_back({{'O','T','L','P',3,2,0,0,0,0,0,20},host->Address});
	browser.Tick(100); assert(browser.Hosts.empty());
	auto bad=std::make_unique<Mock>(); bad->FailOpen=true;
	AndroidLanProbe failed(std::move(bad)); assert(!failed.Open(true,1));
	AndroidLanProbe missing(nullptr); assert(!missing.Open(true,1));
	{
		auto hs = std::make_unique<Mock>(), cs = std::make_unique<Mock>();
		auto * hp = hs.get(); auto * cp = cs.get(); hp->Other = cp; cp->Other = hp;
		AndroidLanProbe directHost(std::move(hs)), directClient(std::move(cs));
		assert(directHost.Open(true, 55, false)); assert(directClient.Open(false, 66, false));
		for (auto const * invalid : {"", "1.2.3", "256.1.2.3", "1.2.3.4extra", "1..2.3", "127.0.0.1", "224.0.0.1", "0.0.0.0"})
			assert(!directClient.Join_Address(invalid));
		unsigned char octets[] = {203, 0, 113, 4}; uint32_t ip; memcpy(&ip, octets, 4);
		hp->Address.Set_Address(ip, Socket_Network_Port(AndroidLanProbe::PORT));
		assert(directClient.Join_Address("203.0.113.4"));
		directClient.Tick(900000); assert(!directClient.Connected);
		assert(cp->Sends == 1 && cp->LastDestination.Get_IP() == ip);
		directHost.Tick(900000); directClient.Tick(900001);
		assert(directClient.Connected && directHost.Connected);
		assert(!directClient.Join_Address("203.0.113.5"));
		hp->Drop = cp->Drop = true;
		directClient.Tick(910000); assert(!directClient.Connected);
		int sends = cp->Sends; directClient.Tick(912000);
		assert(cp->Sends == sends && directClient.Hosts.empty());
		assert(directClient.Open(false, 77, false));
		directClient.Tick(920000); assert(cp->Sends == sends);
	}
	puts("PASS: direct IPv4 join, invalid addresses, long-uptime initial join, timeout without broadcasts");
	puts("PASS: lobby, content mismatch, readiness, launch request/commit/ack loss recovery, frozen setup, timeout, ordering, malformed packets, bind failure");
}
