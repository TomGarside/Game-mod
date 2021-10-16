#ifndef __GAME_SITESQUARE_H__
#define __GAME_SITESQUARE_H__

#include "idlib/precompiled.h"
#include "game/Game_local.h"

// represents a single square in site
class siteSquare {
	
	//top corner 
	idVec3 topPoint; 
	//its a square
	const float sideLen = 300; 

	// type of loot 
	char* lootString; 

	//loot depth 
	int lootDepth; 

	//amount dug
	int AmountDug; 

	// damage done to loot %
	int lootdamage; 

public:

	// dig in Square 
	void digSquare(char* tool);

	void setLootStr(char*); 
	char* getLootStr();

	void setTopPoint(idVec3);
	idVec3 getTopPoint();

	void dropLoot();
	 


};
#endif __GAME_SITESQUARE_H__
