#ifndef __GAME_WAVESPAWNER_H__
#define __GAME_WAVWSPAWNER_H__

#include "idlib/precompiled.h"
#include "game/Game_local.h"
#include "game/spawner.h"

// spawns waves of monsters 
class waveSpawner {
	int numWaves = 1;

	//location is center of spawn group 
	idVec3 spawnlocation; 
	// direction 
	idMat3     direction;

	char* weakMonsterString;
	char* medMonsterString;
	char* megaMonsterString;

	// monster count for testing put this in def ?
	int weakMonsterCount = 5;
	int medMonsterCount = 2;
	int megaMonsterCount = 1;
	int count = 0;

	//idEntity* monsters[1000]; 

	
public:
	waveSpawner(idVec3 spawnLocation, idMat3 direction, char* weakMonsterString,char* medMonsterString, char* megaMonsterString, int numWaves ) {
		// init varaibles 
		waveSpawner::spawnlocation = spawnLocation; 
		waveSpawner::weakMonsterString = weakMonsterString;
		waveSpawner::medMonsterString = medMonsterString;
		waveSpawner::megaMonsterString = megaMonsterString;
		waveSpawner::direction = direction;
		waveSpawner::numWaves = numWaves;

		
	}


	// spawns a number of enemies based on wave count 

	void spawnWave();

private:
	void spawnMonster(idVec3, char*, char*, int);

	idVec3 offSetLocation();


};
#endif __GAME_WAVESPAWNER_H__
