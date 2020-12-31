#include "common.hpp"
#include "base_tab.h"
#include "imgui.h"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "features.hpp"
#include <script_global.hpp>

namespace big
{
	void base_tab::render_base_tab()
	{
		const char* const demo_combo[]
		{
			"One",
			"Two",
			"Three"
		};
		const double min = 0., max = 10.;

		//If you want to add a new option, you have to first declare it in settings.h's default_options, otherwise, this code will crash when trying to access an option that does not exist in memory.
		auto font = ImGui::GetFont();
		font->Scale = 1.5f;
		ImGui::PushFont(font);
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "base_tab");
		//ImGui::Text("janmenu");
		ImGui::PopFont();
		font->Scale = 1;
		ImGui::PushFont(font);
		ImGui::PopFont();
		ImGui::SameLine();

		std::string name = "welcome, ";
		auto name2 = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
		name += name2;
		ImGui::Text(name.c_str());

		ImGui::Separator();

		ImGui::Checkbox("godmode", &features::godbool);
		ImGui::Checkbox("neverwanted", &features::never_wanted_bool);
		ImGui::Checkbox("off the radar", &features::off_the_radar_bool);
		if (ImGui::Button("teleport to wp")) {
			features::teleport_bool = true;

			//auto res = features::teleport(true);

			//if (res == 2) {
			//	ImGui::OpenPopup("nowp?");
			//}

			//if (ImGui::BeginPopupModal("nowp?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			//{
			//	ImGui::Text("no waypoint set. please set one before you continue\n\n");
			//	ImGui::Separator();

			//	//static int unused_i = 0;
			//	//ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

			///*	static bool dont_ask_me_next_time = false;
			//	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			//	ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
			//	ImGui::PopStyleVar();*/

			//	if (ImGui::Button("ok", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			//	ImGui::SetItemDefaultFocus();
			//	ImGui::SameLine();
			//	if (ImGui::Button("cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			//	ImGui::EndPopup();
			//}

			//Vector3 pos = HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(HUD::_GET_WAYPOINT_BLIP_SPRITE()));
		}
		if (ImGui::CollapsingHeader("player")) {
			ImGui::Checkbox("trigger", &features::aimbot_bool);
			ImGui::SameLine();
			const char* items[] = { "head", "pelvis", "foot (left)", "foot (right)" };
			static int item_current = 0;
			if (ImGui::Combo("trigger point", &item_current, items, ARRAYSIZE(items))) {
				std::map<PedBones, int> bones = {
				{ SKEL_Head, 0 },
				{ SKEL_Pelvis, 1 },
				{ SKEL_L_Foot ,2 } };

				for (auto it = bones.begin(); it != bones.end(); ++it)
					if (it->second == item_current)
						features::trigger_point = it->first;
			}
			ImGui::Checkbox("esp", &features::esp_bool);
			static int item_current2 = 1;

			const char* session_types[] = {
				"join public session",
				"new public session",
				"closed crew session",
				"crew session",
				"closed friend session",
				"find friend session",
				"solo session",
				"invite only session",
				"join crew session",
				"leave gta online"
			};

			ImGui::ListBox("", &item_current2, session_types, ARRAYSIZE(session_types), 5);
			//GAMEPLAY::SET_OVERRIDE_WEATHER
			ImGui::SameLine();
			if (ImGui::Button("create session type")) {
				std::map<int, int> sessions = { { 0, 0 },
				{ 1, 1 },
				{ 2,2 },
				{ 3,3 },
				{ 6,4},
				{ 9,5},
				{ 10,6 },
				{ 11,7},
				{ 12,8},
				{ -1, 9} };

				//	LOG(G3LOG_DEBUG) << "creating session: " << session_types[item_current] << " with identifier: " << identifier;

				g_fiber_pool->queue_job([]
					{
						auto identifier = 0;
						std::map<int, int> sessions = {
						{ 0, 0 },
						{ 1, 1 },
						{ 2,2 },
						{ 3,3 },
						{ 6,4},
						{ 9,5},
						{ 10,6 },
						{ 11,7},
						{ 12,8},
						{ -1, 9} };

						for (auto it = sessions.begin(); it != sessions.end(); ++it)
							if (it->second == item_current)
								identifier = it->first;

						//LOG(G3LOG_DEBUG) << "creating session: " << session_types[item_current] << " with identifier: " << identifier;

						features::join_session(identifier);
					});
			}
		}

		if (ImGui::CollapsingHeader("cayo perico heist")) {
			if (ImGui::Button("go to cayo perico")) {
				features::cayo_bool = true;
			}

			if (ImGui::Button("unlock all heist preps")) {
				features::unlock_heist_preps();
			}

			const char* newVehicles[] = {
				"alkonost",
				"annihilator2",
				"avisa",
				"brioso2",
				"dinghy5",
				"italirsx",
				"kosatka",
				"longfin",
				"manchez2",
				"patrolboat",
				"seasparrow2",
				"seasparrow3",
				"slamtruck",
				"squaddie",
				"toreador",
				"verus",
				"vetir",
				"veto2",
				"veto",
				"weevil",
				"winky"
			};

			//const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
			static int item_current = 1;
			ImGui::Separator();
			if (ImGui::Button("spawn selected vehicle")) {
				features::vehicle_model = newVehicles[item_current];
				features::spawn_vehicle_bool = true;
			}

			ImGui::ListBox("", &item_current, newVehicles, ARRAYSIZE(newVehicles), 9);

			/*	if (ImGui::Button("spawn selected vehicle")) {
					features::vehicle_model = newVehicles[item_current];
					features::spawn_vehicle_bool = true;
				}*/
		}

		//	if (ImGui::SliderInt("Int", (PINT)g_settings.options["demo int"].get<int64_t*>(), 0, 10))
		////		g_settings.save();
		//	if (ImGui::SliderScalar("Double", ImGuiDataType_Double, g_settings.options["demo double"].get<double*>(), &min, &max)) //JSON does not describe rational numbers as integer/float/double/etc types, it is just "number". See: https://nlohmann.github.io/json/features/types/
		//		g_settings.save();
		//	if (ImGui::Combo("Combo", (PINT)g_settings.options["demo combo"].get<int64_t*>(), demo_combo, sizeof(demo_combo) / sizeof(*demo_combo)))
		//		g_settings.save();

		if (ImGui::CollapsingHeader("vehicles")) {
			ImGui::Checkbox("always fix car", &features::car_always_fixed_bool);
			//	ImGui::Checkbox("vehicle godmode", &features::vehicle_god);

			if (ImGui::Button("Delete.."))
				ImGui::OpenPopup("Delete?");

			// Always center this window when appearing
			ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

			if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
				ImGui::Separator();

				//static int unused_i = 0;
				//ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

				static bool dont_ask_me_next_time = false;
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
				ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
				ImGui::PopStyleVar();

				if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::SetItemDefaultFocus();
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
				ImGui::EndPopup();
			}
		}

		if (ImGui::CollapsingHeader("player list")) {
			int player_count = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();

			if (player_count == 0) {
				ImGui::Text("this feature is only available in gta:o");
			}
			else {
				if (ImGui::BeginTable("##table1", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_ContextMenuInBody)) {
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					std::vector<Ped> peds;

					const char** player_names = new const char* [player_count];

					for (int i = 0; i < player_count; i++) {
						Ped ped = PLAYER::GET_PLAYER_PED(i);
						auto player_name = PLAYER::GET_PLAYER_NAME(i);
						peds.push_back(ped);

						player_names[i] = player_name;

						////Vector3 shitterPosition = ENTITY::GET_ENTITY_COORDS(shitterPed, false);
					}

					static int item_current = 1;

					ImGui::ListBox("", &item_current, player_names, player_count, 8);
					//	ImGui::PushItemWidth(-10);
					ImGui::TableSetColumnIndex(1);
					Vector3 player_pos = ENTITY::GET_ENTITY_COORDS(peds[item_current], false);
					ImGui::Text("selected player: %d", player_names[item_current]);
					ImGui::SameLine();
					ImGui::Text(player_names[item_current]);
					ImGui::Text("player pos: ");
					ImGui::SameLine();
					ImGui::Text(player_pos.to_string().c_str());

					if (ImGui::Button("teleport to player")) {
						Entity entity = PLAYER::PLAYER_PED_ID();
						ENTITY::SET_ENTITY_COORDS(entity, player_pos.x, player_pos.y, player_pos.z + 1, 0, 0, 0, 1);
					}
					ImGui::Checkbox("spectate plater", &features::spectate_player);

					NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(features::spectate_player, peds[item_current]);

					ImGui::EndTable();

					/*	for (auto i = 0; i < player_count; i++) {
							delete player_names[i];
						}*/

					delete[]player_names;
				}
			}

			////int player_count = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();

			////std::vector<Ped> peds;
			//////std::vector<const char*> player_names;
			//////const int player_count_init = player_count;

			////const char** player_names = new const char* [player_count];

			////for (int i = 0; i < player_count; i++) {
			////	Ped ped = PLAYER::GET_PLAYER_PED(i);
			////	auto player_name = PLAYER::GET_PLAYER_NAME(i);

			////	player_names[i] = player_name;

			////	////Vector3 shitterPosition = ENTITY::GET_ENTITY_COORDS(shitterPed, false);
			////}

			////if (ImGui::BeginTable("##table1", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_ContextMenuInBody)) {
			////	ImGui::TableNextRow();
			////	ImGui::TableSetColumnIndex(0);

			////	ImGui::EndTable();

			////	const char* newVehicles[] = {
			////	"alkonost",
			////	"annihilator2",
			////	"avisa",
			////	"brioso2",
			////	"dinghy5",
			////	"italirsx",
			////	"kosatka",
			////	"longfin",
			////	"manchez2",
			////	"patrolboat",
			////	"seasparrow2",
			////	"seasparrow3",
			////	"slamtruck",
			////	"squaddie",
			////	"toreador",
			////	"verus",
			////	"vetir",
			////	"veto2",
			////	"veto",
			////	"weevil",
			////	"winky"
			////	};

			////	static int item_current = 1;

			////	ImGui::ListBox("", &item_current, newVehicles, ARRAYSIZE(newVehicles), 8);
			////	ImGui::PushItemWidth(-10);
			////	ImGui::TableSetColumnIndex(1);

			////	ImGui::Text("selected player: ");
			////	ImGui::SameLine();
			////	//ImGui::Text(player_names[item_current]);
			/////*	int player_count = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();
			////	ImGui::Text("%d", player_count);*/
			////	ImGui::EndTable();
			////}

			//////delete player_names;
		}

		if (ImGui::CollapsingHeader("config")) {
		}

		if (ImGui::CollapsingHeader("recovery")) {
			static int value = INT_MAX - 1;
			ImGui::InputInt("", &value);
			ImGui::SameLine();
			if (ImGui::Button("set vehicle sell value")) {
				*script_global(99007).at(970).as<int*>() = value;
			}
			ImGui::SameLine();
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted("to use this feature properly follow these instructions: \n(1) order one of your vehicles \n(2) drive into the nearest LSC \n(3) go to the sell tab \n(4) click set vehicle sell value \n(5) sell the vehicle \n(6) the game will throw an error simply accept it. after you are in sp, restart your game.");
				ImGui::PopTextWrapPos();

				ImGui::EndTooltip();
			}
			if (ImGui::Button("unlock all")) {
				features::unlock_all();
			}

			/*static int level = 120;
			ImGui::SliderInt("", &level, 1, 8000);
			if (ImGui::Button("set level")) {
				g_fiber_pool->queue_job([] {
					features::set_level(&level);
					});
			}
			ImGui::SameLine();
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted("after you've set your level, change your session");
				ImGui::PopTextWrapPos();

				ImGui::EndTooltip();
			}*/
		}

		if (ImGui::CollapsingHeader("Configuration")) {
			static bool selection[5] = { false, true, false, false, false };
			ImGui::Selectable("1. I am selectable", &selection[0]);

			ImGui::Selectable("2. I am selectable", &selection[1]);
			ImGui::Text("3. I am not selectable");
			ImGui::Selectable("4. I am selectable", &selection[3]);
			if (ImGui::Selectable("5. I am double clickable", selection[4], ImGuiSelectableFlags_AllowDoubleClick))
				if (ImGui::IsMouseDoubleClicked(0))
					selection[4] = !selection[4];

			static int selected = -1;
			for (int n = 0; n < 5; n++)
			{
				char buf[32];
				sprintf(buf, "Object %d", n);
				if (ImGui::Selectable(buf, selected == n))
					selected = n;

				ImGui::SameLine();

				if (selected) {
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "on");
				}
				else
				{
					ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "off");
				}
			}
		}

		//if (ImGui::Button("Spawn an Adder"))
		//{
		//	*script_global(262145).at(28999).as<int*>() = 7200;
		//}

		//ImGui::SameLine();

		//if (ImGui::Button("Test g3log crash within ImGui"))
		//{
		//	*((PINT)nullptr) = 0xDEADBEEF;
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Test g3log crash within GTA V Script"))
		//{
		//	QUEUE_JOB_BEGIN_CLAUSE()
		//	{
		//		//PED::_0xB782F8238512BAD5(PLAYER::PLAYER_PED_ID(), nullptr); //This causes a crash at GTA5.exe+5845356 and nothing of value was in the log in the stack dump because of the context switch to GTA 5's memory. If you encounter something similar, you will have to figure out where the crash occured in the GTA 5 exe, and trace back that native, and figure out which function is calling the native that is crashing.
		//		*((PINT)nullptr) = 0xDEADBEEF;
		//	}
		//	QUEUE_JOB_END_CLAUSE
		//}

		ImGui::Separator();

		if (ImGui::Button("unload"))
		{
			g_running = false;
		}

		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	}
}