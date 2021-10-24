
#include "idlib/precompiled.h"
#pragma hdrstop

#include "siteSquare.h"
#include "game/Game_local.h"

void siteSquare::digSquare(char* tool) {

	// check tool and subtract amount 
	if (tool == SHOVEL) {
		if (siteSquare::AmountDug < SHOVELDAMAGERANGE) {
			siteSquare::lootdamage = siteSquare::lootdamage + SHOVELDAMAGE ;
		}
		siteSquare::AmountDug = siteSquare::AmountDug + SHOVELDIG;
	}
	else if (tool == TROWEL) {
		if (siteSquare::AmountDug < TROWELDAMAGERANGE) {
			siteSquare::lootdamage = siteSquare::lootdamage + TROWELDAMAGE ;
		}
		siteSquare::AmountDug = siteSquare::AmountDug + TROWELDIG;
	}
	else if (tool == BRUSH) {
		siteSquare::AmountDug = siteSquare::AmountDug + BRUSHDIG; 
	}

	gameLocal.Printf(" tool used %s dug:%d of %d damage: %d\n",tool,  siteSquare::AmountDug, siteSquare::lootDepth, siteSquare::lootdamage);

	if (siteSquare::AmountDug >= siteSquare::lootDepth && !siteSquare::lootSpawned) {
		// check loot damage drop loot
		if (siteSquare::lootdamage > 100) {
			// broken loot :(
			siteSquare::setLootStr(siteSquare::getDead()); 
			siteSquare::dropLoot(); 
			siteSquare::lootSpawned = 1;
		}
		else {
			siteSquare::lootSpawned = 1; 
			siteSquare::dropLoot(); 

		}
	}

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
void siteSquare::setCenter(idVec3 newTopPoint) {
	siteSquare::squareCenter = newTopPoint;
}
idVec3 siteSquare::getCenter() {
	return siteSquare::squareCenter;
}
void siteSquare::setLootDepth(int depth) {
	siteSquare::lootDepth = depth;
}
int siteSquare::getLootDepth() {
	return siteSquare::lootDepth;
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
		dict.Set("origin", siteSquare::squareCenter.ToString());



		// spawn new entity 
		gameLocal.SpawnEntityDef(dict, &newEnt);
		// play effect on spawn 
		//gameLocal.PlayEffect(spawnArgs, "fx_impact", origin, axis, false, vec3_origin, true);	
	}

// return a random dead marine chunk 
char* siteSquare::getDead() {
	int randDead = rvRandom::irand(1, 100);
	char* gibs;
	switch (randDead / 10) {
	case 9:
	case 8:
		gibs = "env_dead_chestwoundbody";
		break;
	case 7:
		gibs = "env_dead_d_arm";
		break;
	case 6:
		gibs = "env_dead_d_leg";
		break;
	case 5:
	case 4:
		gibs = "env_dead_d_leg_clean";
		break;
	default:
		gibs = "env_dead_half";
	}

	gameLocal.Printf("Spawning marine chunks %s %i \n ", gibs, randDead / 10);

	return gibs;


}

void siteSquare::dropFlags() {
	idDict	  dict;
	float	  yaw;
	idPlayer* player = gameLocal.GetLocalPlayer();
	idEntity* newEnt = NULL;
	idVec3  top2;
	idVec3  top3;
	idVec3  top4;

	// get player direction 
	yaw = player->viewAngles.yaw;

    dict.Set("classname", "tom_flag");
	dict.Set("angle", va("%f", yaw));
	top2.Set(siteSquare::topPoint.x - 200, siteSquare::topPoint.y, siteSquare::topPoint.z);
	top3.Set(siteSquare::topPoint.x, siteSquare::topPoint.y-200, siteSquare::topPoint.z);
	top4.Set(siteSquare::topPoint.x - 200, siteSquare::topPoint.y-200, siteSquare::topPoint.z);


	// validate location before spawning 
	dict.Set("origin", siteSquare::topPoint.ToString()); 
	gameLocal.SpawnEntityDef(dict, &newEnt);


	dict.Set("origin", top2.ToString());
	gameLocal.SpawnEntityDef(dict, &newEnt);
 
	dict.Set("origin", top3.ToString());
	gameLocal.SpawnEntityDef(dict, &newEnt);

	dict.Set("origin", top4.ToString());
	gameLocal.SpawnEntityDef(dict, &newEnt);
}
