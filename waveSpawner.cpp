

#include "idlib/precompiled.h"
#pragma hdrstop

#include "waveSpawner.h"
#include "game/Game_local.h"
#include "game/spawner.h"

void waveSpawner::spawnMonster(idVec3 spawnlocation, char* monsterString) {
		idDict	  dict;
		float	  yaw;
		idPlayer* player = gameLocal.GetLocalPlayer();
		idEntity* newEnt = NULL;

		// get player direction 
		yaw = player->viewAngles.yaw;

		dict.Set("classname", monsterString);
		dict.Set("angle", va("%f",yaw));

		// validate location before spawning 
		dict.Set("origin", spawnlocation.ToString());
		


		// spawn new entity 
		gameLocal.SpawnEntityDef(dict, &newEnt);
		// play effect on spawn 
		//gameLocal.PlayEffect(spawnArgs, "fx_impact", origin, axis, false, vec3_origin, true);	
}

idVec3 waveSpawner::offSetLocation() {
	idVec3 newLocation;
	float randx = rvRandom::flrand(-300.0f, 300.0f);
	float randy = rvRandom::flrand(-300.0f, 300.0f);
	newLocation.Set(waveSpawner::spawnlocation.x + randx, waveSpawner::spawnlocation.y + randy, waveSpawner::spawnlocation.z);
	return newLocation;
}

void waveSpawner::spawnWave() {
	
	gameLocal.Printf("num waves %d\n", waveSpawner::numWaves);
	//spawn low level enemies 
	gameLocal.Printf("spawning wave of %d :%s at %s\n", waveSpawner::numWaves * waveSpawner::weakMonsterCount, waveSpawner::weakMonsterString, spawnlocation.ToString());
	for (int e = 0; e < waveSpawner::numWaves * waveSpawner::weakMonsterCount; e++) {
		// calc spawn location 
				waveSpawner::spawnMonster(waveSpawner::offSetLocation(), waveSpawner::weakMonsterString);	 
	}
	gameLocal.Printf("spawning wave of %d :%s at %s\n", waveSpawner::numWaves * waveSpawner::medMonsterCount, waveSpawner::medMonsterString, spawnlocation.ToString());
	//spawn tough guys 
	for (int e = 0; e < waveSpawner::numWaves * waveSpawner::medMonsterCount; e++) {
			waveSpawner::spawnMonster(waveSpawner::offSetLocation(), waveSpawner::medMonsterString);
	}
	// spawn really tough guy 
	gameLocal.Printf("spawning wave of %d :%s at %s\n", waveSpawner::numWaves * waveSpawner::megaMonsterCount, waveSpawner::megaMonsterString, spawnlocation.ToString());
	for (int e = 0; e < waveSpawner::numWaves * waveSpawner::megaMonsterCount; e++) {
			waveSpawner::spawnMonster(waveSpawner::offSetLocation(), waveSpawner::megaMonsterString);
	}

   
}


