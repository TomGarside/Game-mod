#ifndef __GAME_DIGSITE_H__
#define __GAME_DIGSITE_H__

#define SITEHEIGHT 10 
#define SITEWIDTH  5 
#define ORIGINX 10920.37
#define ORIGINY -7967.3
#define ORIGINZ 132.35
#define ACTIONPOINTS 10

#include "./idlib/precompiled.h"
#include "game/Game_local.h"
#include "siteSquare.h"

// represents dig site
class digSite {
	idVec3 siteCorner;
	siteSquare Squares [SITEHEIGHT][SITEWIDTH];
	float squareSide = 200.0f; 
	int gridHeight;
	int gridWidth;
	int actionPoints = 10; 


public:
	digSite(){}

	void buildSite(idVec3 origin);
	void spawnWave();
	void dig(idVec3 position, char* tool);
	void resetAp();
	void updateAp();
	void dropTelePoint();
private:


	char* digSite::genLootStr();

};
#endif __GAME_DIGSITE_H__
