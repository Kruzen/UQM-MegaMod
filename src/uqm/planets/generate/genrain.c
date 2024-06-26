//Copyright Paul Reiche, Fred Ford. 1992-2002

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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "genall.h"
#include "../planets.h"
#include "../../build.h"
#include "../../gendef.h"
#include "../../grpinfo.h"
#include "../../starmap.h"
#include "../../state.h"
#include "../../globdata.h"
#include "libs/mathlib.h"

static bool GenerateRainbowWorld_initNpcs (SOLARSYS_STATE *solarSys);
static bool GenerateRainbowWorld_generatePlanets (SOLARSYS_STATE *solarSys);
static bool GenerateRainbowWorld_generateOrbital (SOLARSYS_STATE *solarSys,
		PLANET_DESC *world);

const GenerateFunctions generateRainbowWorldFunctions = {
	/* .initNpcs         = */ GenerateRainbowWorld_initNpcs,
	/* .reinitNpcs       = */ GenerateDefault_reinitNpcs,
	/* .uninitNpcs       = */ GenerateDefault_uninitNpcs,
	/* .generatePlanets  = */ GenerateRainbowWorld_generatePlanets,
	/* .generateMoons    = */ GenerateDefault_generateMoons,
	/* .generateName     = */ GenerateDefault_generateName,
	/* .generateOrbital  = */ GenerateRainbowWorld_generateOrbital,
	/* .generateMinerals = */ GenerateDefault_generateMinerals,
	/* .generateEnergy   = */ GenerateDefault_generateEnergy,
	/* .generateLife     = */ GenerateDefault_generateLife,
	/* .pickupMinerals   = */ GenerateDefault_pickupMinerals,
	/* .pickupEnergy     = */ GenerateDefault_pickupEnergy,
	/* .pickupLife       = */ GenerateDefault_pickupLife,
};

static bool
GenerateRainbowWorld_initNpcs (SOLARSYS_STATE *solarSys)
{
	if (DIF_HARD && GET_GAME_STATE (SLYLANDRO_MULTIPLIER) > 0)
	{
		HIPGROUP hGroup, hNextGroup;
		BYTE angle, num_groups, which_group;

		if (!GetGroupInfo (GLOBAL (BattleGroupRef), GROUP_INIT_IP))
		{// This code will run if we have no battle group generated
		 // or all are expired
			GLOBAL (BattleGroupRef) = 0;
			/* 1-3, 3-5, 5-7, 7-9 Probes total */
			num_groups = (GET_GAME_STATE (SLYLANDRO_MULTIPLIER) * 2) - 1 +
					(COUNT)TFB_Random () % 3;
			which_group = 0;
			do
			{
				CloneShipFragment (SLYLANDRO_SHIP,
						&GLOBAL (npc_built_ship_q), 0);
				PutGroupInfo (GROUPS_RANDOM, ++which_group);
				ReinitQueue (&GLOBAL (npc_built_ship_q));
			} while (--num_groups);

			GetGroupInfo (GROUPS_RANDOM, GROUP_INIT_IP);
		}
		// Fresh groups or not - force probes to rotate around rainbow world
		// and not spread around the system
		angle = (COUNT)TFB_Random () % 9; // Initial angle = 0 - OCTANT
		for (hGroup = GetHeadLink (&GLOBAL (ip_group_q));
					hGroup; hGroup = hNextGroup)
		{
			IP_GROUP *GroupPtr;

			GroupPtr = LockIpGroup (&GLOBAL (ip_group_q), hGroup);
			hNextGroup = _GetSuccLink (GroupPtr);

			GroupPtr->task = IN_ORBIT;
			GroupPtr->sys_loc = solarSys->SunDesc[0].PlanetByte + 1;
			GroupPtr->dest_loc = GroupPtr->sys_loc;
			GroupPtr->orbit_pos = NORMALIZE_FACING (ANGLE_TO_FACING (angle));
			GroupPtr->group_counter = 0;
			UnlockIpGroup (&GLOBAL (ip_group_q), hGroup);

			// Next ship in queue will add random value to its angle 
			// between OCTANT and HALF_CIRCLE
			angle += ((COUNT)TFB_Random() % 25) + OCTANT;

			// Normalize angle
			if (angle > FULL_CIRCLE)
				angle -= FULL_CIRCLE;
		}
	}
	else
		GenerateDefault_initNpcs (solarSys);

	return true;
}

static bool
GenerateRainbowWorld_generatePlanets (SOLARSYS_STATE *solarSys)
{
	COUNT angle;

	solarSys->SunDesc[0].NumPlanets = (BYTE)~0;
	solarSys->SunDesc[0].PlanetByte = 0;

	if (!PrimeSeed)
		solarSys->SunDesc[0].NumPlanets = (RandomContext_Random (SysGenRNG) % (MAX_GEN_PLANETS - 1) + 1);

	FillOrbits (solarSys, solarSys->SunDesc[0].NumPlanets, solarSys->PlanetDesc, FALSE);
	GeneratePlanets (solarSys);

	solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].data_index = RAINBOW_WORLD;
	solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].NumPlanets = 0;
	solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].radius = EARTH_RADIUS * 50L / 100;
	angle = ARCTAN (solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].location.x,
			solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].location.y);
	if (angle <= QUADRANT)
		angle += QUADRANT;
	else if (angle >= FULL_CIRCLE - QUADRANT)
		angle -= QUADRANT;
	solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].location.x =
			COSINE (angle, solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].radius);
	solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].location.y =
			SINE (angle, solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].radius);
	ComputeSpeed (&solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte], FALSE, 1);

	if (!PrimeSeed)
		solarSys->PlanetDesc[solarSys->SunDesc[0].PlanetByte].NumPlanets = (RandomContext_Random (SysGenRNG) % MAX_GEN_MOONS);

	return true;
}

static bool
GenerateRainbowWorld_generateOrbital (SOLARSYS_STATE *solarSys, PLANET_DESC *world)
{
	if (matchWorld (solarSys, world, solarSys->SunDesc[0].PlanetByte, MATCH_PLANET))
	{
		BYTE which_rainbow;
		UWORD rainbow_mask;
		STAR_DESC *SDPtr;

		rainbow_mask = MAKE_WORD (
				GET_GAME_STATE (RAINBOW_WORLD0),
				GET_GAME_STATE (RAINBOW_WORLD1));

		which_rainbow = 0;
		SDPtr = &star_array[0];
		while (SDPtr != CurStarDescPtr)
		{
			if (SDPtr->Index == RAINBOW_DEFINED)
				++which_rainbow;
			++SDPtr;
		}
		rainbow_mask |= 1 << which_rainbow;
		SET_GAME_STATE (RAINBOW_WORLD0, LOBYTE (rainbow_mask));
		SET_GAME_STATE (RAINBOW_WORLD1, HIBYTE (rainbow_mask));
	}

	GenerateDefault_generateOrbital (solarSys, world);
	return true;
}