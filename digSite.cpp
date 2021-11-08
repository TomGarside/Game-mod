#include "idlib/precompiled.h"
#pragma hdrstop

#include "digSite.h"
#include "waveSpawner.h"
#include "game/Game_local.h"

void digSite::buildSite(idVec3 origin) {
	digSite::siteCorner = origin;
	// set up all the squares 
	for (int x = 0; x < SITEHEIGHT; x++) {
		for (int y = 0; y < SITEWIDTH; y++) {

			// calc new vect for point 
			idVec3 newPoint;
			idVec3 centerPoint;
			float newX = digSite::siteCorner.x - ((x + 1) * digSite::squareSide);
			float newY = digSite::siteCorner.y - ((y + 1) * digSite::squareSide);
			newPoint.Set(newX, newY, digSite::siteCorner.z);
			centerPoint.Set(newX - (digSite::squareSide / 2), newY - (digSite::squareSide / 2), digSite::siteCorner.z);

			digSite::Squares[x][y].setTopPoint(newPoint);

			// generate Loot string 
			digSite::Squares[x][y].setLootStr(digSite::genLootStr());

			// set loot depth 
			digSite::Squares[x][y].setLootDepth(rvRandom::irand(1, 30));

			digSite::Squares[x][y].setCenter(centerPoint);

			// draw lines ?? 
			//gameLocal.Printf("built square %i %i loot %s\n", x + 1, y + 1, digSite::Squares[x][y].getLootStr());

			digSite::Squares[x][y].dropFlags();

		}
		
		dropTelePoint(origin, "tom_spawn_flag");
	}
	
	updateAp();

}
void digSite::dropTelePoint(idVec3 origin, char * name ) {
	
	idDict	  dict;
	float	  yaw;
	idPlayer* player = gameLocal.GetLocalPlayer();
	idEntity* newEnt = NULL;

	// get player direction 
	yaw = player->viewAngles.yaw;

	dict.Set("classname", "tom_flag");
	dict.Set("angle", va("%f", yaw));

	// validate location before spawning 
	dict.Set("origin", origin.ToString());

	dict.Set("name",name);

	// spawn new entity 
	if (!gameLocal.FindEntity("tom_spawn_flag")) {
		gameLocal.SpawnEntityDef(dict, &newEnt);
	}
}

void  digSite::dig(char* tool) {

	idVec3		end;
	trace_t		tr;
	int			contents;
	idEntity* ignore;
	idPlayer* player; 
	char*     msg;
	


	player = gameLocal.GetLocalPlayer();

	idClip* clipWorld = gameLocal.GetEntityClipWorld(player);
	idVec3 playerViewOrigin = player->firstPersonViewOrigin;
	idMat3 playerViewAxis = player->firstPersonViewAxis;
	// TODO fix this to a shorter range 
	end = playerViewOrigin + ((20 * 16) * playerViewAxis[0]);
	end += (playerViewAxis[1]);
	end += (playerViewAxis[2]);

	gameLocal.Printf("digging with %s \n ", tool);
	//trace point hit 

	clipWorld->TracePoint(tr, playerViewOrigin, end, 1, player);



	gameLocal.Printf("tr fraction %f\n", tr.fraction);
	// trace met somthing 
	if (tr.fraction < 1.0f) {
		int xBox = int((digSite::siteCorner.x - tr.endpos.x) / digSite::squareSide) - 1;
		int yBox = int((digSite::siteCorner.y - tr.endpos.y) / digSite::squareSide) - 1;
		gameLocal.Printf("box = x:%d %d y:%d %d\n", xBox, SITEHEIGHT, yBox, SITEWIDTH);

		if (xBox >= 0 && yBox >= 0 && xBox <= SITEHEIGHT && yBox <= SITEWIDTH) {
			// not alowed to dig at night 
			if (gameLocal.GetLocalPlayer()->nightTime) {
				gameLocal.Printf("cant dig at night");
				msg = "Its not safe to dig at night";

			}
			else if (digSite::Squares[xBox][yBox].getExcavated()) {
				gameLocal.Printf("already dug");
				msg = "You already dug hear!";
				
			}
			else {
				gameLocal.Printf("ok to dig ");
				digSite::actionPoints--;
				digSite::Squares[xBox][yBox].digSquare(tool);
				
			}
			gameLocal.GetLocalPlayer()->GUIMainNotice(msg);
			if (digSite::actionPoints <= 0 && !gameLocal.GetLocalPlayer()->nightTime) {
				char* msg = "Used all action points the sun sets....";
				gameLocal.GetLocalPlayer()->GUIMainNotice(msg);
				digSite::spawnWave();
			}
		}
    }
	updateAp();
	

}

//TODO sort out gun and powerup drops 
char* digSite::genLootStr() {
	int randLoot = rvRandom::irand(1, 12);
	char* loot;
	switch (randLoot) {
	case 12:
		loot = "weapon_napalmgun";
		break;
	case 11:
		loot = "powerup_regeneration";
		break;
	case 10:
		loot = "powerup_ammoregen";
		break;

	case 9:
		loot = "weapon_dmg";
		break;
		
	case 8:
		loot = "weapon_hyperblaster";
		break;
	case 7:
		loot = "weapon_grenadelauncher";
		break;
	case 6:
		loot = "weapon_lightninggun";
		break;
	case 5:
		loot = "powerup_haste";
		break; 
	case 4:
		loot = "weapon_nailgun";
		break;
	case 3:
		loot = "powerup_quad_damage";
		break;
	case 2:
		loot = "weapon_railgun";
		break;
	case 1:
		loot = "weapon_nailgun";
		break;
	default:
		loot = "weapon_railgun";
	}

	gameLocal.Printf("Spawning loot %s %i \n ", loot);

	return loot;

		//placeholder 
		//return "tom_flag";
}

void digSite::spawnWave() {
		// load wave number from cvar 
		idCVar* waveVar = cvarSystem->Find("t_numWaves");
		int wave = waveVar->GetInteger();

		idMat3 axis;

		waveSpawner monsterWave(digSite::Squares[SITEHEIGHT / 2][SITEWIDTH / 2].getCenter(), axis, "monster_strogg_marine", "monster_gunner", "monster_gladiator", wave);
		monsterWave.spawnWave();
		//update wave 

		waveVar->SetInteger(++wave);

}
void digSite::resetAp() {
	digSite::actionPoints = ACTIONPOINTS;
	updateAp();
}

void digSite::updateAp() {
	char apStr[20];
	itoa(digSite::actionPoints, apStr, 10);
	gameLocal.Printf(apStr);
	gameLocal.GetLocalPlayer()->GUIFragNotice(apStr);
}