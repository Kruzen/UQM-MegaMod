/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * This file contains definitions relating to using strings specific to
 * the game. libs/strlib.h is for the string library.
 */

#ifndef UQM_GAMESTR_H_
#define UQM_GAMESTR_H_


#include "libs/strlib.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define STAR_STRING_COUNT       149
#define DEVICE_STRING_COUNT      29
#define CARGO_STRING_COUNT       14
#define ELEMENTS_STRING_COUNT   133
#define SCAN_STRING_COUNT        66
#define STAR_NUMBER_COUNT        14
#define PLANET_NUMBER_COUNT      43
#define MONTHS_STRING_COUNT      12
#define FEEDBACK_STRING_COUNT     8
#define STARBASE_STRING_COUNT    42
#define ENCOUNTER_STRING_COUNT    8
#define NAVIGATION_STRING_COUNT   9
#define NAMING_STRING_COUNT       8
#define MELEE_STRING_COUNT       25
#define SAVEGAME_STRING_COUNT     8
#define OPTION_STRING_COUNT      10
#define QUITMENU_STRING_COUNT     5
#define STATUS_STRING_COUNT      22
#define FLAGSHIP_STRING_COUNT    13
#define ORBITSCAN_STRING_COUNT   19
#define MAINMENU_STRING_COUNT    74
#define NETMELEE_STRING_COUNT    34
#define BIOLOGICAL_STRING_COUNT  26
#define PLAYMENU_STRING_COUNT    30
#define LABEL_STRING_COUNT       26

enum {
	STAR_STRING_BASE       = 0,
	DEVICE_STRING_BASE     = STAR_STRING_BASE + STAR_STRING_COUNT,
	CARGO_STRING_BASE      = DEVICE_STRING_BASE + DEVICE_STRING_COUNT,
	ELEMENTS_STRING_BASE   = CARGO_STRING_BASE + CARGO_STRING_COUNT,
	SCAN_STRING_BASE       = ELEMENTS_STRING_BASE + ELEMENTS_STRING_COUNT,
	STAR_NUMBER_BASE       = SCAN_STRING_BASE + SCAN_STRING_COUNT,
	PLANET_NUMBER_BASE     = STAR_NUMBER_BASE + STAR_NUMBER_COUNT,
	MONTHS_STRING_BASE     = PLANET_NUMBER_BASE + PLANET_NUMBER_COUNT,
	FEEDBACK_STRING_BASE   = MONTHS_STRING_BASE + MONTHS_STRING_COUNT,
	STARBASE_STRING_BASE   = FEEDBACK_STRING_BASE + FEEDBACK_STRING_COUNT,
	ENCOUNTER_STRING_BASE  = STARBASE_STRING_BASE + STARBASE_STRING_COUNT,
	NAVIGATION_STRING_BASE = ENCOUNTER_STRING_BASE + ENCOUNTER_STRING_COUNT,
	NAMING_STRING_BASE     = NAVIGATION_STRING_BASE + NAVIGATION_STRING_COUNT,
	MELEE_STRING_BASE      = NAMING_STRING_BASE + NAMING_STRING_COUNT,
	SAVEGAME_STRING_BASE   = MELEE_STRING_BASE + MELEE_STRING_COUNT,
	OPTION_STRING_BASE     = SAVEGAME_STRING_BASE + SAVEGAME_STRING_COUNT,
	QUITMENU_STRING_BASE   = OPTION_STRING_BASE + OPTION_STRING_COUNT,
	STATUS_STRING_BASE     = QUITMENU_STRING_BASE + QUITMENU_STRING_COUNT,
	FLAGSHIP_STRING_BASE   = STATUS_STRING_BASE + STATUS_STRING_COUNT,
	ORBITSCAN_STRING_BASE  = FLAGSHIP_STRING_BASE + FLAGSHIP_STRING_COUNT,
	MAINMENU_STRING_BASE   = ORBITSCAN_STRING_BASE + ORBITSCAN_STRING_COUNT,
	NETMELEE_STRING_BASE   = MAINMENU_STRING_BASE + MAINMENU_STRING_COUNT,
	BIOLOGICAL_STRING_BASE = NETMELEE_STRING_BASE + NETMELEE_STRING_COUNT,
	PLAYMENU_STRING_BASE   = BIOLOGICAL_STRING_BASE + BIOLOGICAL_STRING_COUNT,
	LABEL_STRING_BASE      = PLAYMENU_STRING_BASE + PLAYMENU_STRING_COUNT,

	GAMESTR_COUNT          = LABEL_STRING_BASE + LABEL_STRING_COUNT
};


#define GAME_STRING(i) ((UNICODE *)GetStringAddress (SetAbsStringTableIndex (GameStrings, (i))))
#define GET_STRING(s,i) ((UNICODE *)GetStringAddress (SetAbsStringTableIndex ((s), (i))))

extern STRING GameStrings;

extern void SetCursorRect (RECT *r, CONTEXT context);
extern void FlushCursorRect (void);
void SetCursorFlashBlock (BOOLEAN state);

#if defined(__cplusplus)
}
#endif

#endif  /* UQM_GAMESTR_H_ */

