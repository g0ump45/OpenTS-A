#include "always.h"

#ifdef __ANDROID__
#include "android_options.h"
#include "android_support.h"
#include "android_controls.h"
#include "android_lan.h"
#include "android_lan_game.h"
#include "rules.h"
#include <chrono>
#include <functional>
#include <random>
#include "newmenu.h"
#include "grphmenu.h"
#include "campaign.h"
#include "addon.h"
#include "enviro.h"
#include "init.h"
#include "netshare.h"
#include "houstype.h"
#include "movie.h"
#include "android_video.h"
#include "_keyboar.h"
#include "_map.h"
#include "_surface.h"
#include "_command.h"
#include "_tooltip.h"
#include "cctooltip.h"
#include "ccini.h"
#include "ccfile.h"
#include "command.h"
#include "conquer.h"
#include "dialog.h"
#include "dsurface.h"
#include "gamedirs.h"
#include "globals.h"
#include "goptions.h"
#include "house.h"
#include "index.h"
#include "language/language.h"
#include "queue.h"
#include "savemgr.h"
#include "saveload.h"
#include "savever.h"
#include "scenario.h"
#include "session.h"
#include "textbtn.h"
#include "srfcache.h"
#include "ownrdraw.h"
#include "font.h"
#include "scheme.h"
#include "techno.h"
#include "theme.h"
#include "audio/audioengine.h"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct Choice {
	int ID;
	std::string Text;
	int X, Y, Width;
	bool Enabled = true;
};

Surface * Menu_Art(char const * name)
{
	Surface * art = SurfaceCache.GetSurface(name);
	if (art == nullptr && SurfaceCache.CachePCX(name)) art = SurfaceCache.GetSurface(name);
	return art;
}

void Draw_Menu_Panel(Rect const & rect)
{
	LogicalSurface->Fill_Rect(rect, DSurface::Build_Hicolor_Pixel(0, 80, 88));
	if (Surface * back = Menu_Art("dbak6440.pcx")) {
		SurfaceCache.Draw(rect, *LogicalSurface, *back);
	}
	for (int side = 0; side < 2; ++side) {
		if (Surface * bar = Menu_Art(side ? "rightbar.pcx" : "leftbar.pcx")) {
			SurfaceCache.Draw(Rect(side ? rect.X + rect.Width - bar->Get_Width() : rect.X,
				rect.Y, bar->Get_Width(), rect.Height), *LogicalSurface, *bar);
		}
	}
	char const * corners[] = {"bar_ul.pcx", "bar_ur.pcx", "bar_ll.pcx", "bar_lr.pcx"};
	for (int i = 0; i < 4; ++i) {
		if (Surface * corner = Menu_Art(corners[i])) {
			Rect destination((i & 1) ? rect.X + rect.Width - corner->Get_Width() : rect.X,
				(i & 2) ? rect.Y + rect.Height - corner->Get_Height() : rect.Y,
				corner->Get_Width(), corner->Get_Height());
			LogicalSurface->Blit_From(destination, *corner, corner->Get_Rect());
		}
	}
}

class MenuButton : public TextButtonClass {
public:
	using TextButtonClass::TextButtonClass;

protected:
	void Draw_Background(void) override
	{
		char name[32];
		Surface * pieces[3];
		char const * positions[] = {"li", "mi", "ri"};
		for (int i = 0; i < 3; ++i) {
			snprintf(name, sizeof(name), "b%ce_%s%d.pcx", IsPressed ? 'd' : 'u', positions[i], Height <= 24 ? 24 : 30);
			pieces[i] = Menu_Art(name);
		}
		if (!pieces[0] || !pieces[1] || !pieces[2]) {
			TextButtonClass::Draw_Background();
			return;
		}
		int const left = pieces[0]->Get_Width(), right = pieces[2]->Get_Width();
		SurfaceCache.Draw(Rect(X, Y, left, Height), *LogicalSurface, *pieces[0]);
		SurfaceCache.Draw(Rect(X + left, Y, Width - left - right, Height), *LogicalSurface, *pieces[1]);
		SurfaceCache.Draw(Rect(X + Width - right, Y, right, Height), *LogicalSurface, *pieces[2]);
	}

	void Draw_Text(char const * text) override
	{
		ColorScheme * scheme = Fetch_Scheme_By_Name("Green");
		if (scheme == nullptr) scheme = ColorSchemes[Get_Color_Scheme()];
		TextPrintType flags = TextPrintType(TPF_BUTTON | TPF_USE_GRAD_PAL |
			(IsDisabled ? 0 : IsPressed ? TPF_BRIGHT_COLOR : TPF_MEDIUM_COLOR));
		int const offset = IsPressed ? 1 : 0;
		Simple_Text_Print(text, *LogicalSurface, Rect(X, Y, Width, Height),
			Point2D(Width / 2 + offset, (Height - Font_From_TPF(flags)->Get_Height()) / 2 + offset),
			scheme, TBLACK, flags, true);
	}
};

class Menu {
	bool PreviousMenuState;
public:
	DSurface Background;
	Menu() : PreviousMenuState(AndroidMenuActive.exchange(true)), Background(VisibleSurface->Get_Width(), VisibleSurface->Get_Height())
	{
		Background.Blit_From(*VisibleSurface);
	}
	~Menu() { AndroidMenuActive = PreviousMenuState; }
	Menu(Menu const &) = delete;
	Menu & operator=(Menu const &) = delete;

	int Show(char const * title, std::vector<Choice> const & choices,
		std::vector<std::string> const & lines = {}, bool compact = false, std::function<bool()> poll = {})
	{
		int const ox = (HiddenSurface->Get_Width() - 640) / 2;
		Keyboard->Clear();
		LogicalSurface = HiddenSurface;
		HiddenSurface->Blit_From(Background);
		Draw_Menu_Panel(compact ? Rect(180 + ox, 110, 280, 240) : Rect(90 + ox, 28, 460, 424));
		if (!compact) {
			TextButtonClass heading(0, title, TPF_BUTTON, 110 + ox, 42, 420, 26, false, true);
			heading.Draw_Me(true);
		}
		for (size_t i = 0; i < lines.size(); ++i) {
			TextButtonClass line(0, lines[i].c_str(), TPF_BUTTON, 108 + ox, 78 + int(i) * 20, 424, 20, false, true);
			line.Draw_Me(true);
		}
		std::vector<std::unique_ptr<TextButtonClass>> buttons;
		GadgetClass * list = nullptr;
		for (Choice const & item : choices) {
			auto button = std::make_unique<MenuButton>(item.ID, item.Text.c_str(), TPF_BUTTON,
				item.X + ox, item.Y, item.Width, compact ? 24 : 30);
			if (list) button->Add(*list);
			else list = button.get();
			if (!item.Enabled) button->Disable();
			buttons.push_back(std::move(button));
		}
		for (;;) {
			Call_Back();
			if (poll && poll()) return -1;
			unsigned const input = list->Input();
			list->Draw_All();
			VisibleSurface->Blit_From(*HiddenSurface);
			auto * visible = static_cast<DSurface *>(VisibleSurface);
			// The snapshot is already transformed into display coordinates.
			Android_Video_Present(visible->Get_Buffer(), visible->Get_Width(), visible->Get_Height(), visible->Stride());
			if (input == KN_ESC) return 0;
			for (Choice const & item : choices) {
				if (item.Enabled && input == (unsigned(item.ID) | KN_BUTTON)) {
					Keyboard->Clear();
					return item.ID;
				}
			}
			Sleep(16);
		}
	}

	bool Confirm(char const * title, char const * detail)
	{
		return Show(title, {{1, "Confirm", 150, 360, 150}, {2, "Cancel", 340, 360, 150}}, {detail}) == 1;
	}

	void Message(char const * title, char const * detail)
	{
		Show(title, {{1, "Back", 220, 390, 200}}, {detail});
	}
};

bool Local_Network(Menu & menu, bool internet = false)
{
	Prepare_Side_Roster();
	RulesClass::Load_Art_INI();
	Session.Read_Scenario_Descriptions();
	std::vector<std::string> maps, names, sides;
	for (int i = 0; i < Session.Scenarios.Count(); ++i) {
		std::string file = Session.Scenarios[i]->Get_Filename();
		if (file.size() < 64 && CCFileClass(file.c_str()).Is_Available() && RandomMapWaypointCount(i) >= 2) {
			maps.push_back(file); names.push_back(Session.Scenarios[i]->Description());
		}
	}
	for (int i = 0; i < HouseTypes.Count(); ++i) {
		if (HouseTypes[i]->IsMultiplay) sides.emplace_back(HouseTypes[i]->Name());
	}
	if (maps.empty() || sides.empty()) { menu.Message("Local Wi-Fi", "No installed multiplayer maps or sides."); return false; }
	for (;;) {
		int mode = menu.Show(internet ? "Internet - Direct IP" : "Local Wi-Fi", {{1, "Host Lobby", 150, 185, 340},
			{2, internet ? "Join by IP" : "Find LAN Hosts", 150, 240, 340}, {4, "Connection Help", 150, 295, 340}, {3, "Back", 220, 390, 200}},
			internet ? std::vector<std::string>{"Both routers: forward UDP 49153 to the phone.", "Host router: also forward UDP 49152.", "Use matching builds and game data."} :
			std::vector<std::string>{"LAN Match", "Both devices must use this build on the same Wi-Fi.", "1v1: bases, no AI or crates."});
		if (mode == 4) {
			if (!Android_Open_Connection_Help()) menu.Message("Connection Help", "Could not open help.");
			continue;
		}
		if (mode != 1 && mode != 2) return false;
		Android_LAN_Reset();
		auto ownedProbe = std::make_unique<AndroidLanProbe>(Socket_Create_Platform_Socket());
		auto & probe = *ownedProbe;
		if (!probe.Open(mode == 1, std::random_device{}(), !internet)) { menu.Message("Local Wi-Fi", probe.Status.c_str()); continue; }
		if (internet && mode == 2) {
			std::string address;
			bool joined = false;
			for (;;) {
				std::vector<Choice> keys;
				std::string const digits = "123456789.0";
				for (int i = 0; i < int(digits.size()); ++i)
					keys.push_back({200 + i, std::string(1, digits[i]), 160 + (i % 3) * 110, 130 + (i / 3) * 43, 100});
				keys.insert(keys.end(), {{20, "Delete", 110, 330, 130}, {21, "Connect", 255, 330, 130}, {22, "Back", 400, 330, 130}});
				int key = menu.Show("Host IPv4 address", keys, {address.empty() ? "Enter the host's public IPv4 address" : address});
				if (key >= 200 && key < 211 && address.size() < 15) address += digits[key - 200];
				else if (key == 20 && !address.empty()) address.pop_back();
				else if (key == 21) {
					if (probe.Join_Address(address)) { joined = true; break; }
					menu.Message("Invalid address", "Enter four numbers from 0 to 255, separated by dots.");
				} else if (key == 22 || key == 0) break;
			}
			if (!joined) continue;
		}
		size_t selected = 0, side = 0;
		std::string player = Session.Handle[0] ? Session.Handle : (mode == 1 ? "Host" : "Guest");
		if (!probe.Set_Player(player, sides[side])) { player = mode == 1 ? "Host" : "Guest"; probe.Set_Player(player, sides[side]); }
		if (mode == 1) probe.Set_Map(maps[selected], std::random_device{}());
		bool editing = false, wired = false, wireFailed = false, wireReady = false;
		std::string draft, hashedMap;
		auto tick = [&]() {
			auto now = std::chrono::steady_clock::now().time_since_epoch();
			uint64_t const ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
			probe.Tick(ms);
			if (probe.Connected && !wired && !wireFailed) {
				wired = Android_LAN_Open_Transport(probe); wireFailed = !wired;
			}
			if (!probe.Connected && wired) { Android_LAN_Reset(); wired = wireReady = false; }
			if (wired) wireReady = Android_LAN_Check_Transport(probe, ms);
			bool const mapFound = std::find(maps.begin(), maps.end(), probe.Map) != maps.end();
			bool const sideFound = probe.Remote.Side.empty() || std::find(sides.begin(), sides.end(), probe.Remote.Side) != sides.end();
			if (mapFound && hashedMap != probe.Map) {
				probe.Set_Content(Android_LAN_Content(probe.Map)); hashedMap = probe.Map;
			}
			probe.Set_Available(mapFound && sideFound && wireReady);
		};
		auto state = [&]() {
			std::string value = probe.Status + probe.Map + probe.Remote.Name + probe.Remote.Side;
			value += std::to_string(probe.Revision) + std::to_string(probe.Credits) + std::to_string(probe.Local.Ready) + std::to_string(probe.Remote.Ready)
				+ std::to_string(probe.Local.Available) + std::to_string(probe.Remote.Available) + std::to_string(probe.Both_Ready()) + std::to_string(probe.Starting())
				+ std::to_string(probe.Launch_Ready()) + std::to_string(probe.Compatible()) + std::to_string(wireReady);
			for (auto const & host : probe.Hosts) value += std::to_string(host.Address.Get_IP());
			return value;
		};
		for (;;) {
			tick();
			if (probe.Launch_Ready()) {
				if (Android_LAN_Launch(std::move(ownedProbe))) return true;
				Android_LAN_Reset(); menu.Message("LAN launch failed", "Could not prepare the selected match."); return false;
			}
			std::vector<Choice> choices;
			std::vector<std::string> lines;
			if (editing) {
				lines = {"Name: " + draft, "Up to 23 letters or numbers"};
				std::string keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
				for (int i = 0; i < int(keys.size()); ++i)
					choices.push_back({200 + i, std::string(1, keys[i]), 110 + (i % 9) * 47, 130 + (i / 9) * 43, 42});
				choices.insert(choices.end(), {{10, "Delete", 110, 320, 130}, {11, "Save Name", 255, 320, 130, !draft.empty()}, {12, "Cancel", 400, 320, 130}});
			} else {
				lines = {probe.Status};
				if (probe.Connected) {
					lines.push_back("Peer: " + probe.Remote.Name + " / " + probe.Remote.Side);
					lines.push_back(probe.Remote.Ready ? "Peer: Ready" : "Peer: Not ready");
					lines.push_back(wireFailed ? "Cannot open gameplay port. Back and retry." :
						!wireReady ? "Checking gameplay connection..." :
						!probe.Local.Available ? "Map or peer side is missing locally." :
						!probe.Compatible() ? "Checking content: map/rules must match." :
						probe.Starting() ? "Starting match - waiting for peer..." :
						probe.Both_Ready() ? "Both ready - host can start the match." : "Confirm the setup, then tap Ready.");
				} else lines.push_back("1v1: 10000 credits, bases, no AI or crates.");
				choices = {{1, "Back", 110, 395, mode == 1 ? 120 : 200},
					{9, "Connection Help", mode == 1 ? 370 : 330, 395, mode == 1 ? 160 : 200, !probe.Starting()}};
				if (mode == 1) choices.push_back({8, "Host IP", 240, 395, 120, !probe.Starting()});
				if (mode == 1 || probe.Connected) {
					auto found = std::find(maps.begin(), maps.end(), probe.Map);
					std::string mapName = found == maps.end() ? probe.Map : names[size_t(found - maps.begin())];
					choices.insert(choices.end(), {{2, "Name: " + player, 110, 180, 420, !probe.Starting()},
						{3, "Side: " + sides[side], 110, 225, 420, !probe.Starting()},
						{4, "Map: " + mapName.substr(0, 42), 110, 270, 420, mode == 1 && !probe.Starting()},
						{7, "Credits: " + std::to_string(probe.Credits), 110, 315, 420, mode == 1 && !probe.Starting()},
						{5, probe.Local.Ready ? "Not Ready" : "Ready", 110, 360, 200, probe.Connected && probe.Local.Available && probe.Compatible() && !probe.Starting()},
						{6, "Start Game", 330, 360, 200, mode == 1 && probe.Both_Ready() && !probe.Starting()}});
				} else for (size_t i = 0; i < probe.Hosts.size(); ++i)
					choices.push_back({100 + int(i), "Join " + std::string(probe.Hosts[i].Address.As_String()), 130, 155 + int(i) * 43, 380});
			}
			std::string before = state();
			int result = menu.Show(editing ? "Player Name" : internet ? "Internet - Direct IP" : "LAN Match", choices, lines, false,
				[&]() { tick(); return probe.Launch_Ready() || (!editing && before != state()); });
			if (editing) {
				if (result >= 200 && result < 236 && draft.size() < 23) draft += "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[result - 200];
				else if (result == 10 && !draft.empty()) draft.pop_back();
				else if (result == 11) { player = draft; probe.Set_Player(player, sides[side]); editing = false; }
				else if (result == 12 || result == 0) editing = false;
			} else if (result == 0 || result == 1) { Android_LAN_Reset(); break; }
			else if (result == 9) {
				if (!Android_Open_Connection_Help()) menu.Message("Connection Help", "Could not open help.");
			}
			else if (result == 8) {
				if (!Android_Open_Host_Address()) menu.Message("Host IP", "Could not open address details.");
			}
			else if (result == 2) { draft = player; editing = true; }
			else if (result == 3) { side = (side + 1) % sides.size(); probe.Set_Player(player, sides[side]); }
			else if (result == 4 && mode == 1) { selected = (selected + 1) % maps.size(); probe.Set_Map(maps[selected], std::random_device{}()); }
			else if (result == 7 && mode == 1) probe.Set_Credits(probe.Credits >= 10000 ? 2500 : probe.Credits + 500);
			else if (result == 5) probe.Set_Ready(!probe.Local.Ready);
			else if (result == 6) probe.Request_Start();
			else if (result >= 100 && result < 105) probe.Join(result - 100);
		}
	}
}


std::vector<std::string> Wrap(std::string text, size_t width = 49)
{
	std::replace(text.begin(), text.end(), '@', '\n');
	std::istringstream paragraphs(text);
	std::vector<std::string> lines;
	std::string paragraph;
	while (std::getline(paragraphs, paragraph)) {
		std::istringstream words(paragraph);
		std::string word, line;
		while (words >> word) {
			if (!line.empty() && line.size() + word.size() + 1 > width) {
				lines.push_back(line);
				line.clear();
			}
			if (!line.empty()) line += ' ';
			line += word;
		}
		lines.push_back(line);
	}
	return lines;
}

void Briefing(Menu & menu)
{
	std::string text = Scen->BriefingText;
	char filename[32] = "MISSION.INI";
	if (Scen->RequiredAddOn > ADDON_BASE_GAME) snprintf(filename, sizeof(filename), "MISSION%d.INI", Scen->RequiredAddOn);
	CCFileClass file(filename);
	CCINIClass ini;
	char voiceover[256] = {};
	if (ini.Load(file, false)) {
		ini.Get_String(Scen->ScenarioName, "VoiceOver", "", voiceover, sizeof(voiceover));
		if (text.empty()) {
			char section[256] = {}, briefing[8192] = {};
			ini.Get_String(Scen->ScenarioName, "Briefing", "", section, sizeof(section));
			if (section[0]) ini.Get_TextBlock(section, briefing, sizeof(briefing));
			text = briefing;
		}
	}
	AudioHandle const narration = voiceover[0]
		? AudioEngine.Open_Stream(voiceover, AUDIO_GROUP_SPEECH, 1.0f, false) : AudioHandle();
	if (text.empty()) text = "No briefing text is available for this mission.";
	auto lines = Wrap(text);
	size_t page = 0;
	for (;;) {
		size_t const end = std::min(page + 14, lines.size());
		int const result = menu.Show("Restate Briefing", {{1, "Previous", 110, 390, 125, page != 0},
			{2, "Next", 255, 390, 125, end < lines.size()}, {3, "Options Menu", 400, 390, 130}},
			std::vector<std::string>(lines.begin() + page, lines.begin() + end));
		if (result == 1) page -= 14;
		else if (result == 2) page += 14;
		else { AudioEngine.Stop_Stream(narration); return; }
	}
}

struct SaveEntry {
	std::string Filename, Description;
	std::filesystem::file_time_type Time;
	bool Valid;
};

std::vector<SaveEntry> Saves()
{
	std::vector<SaveEntry> result;
	std::error_code error;
	std::filesystem::directory_iterator it(std::filesystem::path(Saved_Game_Name("")).parent_path(), error), end;
	for (; !error && it != end; it.increment(error)) {
		if (!it->is_regular_file(error)) continue;
		std::string extension = it->path().extension().string();
		if (strcasecmp(extension.c_str(), ".sav") != 0) continue;
		std::string filename = it->path().filename().string();
		SaveVersionInfo info;
		bool const readable = Get_Savefile_Info(filename.c_str(), &info);
		bool const valid = readable && info.Get_Internal_Version() == int(ExpectedGameVersion)
			&& (info.Get_Game_Type() == GAME_NORMAL || info.Get_Game_Type() == GAME_SKIRMISH);
		result.push_back({filename, readable ? info.Get_Scenario_Description() : "Unreadable save", it->last_write_time(error), valid});
	}
	std::sort(result.begin(), result.end(), [](SaveEntry const & a, SaveEntry const & b) { return a.Time > b.Time; });
	return result;
}

bool Enter_Save_Name(Menu & menu, std::string & name)
{
	name = name.substr(0, 32);
	bool lower = false;
	for (;;) {
		std::string const keys = lower ? "abcdefghijklmnopqrstuvwxyz0123456789" : "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		std::vector<Choice> choices;
		for (int i = 0; i < int(keys.size()); ++i)
			choices.push_back({200 + i, std::string(1, keys[i]), 110 + (i % 9) * 47, 130 + (i / 9) * 40, 42});
		bool const valid = name.find_first_not_of(' ') != std::string::npos;
		choices.insert(choices.end(), {{1, "Space", 110, 300, 100}, {2, "Delete", 215, 300, 100},
			{3, "Clear", 320, 300, 100}, {4, lower ? "ABC" : "abc", 425, 300, 100},
			{5, "Save", 150, 370, 150, valid}, {6, "Cancel", 340, 370, 150}});
		int const result = menu.Show("Name Your Save", choices, {name, "Up to 32 characters"});
		if (result >= 200 && result < 236 && name.size() < 32) name += keys[result - 200];
		else if (result == 1 && name.size() < 32) name += ' ';
		else if (result == 2 && !name.empty()) name.pop_back();
		else if (result == 3) name.clear();
		else if (result == 4) lower = !lower;
		else if (result == 5 && valid) {
			name = name.substr(name.find_first_not_of(' '));
			name.erase(name.find_last_not_of(' ') + 1);
			return true;
		} else if (result == 0 || result == 6) return false;
	}
}

// A load can replace the engine surfaces; callers must not restore an old surface pointer.
bool Save_Menu(Menu & menu, int mode)
{
	size_t page = 0;
	for (;;) {
		auto saves = Saves();
		if (page >= saves.size()) page = 0;
		std::vector<Choice> choices;
		if (mode == 1) choices.push_back({1, "Create New Save", 130, 88, 380});
		for (size_t i = page; i < std::min(page + 5, saves.size()); ++i) {
			std::string label = saves[i].Description + "  [" + saves[i].Filename + "]";
			if (label.size() > 43) label = label.substr(0, 40) + "...";
			choices.push_back({100 + int(i - page), label, 110, 130 + int(i - page) * 44, 420, mode != 2 || saves[i].Valid});
		}
		choices.push_back({2, "Previous", 110, 390, 125, page != 0});
		choices.push_back({3, "Next", 255, 390, 125, page + 5 < saves.size()});
		choices.push_back({4, "Options Menu", 400, 390, 130});
		int const selected = menu.Show(mode == 1 ? "Save Game" : mode == 2 ? "Load Game" : "Delete Game", choices,
			saves.empty() && mode != 1 ? std::vector<std::string>{"No saved games found."} : std::vector<std::string>{});
		if (selected == 0 || selected == 4) return false;
		if (selected == 2) { page -= 5; continue; }
		if (selected == 3) { page += 5; continue; }
		std::string filename;
		if (selected == 1) {
			for (unsigned slot = 1; slot != 100000; ++slot) {
				char name[32];
				snprintf(name, sizeof(name), "ANDROID%05u.SAV", slot);
				std::error_code error;
				if (!std::filesystem::exists(Saved_Game_Name(name), error) && !error) { filename = name; break; }
			}
			if (filename.empty()) { menu.Message("Save failed", "No free save filename is available."); continue; }
		} else {
			filename = saves[page + selected - 100].Filename;
			if (!menu.Confirm(mode == 1 ? "Overwrite this save?" : mode == 2 ? "Load this save?" : "Delete this save?", filename.c_str())) continue;
		}
		if (mode == 1) {
			std::string name = selected == 1 ? Scen->Description : saves[page + selected - 100].Description;
			if (!Enter_Save_Name(menu, name)) continue;
			bool const saved = SaveManager.Request_Save_Game(filename.c_str(), name.c_str(), true, SaveManagerClass::NoticeType::Requested);
			menu.Message(saved ? "Game saved" : "Save failed", name.c_str());
		} else if (mode == 2) {
			ScenarioActive = false;
      TacticalActive = false;
      if (Load_Game(filename.c_str())) return true;
			menu.Message("Load failed", "This save could not be loaded.");
		} else {
			std::error_code error;
			bool const removed = std::filesystem::remove(Saved_Game_Name(filename.c_str()), error);
			menu.Message(removed && !error ? "Save deleted" : "Delete failed", filename.c_str());
		}
	}
}

std::string Toggle(char const * name, bool enabled)
{
	return std::string(name) + (enabled ? ": On" : ": Off");
}

void Music(Menu & menu)
{
	std::vector<int> tracks;
	for (int i = 0; i < Theme.Max_Themes(); ++i) if (Theme.Is_Allowed(ThemeType(i))) tracks.push_back(i);
	size_t page = 0;
	for (;;) {
		std::vector<Choice> choices;
		for (size_t i = page; i < std::min(page + 6, tracks.size()); ++i)
			choices.push_back({100 + int(i - page), Theme.Full_Name(ThemeType(tracks[i])), 130, 85 + int(i - page) * 42, 380});
		choices.insert(choices.end(), {{1, "Previous", 110, 348, 125, page > 0}, {2, "Next", 255, 348, 125, page + 6 < tracks.size()},
			{3, "Stop Music", 400, 348, 130}, {4, "Back", 220, 396, 200}});
		int const result = menu.Show("Music Tracks", choices);
		if (result == 1) page -= 6;
		else if (result == 2) page += 6;
		else if (result == 3) Theme.Stop();
		else if (result >= 100) Theme.Queue_Song(ThemeType(tracks[page + result - 100]));
		else return;
	}
}

void Sound(Menu & menu)
{
	for (;;) {
		std::vector<Choice> choices;
		float const volumes[] = {Options.ScoreVolume, Options.SoundVolume, Options.VoiceVolume};
		char const * names[] = {"Music", "Sound Effects", "Voice"};
		for (int i = 0; i < 3; ++i) {
			choices.push_back({10 + i * 2, "-", 115, 90 + i * 48, 42});
			choices.push_back({30 + i, std::string(names[i]) + ": " + std::to_string(int(volumes[i] * 100 + 0.5f)) + "%", 170, 90 + i * 48, 300, false});
			choices.push_back({11 + i * 2, "+", 483, 90 + i * 48, 42});
		}
		choices.insert(choices.end(), {{1, Toggle("Shuffle", Options.IsScoreShuffle), 115, 240, 195},
			{2, Toggle("Repeat", Options.IsScoreRepeat), 330, 240, 195}, {3, "Music Tracks", 190, 295, 260}, {4, "Game Controls", 190, 395, 260}});
		int const result = menu.Show("Sound", choices);
		if (result == 1) Options.Set_Shuffle(!Options.IsScoreShuffle);
		else if (result == 2) Options.Set_Repeat(!Options.IsScoreRepeat);
		else if (result == 3) Music(menu);
		else if (result >= 10 && result <= 15) {
			int const index = (result - 10) / 2;
			float const value = std::clamp(volumes[index] + ((result & 1) ? 0.1f : -0.1f), 0.0f, 1.0f);
			if (index == 0) Options.Set_Score_Volume(value, false);
			if (index == 1) Options.Set_Sound_Volume(value, false);
			if (index == 2) Options.Set_Voice_Volume(value, false);
		} else { Options.Save_Settings(); return; }
	}
}

int Pick_Key(Menu & menu)
{
	int page = 0, modifiers = 0;
	for (;;) {
		std::vector<Choice> choices;
		std::string const keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		for (int i = 0; i < 18; ++i) {
			int const key = page == 0 ? keys[i] : page == 1 ? keys[18 + i] : i < 12 ? VK_F1 + i : 0;
			if (!key) continue;
			std::string label = page == 2 ? "F" + std::to_string(i + 1) : std::string(1, char(key));
			choices.push_back({key + 100, label, 115 + (i % 6) * 69, 125 + (i / 6) * 45, 62});
		}
		choices.insert(choices.end(), {{1, Toggle("Shift", modifiers & KN_SHIFT_BIT), 115, 80, 130},
			{2, Toggle("Ctrl", modifiers & KN_CTRL_BIT), 255, 80, 130}, {3, Toggle("Alt", modifiers & KN_ALT_BIT), 395, 80, 130},
			{4, "More Keys", 115, 300, 195}, {5, "Unassign", 330, 300, 195}, {6, "Cancel", 220, 395, 200}});
		int const result = menu.Show("Choose Keyboard Shortcut", choices);
		if (result == 1) modifiers ^= KN_SHIFT_BIT;
		else if (result == 2) modifiers ^= KN_CTRL_BIT;
		else if (result == 3) modifiers ^= KN_ALT_BIT;
		else if (result == 4) page = (page + 1) % 3;
		else if (result == 5) return 0;
		else if (result >= 100) return (result - 100) | modifiers;
		else return -1;
	}
}

std::string Android_Key_Name(int key)
{
        if (!key) return "Unassigned";

        std::string text;
        if (key & KN_ALT_BIT) text += "Alt+";
        if (key & KN_CTRL_BIT) text += "Ctrl+";
        if (key & KN_SHIFT_BIT) text += "Shift+";

        int const base = key & 0xFF;
        if ((base >= 'A' && base <= 'Z') || (base >= '0' && base <= '9')) {
                text += char(base);
        } else if (base >= VK_F1 && base <= VK_F12) {
                text += "F" + std::to_string(base - VK_F1 + 1);
        } else {
                text += "?";
        }

        return text;
}

std::string Command_Key_Name(CommandClass const * command)
{
        for (int i = 0; i < HotkeyCommands.Count(); ++i) {
                if (HotkeyCommands.Fetch_By_Position(i) == command) {
                        return Android_Key_Name(HotkeyCommands.Fetch_ID_By_Position(i));
                }
        }
        return "Unassigned";
}
void Keyboard_Menu(Menu & menu)
{
	int page = 0;
	for (;;) {
		std::vector<Choice> choices;
		for (int i = page; i < std::min(page + 6, AllCommands.Count()); ++i) {
			std::string label = AllCommands[i]->Get_Display_Name();
			if (label.size() > 44) label = label.substr(0, 41) + "...";
			choices.push_back({100 + i - page, label, 110, 90 + (i - page) * 43, 420});
		}
		choices.insert(choices.end(), {{1, "Previous", 110, 360, 125, page > 0}, {2, "Next", 255, 360, 125, page + 6 < AllCommands.Count()},
			{3, "Game Controls", 400, 360, 130}});
		int const result = menu.Show("Keyboard Commands", choices);
		if (result == 1) page -= 6;
		else if (result == 2) page += 6;
		else if (result >= 100) {
			CommandClass const * command = AllCommands[page + result - 100];
			int const key = Pick_Key(menu);
			if (key < 0) continue;
			if (key && HotkeyCommands.Is_Present(key) && HotkeyCommands[key] != command
				&& !menu.Confirm("Replace existing shortcut?", HotkeyCommands[key]->Get_Display_Name())) continue;
			for (int i = HotkeyCommands.Count() - 1; i >= 0; --i)
				if (HotkeyCommands.Fetch_By_Position(i) == command) HotkeyCommands.Remove_Index(HotkeyCommands.Fetch_ID_By_Position(i));
			if (key) { HotkeyCommands.Remove_Index(key); HotkeyCommands.Add_Index(key, command); }
			CCINIClass ini;
			for (int i = 0; i < HotkeyCommands.Count(); ++i)
				ini.Put_Int("Hotkey", HotkeyCommands.Fetch_By_Position(i)->Get_Unique_Name(), HotkeyCommands.Fetch_ID_By_Position(i));
			CCFileClass file("KEYBOARD.INI");
			if (!ini.Save(file, false)) menu.Message("Keyboard", "Could not save keyboard settings.");
		} else return;
	}
}

void Touch_Controls_Guide(Menu & menu)
{
        for (;;) {
                int const result = menu.Show("Controls Guide", {
                        {1, "Modern Touch", 110, 150, 420},
                        {2, "Original Touch (disabled)", 110, 205, 420, false},
                        {3, "Back", 220, 390, 200}},
                        {"Choose a control scheme to see how it works."});

                if (result == 1) {
                        menu.Show("Modern Touch", {
                                {1, "Back", 220, 390, 200}},
                                {"Tap unit: Select",
                                 "Tap ground: Move selected units",
                                 "Tap enemy: Attack",
                                 "Drag, then release: Box-select units",
                                 "Double-tap unit: Select same type",
                                 "Second tap + drag: Pan camera",
                                 "Pinch: Zoom battlefield",
                                 "Two-finger tap: Right click",
                                 "Keep still; lift both within 0.25 sec",
                                 "Right click uses first finger position",
                                 "Hold production icon 0.5 sec, release:",
                                 "Pause build; repeat to cancel",
                                 "Hold ground 0.5 sec, release:",
                                 "Attack-move (without dragging)"});
                } else if (result == 2) {
                        menu.Show("Original Touch", {
                                {1, "Back", 220, 390, 200}},
                                {"Touch: Left click",
                                 "Touch + drag: Left-click drag",
                                 "Double-tap: Right click",
                                 "Uses the original mouse-style controls."});
                } else {
                        return;
                }
        }
}

void Touch_Controls(Menu & menu)
{
	for (;;) {
		int const speed = AndroidControls.PanSpeed.load();
		int const delay = AndroidControls.DoubleTapMilliseconds.load();
		int const result = menu.Show("Touch Controls", {
			{1, AndroidControls.ControlScheme.load() == ANDROID_CONTROL_MODERN ? "Scheme: Modern Touch" : "Scheme: Original Touch", 110, 86, 420},
			{2, Toggle("Double-tap gestures", AndroidControls.DoubleTapRightClick.load()), 110, 130, 420},
			{3, Toggle("Selection box", AndroidControls.SelectionBox.load()), 110, 174, 205},
			{4, Toggle("Touch edge scroll", AndroidControls.EdgeScrolling.load()), 325, 174, 205},
			{5, "-", 110, 218, 42, speed > 1},
			{30, "Camera speed: " + std::to_string(speed), 160, 218, 320, false},
			{6, "+", 488, 218, 42, speed < 16},
			{7, "-", 110, 262, 42, delay > 150},
			{31, "Double-tap: " + std::to_string(delay) + " ms", 160, 262, 320, false},
			{8, "+", 488, 262, 42, delay < 500},
			{9, "Reset Controls", 110, 330, 205}, {10, "Back", 325, 330, 205}});
		if (result == 1) {
int const scheme = menu.Show("Control Schemes", {
{2, AndroidControls.ControlScheme.load() == ANDROID_CONTROL_MODERN ? "Modern Touch (active)" : "Modern Touch", 110, 150, 420},
{1, "Original Touch (disabled)", 110, 194, 420, false},
{3, "Classic Cursor - coming later", 110, 238, 420, false},
{4, "Advanced Touch - coming later", 110, 282, 420, false},
{5, "Controls Guide", 110, 336, 205},
{6, "Back", 325, 336, 205}},
{"Modern Touch is the only enabled scheme."});

if (scheme == 2) {
AndroidControls.ControlScheme = ANDROID_CONTROL_MODERN;
} else if (scheme == 5) {
Touch_Controls_Guide(menu);
continue;
} else {
continue;
}

if (!Android_Save_Control_Settings())
menu.Message("Touch Controls", "Settings active, but could not save to storage.");
continue;
}
if (result == 2) AndroidControls.DoubleTapRightClick = !AndroidControls.DoubleTapRightClick.load();
		else if (result == 3) AndroidControls.SelectionBox = !AndroidControls.SelectionBox.load();
		else if (result == 4) AndroidControls.EdgeScrolling = !AndroidControls.EdgeScrolling.load();
		else if (result == 5 || result == 6) AndroidControls.PanSpeed = std::clamp(speed + (result == 6 ? 1 : -1), 1, 16);
		else if (result == 7 || result == 8) AndroidControls.DoubleTapMilliseconds = std::clamp(delay + (result == 8 ? 50 : -50), 150, 500);
		else if (result == 9) {
			if (!menu.Confirm("Reset touch controls?", "Restore the default Modern Touch controls?")) continue;
			Android_Reset_Control_Settings();
		} else return;
		if (!Android_Save_Control_Settings()) menu.Message("Touch Controls", "Settings active, but could not save to storage.");
	}
}

void Support(Menu & menu)
{
	for (;;) {
		int const result = menu.Show("Support OpenTS-A", {
			{1, "Ko-fi", 170, 285, 300},
			{2, "GitHub Sponsors", 170, 335, 300},
			{3, "Back", 170, 390, 300}}, {
			"Support development by GEARS0FUMP45.",
			"Donations are optional. All features stay free.",
			"Support does not purchase game files or content.",
			"Links open in your browser.",
			"Unofficial; not affiliated with Electronic Arts."});
		if (result != 1 && result != 2) return;
		if (!Android_Open_Url(result == 1 ? AndroidSupport::KoFi : AndroidSupport::Sponsors))
			menu.Message("Support OpenTS-A", "Could not open a browser. Please try again later.");
	}
}

void About(Menu & menu)
{
	for (;;) {
		int const result = menu.Show("About OpenTS-A", {
			{1, "Support Development", 170, 290, 300},
			{2, "OpenTS Project", 170, 335, 300},
			{3, "Back", 170, 390, 300}}, {
			"Android port by GEARS0FUMP45.",
			"Based on OpenTS by the OpenTS developers.",
			"Tiberian Sun was created by Westwood Studios",
			"and published by Electronic Arts.",
			"Unofficial; not affiliated with Electronic Arts."});
		if (result == 1) Support(menu);
		else if (result == 2) {
			if (!Android_Open_Url(AndroidSupport::Upstream))
				menu.Message("About OpenTS-A", "Could not open a browser. Please try again later.");
		} else return;
	}
}

void Controls(Menu & menu)
{
	for (;;) {
		std::vector<Choice> choices;
		int const values[] = {6 - Options.GameSpeed, 6 - Options.ScrollRate, Options.DetailLevel};
		char const * names[] = {"Game Speed", "Scroll Rate", "Visual Details"};
		for (int i = 0; i < 3; ++i) {
			choices.push_back({10 + i * 2, "-", 115, 86 + i * 44, 42, values[i] > 0});
			choices.push_back({30 + i, std::string(names[i]) + ": " + std::to_string(values[i] + 1), 170, 86 + i * 44, 300, false});
			choices.push_back({11 + i * 2, "+", 483, 86 + i * 44, 42, values[i] < (i == 2 ? 2 : 6)});
		}
		choices.insert(choices.end(), {{1, Toggle("Sidebar Text", Options.SidebarCameoText), 110, 230, 205},
			{2, Toggle("Target Lines", Options.ActionLines), 325, 230, 205}, {3, Toggle("Tooltips", Options.ToolTips), 110, 273, 205},
			{4, Toggle("Scroll Coasting", Options.ScrollMethod == 0), 325, 273, 205}, {5, "Touch Controls", 210, 316, 220},
			{9, "About OpenTS-A", 210, 354, 220},
			{6, "Sound", 110, 395, 125, AudioEngine.Is_Available()}, {7, "Keyboard", 255, 395, 125}, {8, "Options Menu", 400, 395, 130}});
		int const result = menu.Show("Game Controls", choices);
		if (result == 1) { Options.SidebarCameoText = !Options.SidebarCameoText; Map.Toggle_Cameo_Text(Options.SidebarCameoText); }
		else if (result == 2) { Options.ActionLines = !Options.ActionLines; TechnoClass::Set_Action_Lines(Options.ActionLines); }
		else if (result == 3) { Options.ToolTips = !Options.ToolTips; if (ToolTips) ToolTips->Activate(Options.ToolTips); }
		else if (result == 4) Options.ScrollMethod = Options.ScrollMethod == 0 ? 1 : 0;
		else if (result == 5) Touch_Controls(menu);
		else if (result == 6) Sound(menu);
		else if (result == 7) Keyboard_Menu(menu);
		else if (result == 9) About(menu);
		else if (result >= 10 && result <= 15) {
			int const delta = (result & 1) ? 1 : -1;
			if (result < 12) {
				int const speed = std::clamp(Options.GameSpeed - delta, 0, 6);
				if (Session.Type == GAME_NORMAL || Session.Type == GAME_SKIRMISH) Options.GameSpeed = speed;
				else OutList.push_back(EventClass(PlayerPtr->HeapID, EventClass::GAMESPEED, speed));
			} else if (result < 14) Options.ScrollRate = std::clamp(Options.ScrollRate - delta, 0, 6);
			else { Options.DetailLevel = std::clamp(Options.DetailLevel + delta, 0, 2); if (ScenarioActive) Map.Reinit_Cell_Drawers(); }
		} else { Options.Save_Settings(); return; }
	}
}

}

namespace {

int Choose_Menu_Item(Menu & menu, char const * title, std::vector<std::string> const & names)
{
	int page = 0;
	for (;;) {
		std::vector<Choice> choices;
		for (int i = page; i < std::min(page + 6, int(names.size())); ++i) {
			choices.push_back({100 + i - page, names[i], 110, 85 + (i - page) * 45, 420});
		}
		choices.insert(choices.end(), {{1, "Previous", 110, 390, 125, page > 0},
			{2, "Next", 255, 390, 125, page + 6 < int(names.size())}, {3, "Back", 400, 390, 130}});
		int const result = menu.Show(title, choices);
		if (result >= 100) return page + result - 100;
		if (result == 1) page -= 6;
		else if (result == 2) page += 6;
		else return -1;
	}
}

bool Main_Campaign(Menu & menu)
{
	std::vector<int> ids;
	std::vector<std::string> names;
	for (int i = 0; i < Campaigns.Count(); ++i) {
		CampaignClass const * campaign = Campaigns[i];
		if (campaign == nullptr) continue;
		bool const available = Addon_Enabled(ADDON_ANY)
			? campaign->RequiredAddon != ADDON_BASE_GAME && Addon_Enabled(AddonType(campaign->RequiredAddon))
			: campaign->RequiredAddon == ADDON_BASE_GAME;
		if (available && CCFileClass(campaign->ScenarioName).Is_Available()) {
			ids.push_back(i);
			names.push_back(campaign->Description);
		}
	}
	if (names.empty()) { menu.Message("New Campaign", "No installed campaigns were found."); return false; }
	for (;;) {
		int const selected = Choose_Menu_Item(menu, "New Campaign", names);
		if (selected < 0) return false;
		int const difficulty = menu.Show("Difficulty", {{1, "Easy", 195, 130, 250},
			{2, "Normal", 195, 180, 250}, {3, "Hard", 195, 230, 250}, {4, "Back", 195, 390, 250}});
		if (difficulty < 1 || difficulty > 3) continue;
		new (&Environment) EnvironmentClass;
		Options.Difficulty = difficulty - 1;
		Scen->Campaign = CampaignType(ids[selected]);
		Session.Type = GAME_NORMAL;
		Session.LoadGame = false;
		return true;
	}
}

bool Main_Skirmish(Menu & menu)
{
	Session.Type = GAME_SKIRMISH;
	Session.Read_MultiPlayer_Settings();
	Prepare_Side_Roster();
	Session.Read_Scenario_Descriptions();
	std::vector<int> maps, houses;
	std::vector<std::string> names;
	for (int i = 0; i < Session.Scenarios.Count(); ++i) {
		if (CCFileClass(Session.Scenarios[i]->Get_Filename()).Is_Available() && RandomMapWaypointCount(i) >= 2) {
			maps.push_back(i);
			names.push_back(Session.Scenarios[i]->Description());
		}
	}
	for (int i = 0; i < HouseTypes.Count(); ++i) {
		if (HouseTypes[i]->IsMultiplay) houses.push_back(i);
	}
	if (maps.empty() || houses.empty()) { menu.Message("Skirmish", "No playable skirmish maps or sides were found."); return false; }
	int selected = 0, side = 0;
	Session.Options.AIPlayers = std::clamp(Session.Options.AIPlayers, 1, 7);
	Session.Options.AIDifficulty = DiffType(std::clamp(int(Session.Options.AIDifficulty), 0, 2));
	Session.Options.Credits = std::clamp(Session.Options.Credits, 2500, 10000);
	BuildLevel = std::clamp(BuildLevel, 1, 10);
	Session.Options.Bases = true;
	for (;;) {
		char const * difficulty[] = {"Easy", "Normal", "Hard"};
		int const result = menu.Show("Skirmish", {
			{1, "Map: " + names[selected], 110, 85, 420},
			{2, std::string("Side: ") + HouseTypes[houses[side]]->GivenName.c_str(), 110, 130, 205},
			{3, "AI Players: " + std::to_string(Session.Options.AIPlayers), 325, 130, 205},
			{4, std::string("AI: ") + difficulty[Session.Options.AIDifficulty], 110, 175, 205},
			{5, "Credits: " + std::to_string(Session.Options.Credits), 325, 175, 205},
			{6, "Tech Level: " + std::to_string(BuildLevel), 110, 220, 205},
			{7, Toggle("Crates", Session.Options.Goodies), 325, 220, 205},
			{8, Toggle("Short Game", Session.Options.ShortGame), 110, 265, 205},
			{9, Toggle("Fog of War", Session.Options.FogOfWar), 325, 265, 205},
			{10, "Starting Units: " + std::to_string(Session.Options.UnitCount), 110, 310, 205},
			{11, "Game Speed: " + std::to_string(7 - std::clamp(Session.Options.GameSpeed, 0, 6)), 325, 310, 205},
			{20, "Start Game", 130, 390, 175}, {21, "Cancel", 335, 390, 175}});
		if (result == 1) { int const map = Choose_Menu_Item(menu, "Select Map", names); if (map >= 0) selected = map; }
		else if (result == 2) side = (side + 1) % houses.size();
		else if (result == 3) Session.Options.AIPlayers = Session.Options.AIPlayers % 7 + 1;
		else if (result == 4) Session.Options.AIDifficulty = DiffType((Session.Options.AIDifficulty + 1) % 3);
		else if (result == 5) Session.Options.Credits = Session.Options.Credits >= 10000 ? 2500 : Session.Options.Credits + 500;
		else if (result == 6) BuildLevel = BuildLevel % 10 + 1;
		else if (result == 7) Session.Options.Goodies = !Session.Options.Goodies;
		else if (result == 8) Session.Options.ShortGame = !Session.Options.ShortGame;
		else if (result == 9) Session.Options.FogOfWar = !Session.Options.FogOfWar;
		else if (result == 10) Session.Options.UnitCount = Session.Options.UnitCount >= SessionClass::CountMax[1] ? SessionClass::CountMin[1] : Session.Options.UnitCount + 1;
		else if (result == 11) Session.Options.GameSpeed = (std::clamp(Session.Options.GameSpeed, 0, 6) + 6) % 7;
		else if (result == 20) {
			int const map = maps[selected];
			if (RandomMapWaypointCount(map) < Session.Options.AIPlayers + 1) {
				menu.Message("Skirmish", "Choose fewer AI players or a larger map.");
				continue;
			}
			if (!Set_Scenario_Info_From_Index(map)) { menu.Message("Skirmish", "The selected map could not be opened."); continue; }
			Session.Options.ScenarioIndex = map;
			Session.House = HousesType(houses[side]);
			Session.ColorIdx = std::clamp(Session.ColorIdx, 0, 7);
			Session.PrefColor = Session.ColorIdx;
			for (int i = 0; i < Session.Players.Count(); ++i) delete Session.Players[i];
			Session.Players.Clear();
			NodeNameType * player = new NodeNameType{};
			snprintf(player->Name, sizeof(player->Name), "%s", Session.Handle[0] ? Session.Handle : "Player");
			player->Player.House = Session.House;
			player->Player.Color = Session.ColorIdx;
			player->Player.ProcessTime = -1;
			Session.Players.Add(player);
			Session.Options.AIPlayers = std::min(Session.Options.AIPlayers, 7);
			Session.Suspended = false;
			Session.LoadGame = false;
			Options.GameSpeed = Session.Options.GameSpeed;
			Session.Write_MultiPlayer_Settings();
			return true;
		} else return false;
	}
}

}

namespace { bool ImportButtonVisible = false; }

void Android_Show_Import_Button(bool visible) { ImportButtonVisible = visible; }

bool Android_Import_Button_Hit(int x, int y)
{
	x -= (VisibleSurface->Get_Width() - 640) / 2;
	return x >= 190 && x < 450 && y >= 46 && y < 76;
}

void Android_Draw_Import_Button(Surface * surface)
{
	if (!ImportButtonVisible) return;
	Surface * previous = LogicalSurface;
	LogicalSurface = surface;
	MenuButton button(200, "Import Game Files", TPF_BUTTON, 190 + (surface->Get_Width() - 640) / 2, 46, 260, 30);
	button.Draw_Me(true);
	LogicalSurface = previous;
}

bool Android_Has_Saved_Games(void)
{
	auto const saves = Saves();
	return std::any_of(saves.begin(), saves.end(), [](SaveEntry const & entry) { return entry.Valid; });
}

int Android_Main_Menu(void)
{
	static bool controls_loaded = false;
	if (!controls_loaded) { Android_Load_Control_Settings(); controls_loaded = true; }
	Session.Type = GAME_NORMAL;
	Android_LAN_Reset();
	std::string const networkError = Android_LAN_Take_Error();
	if (!networkError.empty()) { Menu notice; notice.Message("LAN match", networkError.c_str()); }
	ScenarioActive = false;
	TacticalActive = false;
	Session.Type = GAME_NORMAL;
	Session.LoadGame = false;
	NewMenuClass * shell = Get_New_Menu();
	// The initial -1 selects the Tiberian Sun / Firestorm page.
	for (;;) {
		int const selection = shell->Process_Game_Select();
		Menu menu;
		if (selection == NSEL_ANDROID_IMPORT) {
			if (!Android_Open_Game_Importer()) menu.Message("Import Game Files", "Could not open the Android importer.");
		} else if (selection == NSEL_START_NEW_GAME) {
			if (Main_Campaign(menu)) { Theme.Stop(); return 1; }
		} else if (selection == NSEL_LOAD_MISSION) {
			if (Save_Menu(menu, 2)) { Theme.Stop(); return 2; }
		} else if (selection == NSEL_SKIRMISH) {
			if (Main_Skirmish(menu)) { Theme.Stop(); return 3; }
			Session.Type = GAME_NORMAL;
		} else if (selection == NSEL_LAN || selection == NSEL_INTERNET) {
			if (Local_Network(menu, selection == NSEL_INTERNET)) { Theme.Stop(); return 3; }
		} else if (selection == NSEL_OPTIONS) {
			Controls(menu);
		} else if (selection == NSEL_INTRO) {
			if (CCFileClass("SIZZLE1.VQA").Is_Available()) Play_Movie("SIZZLE1.VQA");
			else menu.Message("Intro / Sneak Peek", "The intro movie is not installed.");
		} else if (selection == NSEL_EXIT) {
			return 0;
		} else if (selection == NSEL_OLD_MENU) {
			menu.Message("Main Menu", "Install GMENU.MIX and its NEWMENU.INI artwork.");
			return 0;
		}
	}
}



int Android_Game_Options_Menu(void)
{
	Menu menu;
	Surface * const previous = LogicalSurface;
	for (;;) {
		bool const solo = Session.Type == GAME_NORMAL || Session.Type == GAME_SKIRMISH;
		bool const present = solo && !Saves().empty();
		std::vector<Choice> choices = {{1, "Game Controls", 195, 86, 250},
			{2, "Restate Briefing", 195, 132, 250, Session.Type == GAME_NORMAL},
			{3, "Load Game", 195, 178, 250, present}, {4, "Save Game", 195, 224, 250, solo || SaveManager.Is_Multiplayer_Saving_Allowed()},
			{5, "Delete Game", 195, 270, 250, present}, {6, "Abort Mission", 195, 316, 250}, {8, "About OpenTS-A", 195, 354, 250}, {7, "Resume Mission", 195, 390, 250}};
		if (!solo) choices.erase(std::remove_if(choices.begin(), choices.end(), [](Choice const & c) { return c.ID == 2 || c.ID == 5; }), choices.end());
		for (size_t i = 0; i < choices.size(); ++i) {
			choices[i].X = 232; choices[i].Y = 130 + int(i) * 28; choices[i].Width = 176;
		}
		int const result = menu.Show("Options", choices, {}, true);
		if (result == 1) Controls(menu);
		else if (result == 2) Briefing(menu);
		else if (result == 8) About(menu);
		else if (result == 3) {
			if (Save_Menu(menu, 2)) { LogicalSurface = HiddenSurface; return IDC_LOAD_GAME; }
		} else if (result == 4) {
			if (solo) Save_Menu(menu, 1);
			else { OutList.push_back(EventClass(PlayerPtr->HeapID, EventClass::SAVEGAME)); LogicalSurface = previous; return IDC_SAVE_GAME; }
		} else if (result == 5) Save_Menu(menu, 3);
		else if (result == 6) {
			int const action = menu.Show("Abort Mission", {{1, "Abort Mission", 195, 150, 250},
				{2, Session.Type == GAME_NORMAL ? "Restart Mission" : "Surrender", 195, 205, 250,
					!PlayerPtr->IsDefeated && !PlayerPtr->IsToWin && !PlayerPtr->IsToLose && !PlayerPtr->IsToDie},
				{3, "Cancel", 195, 360, 250}}, {"Unsaved progress will be lost."});
			if ((action == 1 || action == 2) && menu.Confirm("Are you sure?", "Unsaved progress will be lost.")) {
				if (action == 1) Queue_Exit();
				else if (Session.Type == GAME_NORMAL) PlayerRestarts = true;
				else OutList.push_back(EventClass(PlayerPtr->HeapID, EventClass::DESTRUCT));
				LogicalSurface = previous;
				return IDCANCEL;
			}
		} else { LogicalSurface = previous; return IDOK; }
	}
}
#endif
