#ifndef __GAME_DIGSITE_H__
#define __GAME_DIGSITE_H__

#define SITEHEIGHT 10 
#define SITEWIDTH  5 

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

public:
	digSite(){
		// init varaibles 
		//digSite::siteCorner = site;
	}

	void buildSite(idVec3 origin);

	void dig(idVec3 position, char* tool);

private:


	char* digSite::genLootStr();

};
#endif __GAME_DIGSITE_H__
