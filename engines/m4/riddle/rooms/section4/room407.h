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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef M4_RIDDLE_ROOMS_SECTION4_ROOM407_H
#define M4_RIDDLE_ROOMS_SECTION4_ROOM407_H

#include "m4/riddle/rooms/room.h"

namespace M4 {
namespace Riddle {
namespace Rooms {

class Room407 : public Room {
private:
	int _val1 = 0;
	int _val2 = 0;
	int _val3 = 0;
	int _val4 = 0;
	int _val5 = 0;
	int _val6 = 0;
	int _val7 = 0;
	int _val8 = 0;
	int _val9 = 0;
	int _val10 = 0;
	int _xyzzy1 = 0;
	int _xyzzy2 = 0;
	int _xyzzy3 = 0;
	int _xyzzy4 = 0;
	int _xyzzy5 = 0;
	int _xyzzy6 = 0;
	int _xyzzy7 = 0;
	int _xyzzy8 = 0;
	int _xyzzy9 = 0;
	int _xyzzy10 = 0;
	int _frotz1 = 0;
	int _frotz2 = 0;
	int _frotz3 = 0;
	int _frotz4 = 0;
	int _frotz5 = 0;
	int _frotz6 = 0;
	int _frotz7 = 0;
	int _frotz8 = 0;
	int _frotz9 = 0;
	int _frotz10 = 0;
	int _int1 = 0;
	int _int2 = 0;
	int _int3 = 0;
	int _int4 = 0;
	int _int5 = 0;
	int _int6 = 0;
	int _int7 = 0;
	int _buttonFrame1 = 0;
	int _buttonFrame2 = 0;
	int _buttonFrame3 = 0;
	int _buttonFrame4 = 0;
	int _int14 = 0;
	int _val15 = 0;
	int _val16 = 0;
	int _waterFlowTube = 0;
	int _waterFlowFaucet = 0;
	int _waterFlowStem = 0;
	machine *_bottle = nullptr;
	machine *_chart = nullptr;
	machine *_cpist = nullptr;
	machine *_drawer = nullptr;
	machine *_escape = nullptr;
	machine *_faucet1 = nullptr;
	machine *_faucet2 = nullptr;
	machine *_lever = nullptr;
	machine *_niche = nullptr;
	machine *_tpist = nullptr;
	machine *_pump = nullptr;
	machine *_bits = nullptr;
	machine *_star2 = nullptr;
	machine *_gears = nullptr;
	machine *_letter = nullptr;
	int _ripMedReach = 0;
	machine *_drawerPopup = nullptr;
	machine *_drawerPopupHose = nullptr;
	machine *_stopperInDrawer = nullptr;
	machine *_tubeInDrawer = nullptr;
	machine *_handleInDrawer = nullptr;
	machine *_tabletopPopup = nullptr;
	machine *_tabletopPopupWithItems1 = nullptr;
	machine *_tabletopPopupWithItems2 = nullptr;
	machine *_tabletopPopupWithItems3 = nullptr;
	machine *_pivotPopup = nullptr;
	machine *_glassTopPopup = nullptr;
	machine *_glassTopPopupWithItems1 = nullptr;
	machine *_glassTopPopupWithItems2 = nullptr;
	machine *_glassBottomWithItems1 = nullptr;
	machine *_glassBottomWithItems2 = nullptr;
	machine *_roofPiston = nullptr;
	machine *_roofPistonWithItems = nullptr;
	machine *_glassGone = nullptr;
	machine *_comboLockPopup = nullptr;
	int _comboLockNumerals = 0;
	int _407pu08b = 0;
	int _407pu08c = 0;
	int _407pu08d = 0;
	machine *_lockButton1 = nullptr;
	machine *_lockButton2 = nullptr;
	machine *_lockButton3 = nullptr;
	machine *_lockButton4 = nullptr;
	int _407h = 0;
	int _ripEnters = 0;
	int _stair = 0;
	machine *_ripley = nullptr;

	void setHotspots();

public:
	Room407() : Room() {}
	~Room407() override {}

	void preload() override;
	void init() override;
	void daemon() override;
	void pre_parser() override;
	void parser() override;
};

} // namespace Rooms
} // namespace Riddle
} // namespace M4

#endif
