#ifndef __GAME_SITESQUARE_H__
#define __GAME_SITESQUARE_H__

#define SHOVEL "shovel"
#define TROWEL "trowel"
#define BRUSH  "brush"
#define SHOVELDIG 5
#define TROWELDIG 3 
#define BRUSHDIG 1 
#define SHOVELDAMAGERANGE  20
#define TROWELDAMAGERANGE  5
#define TROWELDAMAGE 20
#define SHOVELDAMAGE 45

#include "idlib/precompiled.h"
#include "game/Game_local.h"

// represents a single square in site
class siteSquare {
	
	//top corner 
	idVec3 topPoint; 

	//its a square
	const float sideLen = 300; 
    
	// center
	idVec3 squareCenter;

	// type of loot 
	char* lootString; 

	//loot depth 
	int lootDepth; 

	//amount dug
	int AmountDug = 0; 

	// damage done to loot %
	int lootdamage = 0; 

	// loot spawned 
	int lootSpawned = 0; 

public:

	// dig in Square 
	void digSquare(char* tool);

	void setLootStr(char*); 
	char* getLootStr();

	void setLootDepth(int); 
	int getLootDepth(); 

	// get randomly generated corpse parts 
	char* getDead(); 

	void setTopPoint(idVec3);
	idVec3 getTopPoint();

	void setCenter(idVec3);
	idVec3 getCenter();

	void dropFlags();
	void dropLoot();
	void dropJunk(); 
	 


};
#endif __GAME_SITESQUARE_H__
