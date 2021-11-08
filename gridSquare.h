
#include "idlib/precompiled.h"
#include "game/Game_local.h"

// contains the suquares used in Archeology mechanic 
class gridSquare
{   
	//corner point in 3d space
	idVec3 corner;
	//length of edges(its a square)
	float sideLength;

	//entity name of loot spawned 
	char* loot;
	// depth of loot in square
	int depthOfLoot; 
	// amount of dirt dug so far 
	int amountDug;
	// amountof damage done so far 
	int lootDamage;


	// initialization 
	gridSquare(idVec3 cornerPoint) {
		gridSquare::corner = cornerPoint;
	}

	void spawnLoot();

	void digSquare(char* tool);

	void spawnLoot();


};
