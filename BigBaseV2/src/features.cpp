#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include <gta/joaat.hpp>
#include <pointers.hpp>
#include <script_global.hpp>
#include <imgui.h>

namespace big
{
	void features::run_tick()
	{
		if (GetAsyncKeyState(VK_F5)) {
			teleport(true);
		}

		TestBool();
		god_mode(godbool);
		never_wanted(never_wanted_bool);
		esp(esp_bool);
		teleport(teleport_bool);
		aimbot(aimbot_bool);
		off_the_radar(off_the_radar_bool);
		set_vehicle_sell_price(vehicle_sell_price_bool);
		go_to_cayo(features::cayo_bool);
		spawn_vehicle(features::spawn_vehicle_bool);
		always_fix_vehicle(features::car_always_fixed_bool);
	}

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
				EXCEPT_CLAUSE
				script::get_current()->yield();
		}
	}

	bool features::testbool = false;
	bool features::godbool = false;
	bool features::never_wanted_bool = false;
	bool features::esp_bool = false;
	bool features::trigger_bool = false;
	bool features::teleport_bool = false;
	bool features::aimbot_bool = false;
	bool features::spawn_vehicle_bool = false;
	bool features::off_the_radar_bool = false;
	int features::vehicle_sell_price = 1000000;
	bool features::vehicle_sell_price_bool = false;
	bool features::cayo_bool = false;
	bool features::toogle_no_wp_modal = false;
	int features::tp_count = 0;
	std::string_view features::vehicle_model = "";
	bool features::car_always_fixed_bool = false;
	bool features::vehicle_god = false;
	int features::trigger_point = SKEL_Head;
	bool features::spectate_player = false;

	void features::TestBool()
	{
		// Code to be executed
	}

	void features::always_fix_vehicle(bool toogle) {
		if (toogle) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

				if (FIRE::IS_ENTITY_ON_FIRE(vehicle))
					FIRE::STOP_ENTITY_FIRE(vehicle);
				VEHICLE::SET_VEHICLE_FIXED(vehicle);
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
				VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.0f);
				VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.0f);
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.0f);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
				//VEHICLE::SET_VEHICLE_PAINT_FADE(vehicle, 0.0f);
				VEHICLE::SET_VEHICLE_UNDRIVEABLE(vehicle, FALSE);
				VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(vehicle, TRUE);
				VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, TRUE, TRUE, TRUE);
				VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(vehicle, TRUE);
				VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(vehicle, FALSE);
			}
		}
	}

	void features::go_to_cayo(bool toogle) {
		/*	[tuneables] : 262145
				[bunker_research_f] : 21389*/

		if (toogle) {
			std::vector<char*> ipls = { "h4_islandx_terrain_01_lod",  "h4_islandx_terrain_01_slod",  "h4_islandx_terrain_02",  "h4_islandx_terrain_02_lod",  "h4_islandx_terrain_02_slod",  "h4_islandx_terrain_03",  "h4_islandx_terrain_03_lod",  "h4_islandx_terrain_04",  "h4_islandx_terrain_04_lod",  "h4_islandx_terrain_04_slod",  "h4_islandx_terrain_05",  "h4_islandx_terrain_05_lod",  "h4_islandx_terrain_05_slod",  "h4_islandx_terrain_06",  "h4_mph4_terrain_01_grass_0",  "h4_mph4_terrain_01_grass_1",  "h4_mph4_terrain_02_grass_0",  "h4_mph4_terrain_02_grass_1",  "h4_mph4_terrain_02_grass_2",  "h4_mph4_terrain_02_grass_3",  "h4_mph4_terrain_04_grass_0",  "h4_mph4_terrain_04_grass_1",  "h4_mph4_terrain_05_grass_0",  "h4_mph4_terrain_06_grass_0",  "h4_islandx_terrain_06_lod",  "h4_islandx_terrain_06_slod",  "h4_islandx_terrain_props_05_a",  "h4_islandx_terrain_props_05_a_lod",  "h4_islandx_terrain_props_05_b",  "h4_islandx_terrain_props_05_b_lod",  "h4_islandx_terrain_props_05_c",  "h4_islandx_terrain_props_05_c_lod",  "h4_islandx_terrain_props_05_d",  "h4_islandx_terrain_props_05_d_lod",  "h4_islandx_terrain_props_05_d_slod",  "h4_islandx_terrain_props_05_e",  "h4_islandx_terrain_props_05_e_lod",  "h4_islandx_terrain_props_05_e_slod",  "h4_islandx_terrain_props_05_f",  "h4_islandx_terrain_props_05_f_lod",  "h4_islandx_terrain_props_05_f_slod",  "h4_islandx_terrain_props_06_a",  "h4_islandx_terrain_props_06_a_lod",  "h4_islandx_terrain_props_06_a_slod",  "h4_islandx_terrain_props_06_b",  "h4_islandx_terrain_props_06_b_lod",  "h4_islandx_terrain_props_06_b_slod",  "h4_islandx_terrain_props_06_c",  "h4_islandx_terrain_props_06_c_lod",  "h4_islandx_terrain_props_06_c_slod",  "h4_mph4_terrain_01",  "h4_mph4_terrain_01_long_0",  "h4_mph4_terrain_02",  "h4_mph4_terrain_03",  "h4_mph4_terrain_04",  "h4_mph4_terrain_05",  "h4_mph4_terrain_06",  "h4_mph4_terrain_06_strm_0",  "h4_mph4_terrain_lod",  "h4_mph4_terrain_occ_00",  "h4_mph4_terrain_occ_01",  "h4_mph4_terrain_occ_02",  "h4_mph4_terrain_occ_03",  "h4_mph4_terrain_occ_04",  "h4_mph4_terrain_occ_05",  "h4_mph4_terrain_occ_06",  "h4_mph4_terrain_occ_07",  "h4_mph4_terrain_occ_08",  "h4_mph4_terrain_occ_09",  "h4_boatblockers",  "h4_islandx",  "h4_islandx_disc_strandedshark",  "h4_islandx_disc_strandedshark_lod",  "h4_islandx_disc_strandedwhale",  "h4_islandx_disc_strandedwhale_lod",  "h4_islandx_props",  "h4_islandx_props_lod",  "h4_islandx_sea_mines",  "h4_mph4_island",  "h4_mph4_island_long_0",  "h4_mph4_island_strm_0",  "h4_aa_guns",  "h4_aa_guns_lod",  "h4_beach",  "h4_beach_bar_props",  "h4_beach_lod",  "h4_beach_party",  "h4_beach_party_lod",  "h4_beach_props",  "h4_beach_props_lod",  "h4_beach_props_party",  "h4_beach_props_slod",  "h4_beach_slod",  "h4_islandairstrip",  "h4_islandairstrip_doorsclosed",  "h4_islandairstrip_doorsclosed_lod",  "h4_islandairstrip_doorsopen",  "h4_islandairstrip_doorsopen_lod",  "h4_islandairstrip_hangar_props",  "h4_islandairstrip_hangar_props_lod",  "h4_islandairstrip_hangar_props_slod",  "h4_islandairstrip_lod",  "h4_islandairstrip_props",  "h4_islandairstrip_propsb",  "h4_islandairstrip_propsb_lod",  "h4_islandairstrip_propsb_slod",  "h4_islandairstrip_props_lod",  "h4_islandairstrip_props_slod",  "h4_islandairstrip_slod",  "h4_islandxcanal_props",  "h4_islandxcanal_props_lod",  "h4_islandxcanal_props_slod",  "h4_islandxdock",  "h4_islandxdock_lod",  "h4_islandxdock_props",  "h4_islandxdock_props_2",  "h4_islandxdock_props_2_lod",  "h4_islandxdock_props_2_slod",  "h4_islandxdock_props_lod",  "h4_islandxdock_props_slod",  "h4_islandxdock_slod",  "h4_islandxdock_water_hatch",  "h4_islandxtower",  "h4_islandxtower_lod",  "h4_islandxtower_slod",  "h4_islandxtower_veg",  "h4_islandxtower_veg_lod",  "h4_islandxtower_veg_slod",  "h4_islandx_barrack_hatch",  "h4_islandx_barrack_props",  "h4_islandx_barrack_props_lod",  "h4_islandx_barrack_props_slod",  "h4_islandx_checkpoint",  "h4_islandx_checkpoint_lod",  "h4_islandx_checkpoint_props",  "h4_islandx_checkpoint_props_lod",  "h4_islandx_checkpoint_props_slod",  "h4_islandx_maindock",  "h4_islandx_maindock_lod",  "h4_islandx_maindock_props",  "h4_islandx_maindock_props_2",  "h4_islandx_maindock_props_2_lod",  "h4_islandx_maindock_props_2_slod",  "h4_islandx_maindock_props_lod",  "h4_islandx_maindock_props_slod",  "h4_islandx_maindock_slod",  "h4_islandx_mansion",  "h4_islandx_mansion_b",  "h4_islandx_mansion_b_lod",  "h4_islandx_mansion_b_side_fence",  "h4_islandx_mansion_b_slod",  "h4_islandx_mansion_entrance_fence",  "h4_islandx_mansion_guardfence",  "h4_islandx_mansion_lights",  "h4_islandx_mansion_lockup_01",  "h4_islandx_mansion_lockup_01_lod",  "h4_islandx_mansion_lockup_02",  "h4_islandx_mansion_lockup_02_lod",  "h4_islandx_mansion_lockup_03",  "h4_islandx_mansion_lockup_03_lod",  "h4_islandx_mansion_lod",  "h4_islandx_mansion_office",  "h4_islandx_mansion_office_lod",  "h4_islandx_mansion_props",  "h4_islandx_mansion_props_lod",  "h4_islandx_mansion_props_slod",  "h4_islandx_mansion_slod",  "h4_islandx_mansion_vault",  "h4_islandx_mansion_vault_lod",  "h4_island_padlock_props",  "h4_mansion_gate_broken",  "h4_mansion_gate_closed",  "h4_mansion_remains_cage",  "h4_mph4_airstrip",  "h4_mph4_airstrip_interior_0_airstrip_hanger",  "h4_mph4_beach",  "h4_mph4_dock",  "h4_mph4_island_lod",  "h4_mph4_island_ne_placement",  "h4_mph4_island_nw_placement",  "h4_mph4_island_se_placement",  "h4_mph4_island_sw_placement",  "h4_mph4_mansion",  "h4_mph4_mansion_b",  "h4_mph4_mansion_b_strm_0",  "h4_mph4_mansion_strm_0",  "h4_mph4_wtowers",  "h4_ne_ipl_00",  "h4_ne_ipl_00_lod",  "h4_ne_ipl_00_slod",  "h4_ne_ipl_01",  "h4_ne_ipl_01_lod",  "h4_ne_ipl_01_slod",  "h4_ne_ipl_02",  "h4_ne_ipl_02_lod",  "h4_ne_ipl_02_slod",  "h4_ne_ipl_03",  "h4_ne_ipl_03_lod",  "h4_ne_ipl_03_slod",  "h4_ne_ipl_04",  "h4_ne_ipl_04_lod",  "h4_ne_ipl_04_slod",  "h4_ne_ipl_05",  "h4_ne_ipl_05_lod",  "h4_ne_ipl_05_slod",  "h4_ne_ipl_06",  "h4_ne_ipl_06_lod",  "h4_ne_ipl_06_slod",  "h4_ne_ipl_07",  "h4_ne_ipl_07_lod",  "h4_ne_ipl_07_slod",  "h4_ne_ipl_08",  "h4_ne_ipl_08_lod",  "h4_ne_ipl_08_slod",  "h4_ne_ipl_09",  "h4_ne_ipl_09_lod",  "h4_ne_ipl_09_slod",  "h4_nw_ipl_00",  "h4_nw_ipl_00_lod",  "h4_nw_ipl_00_slod",  "h4_nw_ipl_01",  "h4_nw_ipl_01_lod",  "h4_nw_ipl_01_slod",  "h4_nw_ipl_02",  "h4_nw_ipl_02_lod",  "h4_nw_ipl_02_slod",  "h4_nw_ipl_03",  "h4_nw_ipl_03_lod",  "h4_nw_ipl_03_slod",  "h4_nw_ipl_04",  "h4_nw_ipl_04_lod",  "h4_nw_ipl_04_slod",  "h4_nw_ipl_05",  "h4_nw_ipl_05_lod",  "h4_nw_ipl_05_slod",  "h4_nw_ipl_06",  "h4_nw_ipl_06_lod",  "h4_nw_ipl_06_slod",  "h4_nw_ipl_07",  "h4_nw_ipl_07_lod",  "h4_nw_ipl_07_slod",  "h4_nw_ipl_08",  "h4_nw_ipl_08_lod",  "h4_nw_ipl_08_slod",  "h4_nw_ipl_09",  "h4_nw_ipl_09_lod",  "h4_nw_ipl_09_slod",  "h4_se_ipl_00",  "h4_se_ipl_00_lod",  "h4_se_ipl_00_slod",  "h4_se_ipl_01",  "h4_se_ipl_01_lod",  "h4_se_ipl_01_slod",  "h4_se_ipl_02",  "h4_se_ipl_02_lod",  "h4_se_ipl_02_slod",  "h4_se_ipl_03",  "h4_se_ipl_03_lod",  "h4_se_ipl_03_slod",  "h4_se_ipl_04",  "h4_se_ipl_04_lod",  "h4_se_ipl_04_slod",  "h4_se_ipl_05",  "h4_se_ipl_05_lod",  "h4_se_ipl_05_slod",  "h4_se_ipl_06",  "h4_se_ipl_06_lod",  "h4_se_ipl_06_slod",  "h4_se_ipl_07",  "h4_se_ipl_07_lod",  "h4_se_ipl_07_slod",  "h4_se_ipl_08",  "h4_se_ipl_08_lod",  "h4_se_ipl_08_slod",  "h4_se_ipl_09",  "h4_se_ipl_09_lod",  "h4_se_ipl_09_slod",  "h4_sw_ipl_00",  "h4_sw_ipl_00_lod",  "h4_sw_ipl_00_slod",  "h4_sw_ipl_01",  "h4_sw_ipl_01_lod",  "h4_sw_ipl_01_slod",  "h4_sw_ipl_02",  "h4_sw_ipl_02_lod",  "h4_sw_ipl_02_slod",  "h4_sw_ipl_03",  "h4_sw_ipl_03_lod",  "h4_sw_ipl_03_slod",  "h4_sw_ipl_04",  "h4_sw_ipl_04_lod",  "h4_sw_ipl_04_slod",  "h4_sw_ipl_05",  "h4_sw_ipl_05_lod",  "h4_sw_ipl_05_slod",  "h4_sw_ipl_06",  "h4_sw_ipl_06_lod",  "h4_sw_ipl_06_slod",  "h4_sw_ipl_07",  "h4_sw_ipl_07_lod",  "h4_sw_ipl_07_slod",  "h4_sw_ipl_08",  "h4_sw_ipl_08_lod",  "h4_sw_ipl_08_slod",  "h4_sw_ipl_09",  "h4_sw_ipl_09_lod",  "h4_sw_ipl_09_slod",  "h4_underwater_gate_closed",  "h4_islandx_placement_01",  "h4_islandx_placement_02",  "h4_islandx_placement_03",  "h4_islandx_placement_04",  "h4_islandx_placement_05",  "h4_islandx_placement_06",  "h4_islandx_placement_07",  "h4_islandx_placement_08",  "h4_islandx_placement_09",  "h4_islandx_placement_10",  "h4_mph4_island_placement" };

			for (auto i = 0; i < ipls.size(); i++) {
				if (i == 0) {
					STREAMING::REQUEST_IPL(ipls[i]);
					i++;
				}

				if (STREAMING::IS_IPL_ACTIVE(ipls[i - 1])) {
					STREAMING::REQUEST_IPL(ipls[i]);
				}
			}

			Entity entity = PLAYER::PLAYER_PED_ID();

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, 4892.064, -4923.567, 3.500, 0, 0, 1);

			features::cayo_bool = false;
		}
	}

	void features::unlock_all() {
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SCRIPT_INCREASE_STL"), 100, 0);

		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_8"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_9"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_10"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_11"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_tattoo_fm_unlocks_12"), -1, 1);

		STATS::STAT_SET_BOOL(rage::joaat("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_USJS_COMPLETED"), 50, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_USJS_FOUND"), 50, 0);
		STATS::STAT_SET_BOOL(rage::joaat("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
		STATS::STAT_SET_BOOL(rage::joaat("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_DB_PLAYER_KILLS"), 1000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_KILLS_PLAYERS"), 1000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_TDM_MVP"), 60, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_RACES_WON"), 101, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
		STATS::STAT_SET_BOOL(rage::joaat("MP0_AWD_FMATTGANGHQ"), 1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FMBBETWIN"), 50000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_DM_WINS"), 51, 0);
		STATS::STAT_SET_BOOL(rage::joaat("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_PLAYER_HEADSHOTS"), 623, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_DM_WINS"), 63, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_TDM_WINS"), 13, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_GOLF_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_FM_TENNIS_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_AWD_20_KILLS_MELEE"), 50, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SMG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_PUMP_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_RPG_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);

		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
		STATS::STAT_SET_INT(rage::joaat("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
	}

	//Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_SelectedPlayer);
	//uint64_t args[3] = { 1120313136, player, -1952943290 };
	//SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 3, 1 << player);

	//Teleport = -1253256204 // func_16277 -> Search "Mission_Pass_Notify"
	//	Clear Wanted = 301606138 // func_16683
	//	Sound Spam = 1337731455 // func_16722 -> Search "CELL_APTINVYACHT"
	//	Sound Spam 2 = 323449272 // func_16104 -> Search "CELL_BWHINV_1"
	//	Set Bounty = 544453591 // func_16690 -> Search "FM_TXT_BNTY2"
	//	CEO Ban = 3266142158 // func_7734 -> Search "MPPLY_VIPGAMEPLAYDISABLEDTIMER"
	//	Send Notifications = 1975453628 // func_16795 -> Search "TICK_ATTVAN"
		//Send To Job = 1764541627 // func_15976 -> Above the first time the string "FMMC_PLYLOAD" appears
	//	Send To Job 2 = 915906776 // func_16528
	//	Remote Blind Eye = -336686044 //  func_16229
	//	CEO 10k = -601653676 //func_16232 -> Search "Goon_Paid_Large"
	//	CEO Kick = -1775205375 // func_16244 -> Seach "GBTER_BIG"
	//	Vehicle Kick = -130330100 // func_16698 -> Seach "PIM_RFMOC"
	//	Transaction Error = 189238289 // func_16261 -> Search "PIM_TIGC"
	//	Remote OTR = -1363050950 //func_16677 -> Search PLAYER::NETWORK_PLAYER_ID_TO_INT() /*421*/

	//Teleport = -171207973 // func_17039 -> Search "Mission_Pass_Notify"
	//	Clear Wanted = 393068387 // func_17445 -> 3 functions above where the string PLYVEH_INS_DES" is found
	//	Sound Spam = 1097312011 // func_17487 -> Search "CELL_APTINVYACHT"
	//	Sound Spam 2 = -1162153263 // func_16862 -> Search "CELL_BWHINV_1"
	//	Set Bounty = -116602735 // func_17452 -> Search "FM_TXT_BNTY2"
	//	CEO Ban = -738295409 // func_16889 -> Search "MPPLY_VIPGAMEPLAYDISABLEDTIMER"
	//	Send Notifications = -1949011582 // func_17560 -> Search "TICK_ATTVAN"
	//	Send To Job = -545396442 // func_16671 -> Above the first time the string "FMMC_PLYLOAD" appears
	//	Send To Job 2 = 1070934291 // func_17290
	//	Remote Blind Eye = 392501634 //  func_16991 -> search Global_1590682[PLAYER::PLAYER_ID() /*883*/].f_758
	//	CEO 10k = -2029779863 //func_16994 -> Search "Goon_Paid_Large"
	//	CEO Kick = -1648921703 // func_17006 -> Seach "GBTER_BIG"
	//	Vehicle Kick = -1333236192 // func_17463 -> Seach "PIM_RFMOC"
	//	Transaction Error = 1302185744 // func_17419 -> Search "PIM_TIGC"
	//	Remote OTR = 575518757 //func_17439 -> Search PLAYER::NETWORK_PLAYER_ID_TO_INT() /*443*/
	//	Rotate Cam = 1120313136 //func_17512 -> search "CnCTG_IN_BF", the reset hash is the one at Global_1392777.f_46

	//* script_global(1312854).as<int*>() = TheSessionID; //First area you went wrong
	//MISC::SET_BIT(&*script_global(1312443).as<int*>(), 1);
	//script::get_current()->yield(200ms);
	//MISC::SET_BIT(&*script_global(1312443).as<int*>(), 0);

	//* script_global(1312443).at(2).as<int*>() = -1;
	////Instead of:
	//*script_global(1312854).as<int*>() = TheSessionID;
	////Then Proceed as per usual

	/*{0, "Join Public Session"},
	{ 1,"New Public Session" },
	{ 2,"Closed Crew Session" },
	{ 3,"Crew Session" },
	{ 6,"Closed Friend Session" },
	{ 9,"Find Friend Session" },
	{ 10,"Solo Session" },
	{ 11,"Invite Only Session" },
	{ 12,"Join Crew Session" },
	{ -1, "Leave GTA Online" },*/

	//Carmod_shop.c line 122182

	//	if (func_1376(78225582, -1224924353, iVar23, -1316591359, 1, Global_99007.f_969[Local_399.f_118.f_1], 1, 4, 0, 3))

	void features::unlock_heist_preps()
	{
		STATS::STAT_SET_INT(rage::joaat("MP0_H4_PROGRESS"), 126823, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_TARGET"), 5, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_BS_GEN"), -1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_BS_ENTR"), 63, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_BS_ABIL"), 63, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_WEAPONS"), 2, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_WEP_DISRP"), 3, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_ARM_DISRP"), 3, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_GRAPPEL"), -1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_UNIFORM"), -1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_BOLTCUT"), -1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4CNF_APPROACH"), -1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4_MISSIONS"), -1, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_CASH_V"), 10000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_WEED_V"), 10000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_COKE_V"), 10000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_GOLD_V"), 10000, 0);

		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_PAINT_V"), 10000, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_CASH_I_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_CASH_C_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_WEED_I_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_WEED_C_SCOPED"), -99, 0);

		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_COKE_I_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_COKE_C_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_GOLD_I_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_GOLD_C_SCOPED"), -99, 0);
		STATS::STAT_SET_INT(rage::joaat("MP0_H4LOOT_PAINT_SCOPED"), -99, 0);
	}

	int features::teleport(bool toogle) {
		if (toogle) {
			Entity entity = PLAYER::PLAYER_PED_ID();
			Vector3 pos = HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(HUD::_GET_WAYPOINT_BLIP_SPRITE()));
			if (pos.x == 0 && pos.y == 0) {
				LOG(G3LOG_DEBUG) << "no waypoint set.";
				features::teleport_bool = false;

				return 2;
			}

			if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
			{
				entity = PED::GET_VEHICLE_PED_IS_USING(entity);
			}

			float groundZ;
			for (int i = 0; i < 20; ++i) {
				if (i) {
					for (float z = 1000.f; z >= 0.f; z -= 100.f) {
						STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, z);
						script::get_current()->yield();
					}
				}

				if (MISC::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, 1000.f, &groundZ, false, false)) {
					pos.z = groundZ;
					break;
					//coords.x, coords.y, groundZ + 1);
				}
			}

			LOG(G3LOG_DEBUG) << "coords: " << pos.x << " " << pos.x << " " << groundZ;

			ENTITY::SET_ENTITY_COORDS(entity, pos.x, pos.y, groundZ + 1, 0, 0, 0, 1);
		}

		features::teleport_bool = false;

		return 0;
	}

	void features::never_wanted(bool toogle)
	{
		if (toogle) {
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), 1);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}
		else {
			PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
			PLAYER::SET_MAX_WANTED_LEVEL(5);
		}
	}

	void features::off_the_radar(bool toogle) {
		if (toogle) {
			*script_global(2425869).at(1 + (PLAYER::PLAYER_ID() * 443)).at(204).as<int*>() = 1;
			*script_global(2440049).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 999;
		}
		else {
			*script_global(2425869).at(1 + (PLAYER::PLAYER_ID() * 443)).at(204).as<int*>() = 0;
			*script_global(2440049).at(70).as<int*>() = 0;
		}
	}

	void features::set_vehicle_sell_price(bool toogle)
	{
		if (toogle)
		{
			Entity entity = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0)) {
				*script_global(970).as<int*>() = INT_MAX - 1;
				//*script_global(970).as<int*>() = features::vehicle_sell_price;
			}
		}
	}

	void features::esp(bool toogle)
	{
		if (toogle)
		{
			Player playerPed = PLAYER::PLAYER_PED_ID();

			for (int i = 0; i < 32; i++)
			{
				Player playerHandle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				Vector3 handleCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerHandle, 0, 0, 0);
				Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);

				Vector3 entCoords = ENTITY::GET_ENTITY_COORDS(playerHandle, 0);

				const char* Name = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(i));
				//auto distanceBetweenPlayers = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(entCoords.x, entCoords.y, entCoords.z, playerCoords.x, playerCoords.y, playerCoords.z, FALSE);

				if (ENTITY::DOES_ENTITY_EXIST(playerHandle))
				{
					float x1;
					float y1;

					BOOL screenCoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z + 0.90f, &x1, &y1);

					std::string playerName = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(i));

					/*std::ostringstream ss;
					ss << distanceBetweenPlayers;
					std::string distanceSetup(ss.str());*/

					std::string nameSetupRed = "~HUD_COLOUR_ORANGE~" + playerName;
					std::string nameSetupGreen = "~HUD_COLOUR_GREEN~" + playerName;

					char* playerInfoRed = new char[nameSetupRed.length() + 1];
					char* playerInfoGreen = new char[nameSetupGreen.length() + 1];

					std::strcpy(playerInfoRed, nameSetupRed.c_str());
					std::strcpy(playerInfoGreen, nameSetupGreen.c_str());

					HUD::SET_TEXT_FONT(4);
					HUD::SET_TEXT_SCALE(0.0, 0.40);
					HUD::SET_TEXT_COLOUR(0, 255, 0, 225);
					HUD::SET_TEXT_CENTRE(0);
					HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					HUD::SET_TEXT_EDGE(0, 0, 0, 0, 0);
					HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
					if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, playerHandle, 17))
					{
						HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerInfoGreen);
					}
					else
					{
						HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerInfoRed);
					}
					HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x1, y1, 0);
					HUD::SET_TEXT_OUTLINE();
					HUD::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);

					delete[] playerInfoGreen;
					delete[] playerInfoRed;
				}
			}
		}
	}

	void features::aimbot(bool toogle) {
		if (toogle) {
			Entity aimed_at_entity;
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &aimed_at_entity))
			{
				if (ENTITY::IS_ENTITY_A_PED(aimed_at_entity) && !ENTITY::IS_ENTITY_DEAD(aimed_at_entity, false))
				{
					Vector3 mouth = PED::GET_PED_BONE_COORDS(aimed_at_entity, features::trigger_point, 0.1f, 0.0f, 0.0f);

					PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), mouth.x, mouth.y, mouth.z, true);
				}
			}
		}
	}

	void features::spawn_vehicle(bool toogle)
	{
		if (toogle) {
			auto hash = rage::joaat(features::vehicle_model);
			while (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				STREAMING::REQUEST_MODEL(hash);
				script::get_current()->yield();
			}

			auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			auto vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y - 3, pos.z, 0.f, true, true);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574; //By writing the "old" bypass to the function, running CREATE_VEHICLE, then restoring it, the anti-cheat does not have enough time to catch the function in a dirty state.
			*script_global(4269479).as<int*>() = 1;

			script::get_current()->yield();
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			if (*g_pointers->m_is_session_started)
			{
				DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
				ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
				auto networkId = NETWORK::VEH_TO_NET(vehicle);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			}

			//	//auto hash = rage::joaat(name);

			//	//constexpr auto hash2 = RAGE_JOAAT(name);

			//	while (!STREAMING::HAS_MODEL_LOADED(hash))
			//	{
			//		STREAMING::REQUEST_MODEL(hash);
			//		script::get_current()->yield();
			//	}

			//auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			//*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			//Vehicle vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.f, TRUE, FALSE, FALSE);
			//*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574; // 0x4125A7 4269479  By writing the "old" bypass to the function, running CREATE_VEHICLE, then restoring it, the anti-cheat does not have enough time to catch the function in a dirty state.
			////*script_global(4269479).as<int*>() = 1;

			//script::get_current()->yield();
			//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			//if (*g_pointers->m_is_session_started)
			//{
			//	DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			//	ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
			//	auto networkId = NETWORK::VEH_TO_NET(vehicle);
			//	if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
			//		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			//	VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
			//}
		}

		features::spawn_vehicle_bool = false;
	}

	void features::vehicle_god_mode(bool toogle) {
		Entity entity = PLAYER::PLAYER_ID();
	}

	void features::player_list(bool toogle, ImGuiContext* context) {
		if (!PLAYER::IS_PLAYER_ONLINE()) {
			return;
		}

		//ImGui::Button("Heu");

		int player_count = NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS();

		std::vector<Ped> peds;
		std::vector<const char*> player_names;
		//const int player_count_init = player_count;

		//const char* player_names[];

		for (int i = 0; i < player_count; i++) {
			Ped ped = PLAYER::GET_PLAYER_PED(i);
			auto player_name = PLAYER::GET_PLAYER_NAME(i);
			ImGui::Button(player_name);

			////Vector3 shitterPosition = ENTITY::GET_ENTITY_COORDS(shitterPed, false);
		}
	}

	void features::set_level(int* level) {
		int first = 223597;
		int last = 0;
		last -= 2.68e+08;

		auto xp_val = first * *level + last;

		LOG(G3LOG_DEBUG) << "xp_val: " << xp_val;

		/*if (found_level) {
			STATS::STAT_SET_INT(rage::joaat("MP0_CHAR_SET_RP_GIFT_ADMIN"), xp_val, 0);
		}*/
	}

	void features::join_session(int identifier)
	{
		LOG(G3LOG_DEBUG) << "creating session with identifier: " << identifier;

		*script_global(1312443).at(2).as<int*>() = identifier;
		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 1);
		script::get_current()->yield(200ms);
		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 0);
	}

	void features::specate_player(bool toogle, Ped ped)
	{
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(toogle, ped);
	}

	void features::god_mode(bool toogle)
	{
		static int armourPlayer = 0;

		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if (armourPlayer == 0) {
			armourPlayer = PED::GET_PED_ARMOUR(playerPed);
		}

		if (toogle) {
			//*script_global(1590682).at(PLAYER::PLAYER_ID(), 883).at(211).at(56).as<int*>() = 1000000000;

			ENTITY::SET_ENTITY_INVINCIBLE(player, true);
			ENTITY::SET_ENTITY_PROOFS(playerPed, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
			/*PED::SET_PED_CAN_RAGDOLL(playerPed, FALSE);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, FALSE);*/
			PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
		}
		else
		{
			ENTITY::SET_ENTITY_INVINCIBLE(player, false);
			ENTITY::SET_ENTITY_PROOFS(playerPed, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
			/*	PED::SET_PED_CAN_RAGDOLL(playerPed, TRUE);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, TRUE);*/

			if (armourPlayer != 0) {
				PED::SET_PED_ARMOUR(player, armourPlayer);
				armourPlayer = 0;
			}
		}
	}
}