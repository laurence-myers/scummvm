/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/ },.
 *
 */

#include "m4/riddle/rooms/section7/room701.h"
#include "m4/graphics/gr_series.h"
#include "m4/riddle/vars.h"

namespace M4 {
namespace Riddle {
namespace Rooms {

void Room701::preload() {
	_G(player).walker_type = WALKER_ALT;
	_G(player).shadow_type = SHADOW_ALT;
	LoadWSAssets("OTHER SCRIPT", _G(master_palette));
}

void Room701::init() {
	if (_G(flags[V286]))
		_G(flags[V224]) = 1;

	_itemDigiName = nullptr;
	_field8C = 0;
	_field50_counter = 0;
	_field9E_triggerNum = -1;
	_field130 = 0;

	if (_G(game).previous_room == KERNEL_RESTORING_GAME) {
		_agentTalkLoopTjSeries = series_load("AGENT TALK LOOP TJ", -1, nullptr);
		_agentGetTelegramSeries = series_load("AGENT  GET TELEGRAM", -1, nullptr);
		_agentShowMapSeries = series_load("AGENT SHOW MAP", -1, nullptr);
		_agentGiveParcelSeries = series_load("AGENT  GIVE PARCEL", -1, nullptr);
		_701rp01Series = series_load("701RP01", -1, nullptr);
		_ripTrekHandTalkPos3Series = series_load("RIP TREK HAND TALK POS3", -1, nullptr);
		_ripTrekTalkerPos3Series = series_load("RIP TREK TALKER POS3", -1, nullptr);
		_ripTrekMedReachPos3Series = series_load("RIP TREK MED REACH POS3", -1, nullptr);
		_701rp99Series = series_load("701RP99", -1, nullptr);
		_agentPoshExpressMach = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 1792, false, triggerMachineByHashCallback, "agent posh express");
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 13, 13, -1, _agentTalkLoopTjSeries, 13, 13, 0);
	} else {
		_field88 = 0;

		player_set_commands_allowed(false);
		_agentTalkLoopTjSeries = series_load("AGENT TALK LOOP TJ", -1, nullptr);
		_agentGetTelegramSeries = series_load("AGENT  GET TELEGRAM", -1, nullptr);
		_agentShowMapSeries = series_load("AGENT SHOW MAP", -1, nullptr);
		_agentGiveParcelSeries = series_load("AGENT  GIVE PARCEL", -1, nullptr);
		_701rp01Series = series_load("701RP01", -1, nullptr);
		_ripTrekHandTalkPos3Series = series_load("RIP TREK HAND TALK POS3", -1, nullptr);
		_ripTrekTalkerPos3Series = series_load("RIP TREK TALKER POS3", -1, nullptr);
		_ripTrekMedReachPos3Series = series_load("RIP TREK MED REACH POS3", -1, nullptr);
		_701rp99Series = series_load("701RP99", -1, nullptr);
		_agentPoshExpressMach = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 1792, false, triggerMachineByHashCallback, "agent posh express");
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 13, 13, -1, _agentTalkLoopTjSeries, 13, 13, 0);

		++_G(flags[V006]);
		if (setItemsPlacedFlags()) {
			_field88 = 1;
			_itemDigiName = getItemsPlacedDigi();
			++_field50_counter;
		}

		ws_demand_location(_G(my_walker), 50, 264);
		ws_demand_facing(_G(my_walker), 3);
		_field134 = 0;
		ws_walk(_G(my_walker), 352, 251, nullptr, player_been_here(701) ? 80 : 40, 3, true);
	}

	digi_preload("701_s01", -1);
	digi_play_loop("701_s01", 2, 45, -1, -1);
}

void Room701::pre_parser() {
	if (player_said("rm702") && !_field88) {
		_G(player).need_to_walk = false;
		_G(player).ready_to_walk = true;
		_G(player).waiting_for_walk = false;
	}
}

void Room701::parser() {
	bool lookFl = player_said_any("look", "look at");
	bool talkFl = player_said_any("talk", "talk to");
	bool takeFl = player_said("take");
	bool gearFl = player_said_any("push", "pull", "gear", "open", "close");

	if (player_said("conv701a")) {
		if (_G(kernel).trigger == 1) {
			int32 who = conv_whos_talking();
			if (who == 1)
				_field98 = 1103;
			else if (who <= 0)
				_field6C = 2102;

			conv_resume(conv_get_handle());
		} else {
			conv701a();
		}
	} // if (player_said("conv701a"))

	else if (talkFl && player_said("agent")) {
		player_set_commands_allowed(false);
		_field88 = 1;
		_field72 = -1;
		_field94 = 1000;
		_field98 = 1100;
		_G(kernel).trigger_mode = KT_DAEMON;
		kernel_timing_trigger(1, 102, nullptr);
		_G(kernel).trigger_mode = KT_PARSE;
	} else if (lookFl && player_said("COAT RACK")) {
		digi_play("com130", 1, 255, -1, -1);
	} else if (lookFl && player_said("Skin") && !_G(flags[V226])) {
		switch (_G(kernel).trigger) {
		case -1:
			player_set_commands_allowed(false);
			setGlobals1(_ripTrekTalkerPos3Series, 1, 1, 1, 4, 1, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			sendWSMessage_110000(_G(my_walker), -1);
			digi_play("701R10", 1, 255, 21, -1);

			break;

		case 21:
			sendWSMessage_120000(_G(my_walker), -1);
			sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 14, -1, _agentTalkLoopTjSeries, 11, 13, 1);

			break;

		case 22:
			sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 11, -1, _agentTalkLoopTjSeries, 11, 11, 0);
			sendWSMessage_110000(_G(my_walker), -1);
			digi_play("701R11", 1, 255, 23, -1);

			break;

		case 23:
			sendWSMessage_120000(_G(my_walker), -1);
			sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 0);
			sendWSMessage_140000(_agentPoshExpressMach, 11);
			digi_play("701X10", 1, 255, 24, -1);

			break;

		case 24:
			sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 11, -1, _agentTalkLoopTjSeries, 11, 11, 0);
			digi_play("701R12", 1, 255, 25, -1);

			break;

		case 25:
			sendWSMessage_150000(_G(my_walker), -1);
			_G(flags[V226]) = 1;
			player_set_commands_allowed(true);

			break;

		default:
			break;
		}
	} // ecx && player_said("Skin") && !_G(flags[V226])

	else if (lookFl && player_said("Skin") && _G(flags[V226])) {
		player_set_commands_allowed(false);
		digi_play("701R13", 1, 255, -1, -1);
		player_set_commands_allowed(true);

	} // ecx && player_said("Skin") && _G(flags[V226])

	else if (lookFl && player_said("Window"))
		digi_play("701R17", 1, 255, -1, -1);
	else if (lookFl && player_said("Poster"))
		digi_play("com002", 1, 255, -1, 997);
	else if (lookFl && player_said("Magazines"))
		digi_play("com003", 1, 255, -1, 997);
	else if (lookFl && player_said("Prayer Wheel"))
		digi_play("701R19", 1, 255, -1, -1);
	else if (lookFl && player_said("Agent"))
		digi_play("701R20", 1, 255, -1, -1);
	else if (lookFl && player_said_any("Sofa", "Chair"))
		digi_play("com023", 1, 255, -1, 997);
	else if (lookFl && player_said("Telephone"))
		digi_play("com024", 1, 255, -1, 997);
	else if (lookFl && player_said("Postcard Rack"))
		digi_play("701R14", 1, 255, -1, -1);
	else if (lookFl && player_said("Brochures"))
		digi_play("701R15", 1, 255, -1, -1);
	else if (lookFl && player_said("BUSH"))
		digi_play("701R41", 1, 255, -1, -1);
	else if (lookFl && player_said(" "))
		digi_play("com001", 1, 255, -1, -1);
	else if (takeFl && player_said("Brochures")) {
		if (inv_player_has("PRAYER WHEEL BROCHURE"))
			digi_play("701R21", 1, 255, -1, -1);
		else {
			switch (_G(kernel).trigger) {
			case -1:
				player_set_commands_allowed(false);
				setGlobals1(_ripTrekMedReachPos3Series, 1, 17, 17, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				sendWSMessage_110000(_G(my_walker), 62);

				break;

			case 62:
				digi_play("950_S07", 2, 255, -1, 950);
				kernel_examine_inventory_object("PING PRAYER WHEEL BROCHURE", _G(master_palette), 5, 1, 318, 150, 63, nullptr, -1);

				break;

			case 63:
				sendWSMessage_140000(_G(my_walker), 64);
				break;

			case 64:
				inv_give_to_player("PRAYER WHEEL BROCHURE");
				player_set_commands_allowed(true);

				break;

			default:
				break;
			}
		}
	} // esi && player_said("Brochures")

	else if (takeFl && player_said("Postcard Rack"))
		digi_play("com004", 1, 255, -1, 997);
	else if (takeFl && player_said("Magazines"))
		digi_play("com005", 1, 255, -1, 997);
	else if (takeFl && player_said("Yeti Skin"))
		digi_play("701R24", 1, 255, -1, -1);
	else if (player_said("PRAYER WHEEL BROCHURE", "PRAYER WHEEL") && inv_player_has("PRAYER WHEEL BROCHURE")) {
		switch (_G(kernel).trigger) {
		case -1:
			player_set_commands_allowed(false);
			setGlobals1(_701rp99Series, 1, 12, 12, 12, 0, 12, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			sendWSMessage_110000(_G(my_walker), 301);

			break;

		case 301:
			digi_play("701R25", 1, 255, 302, -1);
			break;

		case 302:
			sendWSMessage_120000(_G(my_walker), 303);
			break;

		case 303:
			sendWSMessage_150000(_G(my_walker), 304);
			break;

		case 304:
			player_set_commands_allowed(true);
			break;

		default:
			break;

		}
	} // player_said("PRAYER WHEEL BROCHURE", "PRAYER WHEEL") && inv_player_has("PRAYER WHEEL BROCHURE")

	else if (gearFl && player_said_any("Sofa", "Chair"))
		digi_play("com025", 1, 255, -1, 997);
	else if (gearFl && player_said("Telephone"))
		digi_play("com026", 1, 255, -1, 997);
	else if ((player_said("SIKKIMESE RUPEE", "Agent") && inv_player_has("SIKKIMESE RUPEE"))
		||   player_said("US DOLLARS", "Agent") // 2 checks in the original: one checks if the payer has dollars, the other doesn't.
		||   (player_said("CHINESE YUAN", "Agent") && inv_player_has("CHINESE YUAN"))
		||   (player_said("PERUVIAN INTI", "Agent") && inv_player_has("PERUVIAN INTI"))
		||   (player_said("SIKKIMESE RUPEE", "Agent") && inv_player_has("SIKKIMESE RUPEE"))) {
		digi_play("com012", 1, 255, -1, 997);
	} else if (player_said("journal", "skin")) {
		digi_play(_G(flags[V226]) ? "701R35" : "701R36", 1, 255, -1, -1);
	} else if (player_said("rm702")) {
		if (_field88) {
			switch (_G(kernel).trigger) {
			case -1:
				disable_player_commands_and_fade_init(3);
				break;

			case 3:
				digi_stop(3);
				_G(game).new_room = 702;
				break;

			default:
				break;
			}
		} else {
			switch (_G(kernel).trigger) {
			case -1:
				player_set_commands_allowed(false);
				player_update_info(_G(my_walker), &_G(player_info));
				ws_walk(_G(my_walker), 214, 265, nullptr, 2, 3, true);

				break;

			case 2:
				setGlobals1(_ripTrekTalkerPos3Series, 1, 1, 1, 5, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				sendWSMessage_110000(_G(my_walker), -1);
				digi_play("22_12p01", 1, 255, 3, -1);

				break;

			case 3:
				sendWSMessage_120000(_G(my_walker), -1);
				sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
				sendWSMessage_1a0000(_agentPoshExpressMach, 11);
				digi_play("22_12n01", 1, 255, 4, -1);

				break;

			case 4:
				sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 11, -1, _agentTalkLoopTjSeries, 11, 11, 0);
				sendWSMessage_150000(_G(my_walker), -1);
				ws_walk(_G(my_walker), 73, 265, nullptr, 5, 3, true);

				break;

			case 5:
				player_set_commands_allowed(true);
				disable_player_commands_and_fade_init(6);

				break;

			case 6:
				digi_stop(3);
				_G(game).new_room = 702;
				break;

			default:
				break;
			}
		}
	} // player_said("rm702")

	_G(player).command_ready = false;
}

void Room701::daemon() {
	switch (_G(kernel).trigger) {
	case 19:
		digi_play("701_s01", 3, 127, 19, -1);
		break;

	case 40:
		_field88 = 1;
		player_set_commands_allowed(false);
		player_update_info(_G(my_walker), &_G(player_info));
		_safariShadow3Mach = series_place_sprite("SAFARI SHADOW 3", 0, _G(player_info).x, _G(player_info).y, _G(player_info).scale, 3840);
		setGlobals1(_ripTrekHandTalkPos3Series, 1, 4, 4, 4, 0, 5, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		sendWSMessage_110000(_G(my_walker), 1040);
		digi_play("701R01", 1, 255, -1, -1);

		break;

	case 41:
		sendWSMessage_150000(_G(my_walker), -1);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X01", 1, 255, 71, -1);

		break;

	case 42:
		setGlobals1(_ripTrekTalkerPos3Series, 1, 1, 1, 5, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		sendWSMessage_110000(_G(my_walker), -1);
		digi_play("701R02", 1, 255, 43, -1);

		break;

	case 43:
		sendWSMessage_120000(_G(my_walker), -1);
		updateCounter();
		sendWSMessage_150000(_G(my_walker), -1);

		if (_field50_counter == 1) {
			_field8C = 1;
			_agentPoshExpressMach02 = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 768, false, triggerMachineByHashCallback, "agent posh express");
			ws_hide_walker(_G(my_walker));
			sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 1, 11, -1, _701rp01Series, 11, 11, 0);
			sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
			sendWSMessage_1a0000(_agentPoshExpressMach, 11);
			digi_play("701X02", 1, 255, 2200, -1);

		} else if (_field50_counter > 0) {
			_field8C = 1;
			_agentPoshExpressMach02 = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 768, 0, triggerMachineByHashCallback, "agent posh express");
			ws_hide_walker(_G(my_walker));
			sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 1, 11, -1, _701rp01Series, 11, 11, 0);
			sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
			sendWSMessage_1a0000(_agentPoshExpressMach, 11);
			digi_play("701X03", 1, 255, 2200, -1);

		} else {
			kernel_timing_trigger(1, (_field134 == 1) ? 44 : 95, nullptr);
		}

		break;

	case 44:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 12, 12, 45, _agentTalkLoopTjSeries, 12, 12, 0);

		break;

	case 45:
		setGlobals1(_ripTrekTalkerPos3Series, 1, 1, 1, 5, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		sendWSMessage_110000(_G(my_walker), -1);
		digi_play("701R03", 1, 255, 47, -1);

		break;

	case 46:
		sendWSMessage_110000(_G(my_walker), -1);
		digi_play("701R03", 1, 255, 47, -1);

		break;

	case 47:
		sendWSMessage_120000(_G(my_walker), -1);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X04", 1, 255, 48, -1);

		break;

	case 48:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 12, 12, -1, _agentTalkLoopTjSeries, 12, 12, 0);
		sendWSMessage_150000(_G(my_walker), 948);

		break;

	case 49:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, -1, _701rp01Series, 11, 11, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X05", 1, 255, 50, -1);

		break;

	case 50:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 12, 12, -1, _agentTalkLoopTjSeries, 12, 12, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, -1, _701rp01Series, 11, 19, 4);
		sendWSMessage_1a0000(_agentPoshExpressMach02, 11);
		digi_play("701R05", 1, 255, 51, -1);

		break;

	case 51:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, -1, _701rp01Series, 11, 11, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 13, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X06", 1, 255, 52, -1);

		break;

	case 52:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 12, 12, -1, _agentTalkLoopTjSeries, 12, 12, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, -1, _701rp01Series, 11, 19, 4);
		sendWSMessage_1a0000(_agentPoshExpressMach02, 11);
		digi_play("701R06", 1, 255, 53, -1);

		break;

	case 53:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, -1, _701rp01Series, 11, 11, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 13, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X07", 1, 255, 54, -1);

		break;

	case 54:
		terminateMachine(_agentPoshExpressMach02);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentShowMapSeries, 1, 47, 55, _agentShowMapSeries, 47, 47, 0);

		break;

	case 55:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentShowMapSeries, 47, 50, -1, _agentShowMapSeries, 47, 50, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X07A", 1, 255, 56, -1);

		break;

	case 56:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentShowMapSeries, 47, 1, 73, _agentShowMapSeries, 1, 1, 0);

		break;

	case 57:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, -1, _701rp01Series, 11, 11, 4);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X08", 1, 255, 58);

		break;

	case 58:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 12, 12, -1, _agentTalkLoopTjSeries, 12, 12, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 19, -1, _701rp01Series, 10, 19, 4);
		sendWSMessage_1a0000(_agentPoshExpressMach02, 9);
		digi_play("701R08", 1, 255, 59);

		break;

	case 59:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 1, 60, _701rp01Series, 1, 1, 0);

		break;

	case 60:
		terminateMachine(_agentPoshExpressMach02);
		terminateMachine(_safariShadow3Mach);
		ws_unhide_walker(_G(my_walker));
		player_set_commands_allowed(true);

		break;

	case 71:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 13, 13, 42, _agentTalkLoopTjSeries, 13, 13, 0);
		break;

	case 72:

		sendWSMessage_150000(_G(my_walker), 54);
		break;

	case 73:
		_agentPoshExpressMach02 = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 768, 0, triggerMachineByHashCallback, "agent posh express");
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 11, -1, _agentTalkLoopTjSeries, 11, 11, 0);
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 11, 74, _701rp01Series, 11, 11, 0);

		break;

	case 74:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 19, -1, _701rp01Series, 10, 19, 4);
		sendWSMessage_1a0000(_agentPoshExpressMach02, 9);
		digi_play("701R07", 1, 255, 57, -1);

		break;

	case 75:
	case 76:
		setGlobals1(_ripTrekTalkerPos3Series, 1, 1, 1, 5, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		sendWSMessage_110000(_G(my_walker), 43);

		break;

	case 80:
		player_set_commands_allowed(false);
		player_update_info(_G(my_walker), &_G(player_info));
		_safariShadow3Mach = series_place_sprite("SAFARI SHADOW 3", 0, _G(player_info).x, _G(player_info).y, _G(player_info).scale, 3840);
		setGlobals1(_ripTrekHandTalkPos3Series, 1, 4, 4, 4, 0, 5, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		sendWSMessage_110000(_G(my_walker), 1080);
		digi_play("701R37", 1, 255, -1, -1);

		break;

	case 81:
		sendWSMessage_150000(_G(my_walker), -1);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X11", 1, 255, 96, -1);

		break;

	case 82:
		if (_G(flags[V286]) != 1 || _G(flags[V362]) || _G(flags[V372]) || _G(flags[V225])) {
			kernel_timing_trigger(1, 75, nullptr);
		} else {
			_G(flags[V225]) = 1;
			kernel_timing_trigger(1, 83, nullptr);
		}

		break;

	case 83:
		digi_play("701r42", 1, 255, 1083, -1);

		break;

	case 84:
		sendWSMessage_120000(_G(my_walker), -1);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 12, 12, 85, _agentTalkLoopTjSeries, 12, 12, 0);

		break;

	case 85:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 13, -1, _agentTalkLoopTjSeries, 11, 13, 1);
		sendWSMessage_1a0000(_agentPoshExpressMach, 11);
		digi_play("701X07", 1, 255, 86, -1);

		break;

	case 86:
		sendWSMessage_10000(1, _agentPoshExpressMach02, _agentTalkLoopTjSeries, 12, 12, -1, _agentTalkLoopTjSeries, 12, 12, 0);
		_ripSketchingInNotebookPos3Series = series_load("RIP SKETCHING IN NOTEBOOK POS 3", -1, nullptr);
		sendWSMessage_150000(_G(my_walker), -1);
		kernel_timing_trigger(1, 88, nullptr);

		break;

	case 88:
		setGlobals1(_ripSketchingInNotebookPos3Series, 1, 32, 32, 34, 1, 32, 32, 32, 32, 0, 32, 1, 1, 1, 0, 0, 0, 0, 0, 0);
		sendWSMessage_110000(_G(my_walker), 89);

		break;

	case 89:
		sendWSMessage_190000(_G(my_walker), 9);
		digi_play("950_S34", 2, 255, 97, 950);

		break;

	case 90:
		sendWSMessage_150000(_G(my_walker), 91);
		break;

	case 91:
		series_unload(_ripSketchingInNotebookPos3Series);
		ws_hide_walker(_G(my_walker));
		_agentPoshExpressMach02 = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 768, 0, triggerMachineByHashCallback, "agent posh express");
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 1, 11, 92, _701rp01Series, 11, 11, 0);

		break;

	case 92:
		terminateMachine(_agentPoshExpressMach02);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentGetTelegramSeries, 86, 1, 93, _agentGetTelegramSeries, 1, 1, 0);

		break;

	case 93:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 11, -1, _agentTalkLoopTjSeries, 11, 11, 0);
		_agentPoshExpressMach02 = TriggerMachineByHash(1, 1, 0, 0, 0, 0, 0, 0, 100, 768, 0, triggerMachineByHashCallback, "agent posh express");
		sendWSMessage_10000(1, _agentPoshExpressMach02, _701rp01Series, 11, 1, 94, _701rp01Series, 1, 1, 0);

		break;

	case 94:
		terminateMachine(_agentPoshExpressMach02);
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 11, 11, -1, _agentTalkLoopTjSeries, 11, 11, 0);
		ws_unhide_walker(_G(my_walker));
		setGlobals1(_ripTrekTalkerPos3Series, 1, 1, 1, 5, 1, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		kernel_timing_trigger(1, 76, nullptr);

		break;

	case 95:
		if (_G(flags[V286]) == 1 && !_G(flags[V362]))
			_G(flags[V372]) = 1;

		terminateMachine(_safariShadow3Mach);
		player_set_commands_allowed(true);

		break;

	case 96:
		sendWSMessage_10000(1, _agentPoshExpressMach, _agentTalkLoopTjSeries, 13, 13, 82, _agentTalkLoopTjSeries, 13, 13, 0);

		break;

	case 97:
		sendWSMessage_120000(_G(my_walker), 1089);

		break;

	case 100:
		kernel_timing_trigger(1, 102, nullptr);

		break;

	case 101:
		_field94 = 1000;
		_field98 = 1105;

		break;

	case 102:
		if (_field9E_triggerNum != -1) {
			kernel_timing_trigger(1, _field9E_triggerNum, nullptr);
			_field9E_triggerNum = -1;
		} else
			kernel_timing_trigger(1, 103, nullptr);

		break;

	case 103:
	case 110:
	case 111:
	case 948:
	case 1040:
	case 1080:
	case 1083:
	case 1089:
	case 2200:
	case 2201:
	case 2300:
	case 2301:
	case 2302:
	case 2303:
	case 2304:
	case 2305:
	case 2306:
	case 2307:
	case 2501:
	case 2504:
	case 2506:
	case 2509:
	case 2600:
	case 2601:
	case 2700:
	case 2701:
	case 2702:
		warning("Not yet implemented");
	default:
		break;
	}
}

void Room701::conv701a() {
	int32 node = _fieldB4 = conv_current_node();
	int32 entry = conv_current_entry();
	const char *digiName = conv_sound_to_play();

	if (digiName == nullptr) {
		conv_resume(conv_get_handle());
		return;
	}

	int32 who = conv_whos_talking();
	if (who <= 0) {
		if (node == 3 && entry == 0) {
			_convDigiName_1 = Common::String(digiName);
			_field94 = 3500;
			_field98 = 3501;
			return;
		}

		_field6C = 2101;

	} else if (who == 1) {
		if (node == 1 && entry == 1) {
			conv_set_box_xy(490, -4);
			set_dlg_rect();
			int32 x1, y1, x2, y2;
			conv_get_dlg_coords(&x1, &y1, &x2, &y2);
			conv_get_dlg_coords(&x1, &y1, &x2, &y2); // useless?
			conv_set_dlg_coords(x1, y1 - 10, x2, y2 - 10);
			set_dlg_rect();
		} else {
			conv_set_box_xy(10, 10);
		}

		switch (node) {
		case 1:
			if (entry == 3) {
				_convDigiName_2 = Common::String(digiName);
				_field94 = 3600;
				_field98 = 3601;

				return;
			}

			_field98 = 1102;

			break;

		case 6:
			if (entry == 0) {
				_field98 = 1102;
				digi_play(digiName, 1, 255, 1, -1);
				_field90 = 1;

				return;
			}

			_field98 = 1102;

			break;

		case 11:
			if (entry != 12) {
				_field94 = 3700;
				_field98 = 3701;

				return;
			}

			break;

		default:
			_field98 = 1102;
			break;
		}
	}

	digi_play(digiName, 1, 255, 1, -1);
}

void Room701::updateCounter() {
	if (_G(flags[V364]) == 1) {
		++_field50_counter;
		switch (_G(flags[V005])) {
		case 1:
			_G(flags[V351]) = 1;
			break;

		case 2:
			_G(flags[V352]) = 1;
			break;

		case 3:
			_G(flags[V353]) = 1;
			break;

		case 4:
			_G(flags[V354]) = 1;
			break;

		default:
			break;
		}
	}

	if (_G(flags[V365]) == 1) {
		_G(flags[V355]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V366]) == 1) {
		_G(flags[V356]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V367]) == 1) {
		_G(flags[V357]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V368]) == 1) {
		_G(flags[V358]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V369]) == 1) {
		_G(flags[V359]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V370]) == 1) {
		_G(flags[V360]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V371]) == 1) {
		_G(flags[V361]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V372]) == 1) {
		_G(flags[V362]) = 1;
		++_field50_counter;
	}

	if (_G(flags[V373]) == 1) {
		_G(flags[V363]) = 1;
		++_field50_counter;
	}
}

bool Room701::inventoryCheck() {
	for (int i = 0; i < 12; ++i)
		_fieldD0[i] = 0;

	_fieldFC_index = 0;

	if (inv_player_has("CRYSTAL SKULL"))
		_fieldD0[_fieldFC_index++] = 1;

	if (inv_player_has("STICK AND SHELL MAP"))
		_fieldD0[_fieldFC_index++] = 2;

	if (inv_player_has("WHEELED TOY"))
		_fieldD0[_fieldFC_index++] = 3;

	if (inv_player_has("REBUS AMULET"))
		_fieldD0[_fieldFC_index++] = 4;

	if (inv_player_has("SHRUNKEN HEAD"))
		_fieldD0[_fieldFC_index++] = 5;

	if (inv_player_has("SILVER BUTTERFLY"))
		_fieldD0[_fieldFC_index++] = 6;

	if (inv_player_has("POSTAGE STAMP"))
		_fieldD0[_fieldFC_index++] = 7;

	if (inv_player_has("GERMAN BANKNOTE"))
		_fieldD0[_fieldFC_index++] = 8;

	if (inv_player_has("WHALE BONE HORN"))
		_fieldD0[_fieldFC_index++] = 9;

	if (inv_player_has("CHISEL"))
		_fieldD0[_fieldFC_index++] = 10;

	if (inv_player_has("INCENSE BURNER"))
		_fieldD0[_fieldFC_index++] = 11;

	if (inv_player_has("ROMANOV EMERALD"))
		_fieldD0[_fieldFC_index++] = 12;

	return _fieldFC_index > 0;
}

} // namespace Rooms
} // namespace Riddle
} // namespace M4
