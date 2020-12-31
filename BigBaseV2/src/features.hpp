#pragma once
#include "common.hpp"
#include <imgui.h>

namespace big::features
{
	void run_tick();
	void script_func();

	/*Test Bool*/
	extern bool testbool;
	extern bool godbool;
	extern bool never_wanted_bool;
	extern bool esp_bool;
	extern bool trigger_bool;
	extern bool teleport_bool;
	extern bool aimbot_bool;
	extern bool spawn_vehicle_bool;
	extern bool off_the_radar_bool;
	extern int vehicle_sell_price;
	extern bool vehicle_sell_price_bool;
	extern bool cayo_bool;
	extern bool toogle_no_wp_modal;
	extern int tp_count;
	extern std::string_view vehicle_model;
	extern bool car_always_fixed_bool;
	extern bool vehicle_god;
	extern int trigger_point;
	extern bool spectate_player;

	void TestBool();
	void god_mode(bool toogle);
	void never_wanted(bool toogle);
	void esp(bool toogle);
	int teleport(bool toogle);
	void aimbot(bool toogle);
	void spawn_vehicle(bool toogle);
	//	void trigger(bool toogle);
	void vehicle_god_mode(bool toogle);
	void off_the_radar(bool toogle);
	void set_vehicle_sell_price(bool toogle);
	void go_to_cayo(bool toogle);
	void unlock_all();
	void unlock_heist_preps();
	void always_fix_vehicle(bool toogle);
	void player_list(bool toogle, ImGuiContext* context);
	void set_level(int* level);
	void join_session(int identifier);
	void specate_player(bool toogle, Ped ped);
}