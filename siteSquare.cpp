
#include "idlib/precompiled.h"
#pragma hdrstop

#include "siteSquare.h"
#include "game/Game_local.h"

void siteSquare::digSquare(char* tool) {
	gameLocal.Printf("tool used %s", tool);
}

void siteSquare::setLootStr(char* newLootStr) {
	siteSquare::lootString = newLootStr;
}
char* siteSquare::getLootStr() {
	return siteSquare::lootString;
}

void siteSquare::setTopPoint(idVec3 newTopPoint) {
	siteSquare::topPoint = newTopPoint;
}
idVec3 siteSquare::getTopPoint() {
	return siteSquare::topPoint;
}

void siteSquare::dropLoot() {
	gameLocal.Printf("droping %s ", siteSquare::getLootStr());
		idDict	  dict;
		float	  yaw;
		idPlayer* player = gameLocal.GetLocalPlayer();
		idEntity* newEnt = NULL;

		// get player direction 
		yaw = player->viewAngles.yaw;

		dict.Set("classname", siteSquare::lootString);
		dict.Set("angle", va("%f", yaw));

		// validate location before spawning 
		dict.Set("origin", siteSquare::topPoint.ToString());



		// spawn new entity 
		gameLocal.SpawnEntityDef(dict, &newEnt);
		// play effect on spawn 
		//gameLocal.PlayEffect(spawnArgs, "fx_impact", origin, axis, false, vec3_origin, true);	
	}