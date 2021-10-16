#ifndef __GAME_DIGSITE_H__
#define __GAME_DIGSITE_H__

#define SITEHEIGHT 20 
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
	digSite(idVec3 topPoint){
		// init varaibles 
		digSite::siteCorner = topPoint;

		// set up all the squares 
		for (int x = 0; x < SITEHEIGHT; x++) {
			for (int y = 0; y < SITEWIDTH; y++) {

				// calc new vect for point 
				idVec3 newPoint;
				float newX = digSite::siteCorner.x - ((x+1) * digSite::squareSide);
				float newY = digSite::siteCorner.y - ((y+1) * digSite::squareSide);
				newPoint.Set(newX, newY, digSite::siteCorner.z);
			  
				digSite::Squares[x][y].setTopPoint(newPoint);

				// generate Loot string 
				digSite::Squares[x][y].setLootStr(digSite::genLootStr());

				// draw lines ?? 
				gameLocal.Printf("built square %i %i loot %s\n", x + 1, y + 1, digSite::Squares[x][y].getLootStr());

				digSite::Squares[x][y].dropLoot();
			}

		}
			

	}

private:

	char* digSite::genLootStr() {
		//placeholder 
		return "weapon_machinegun";
	}

	
	
};
#endif __GAME_DIGSITE_H__
