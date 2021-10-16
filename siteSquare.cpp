
#include "idlib/precompiled.h"
#pragma hdrstop

#include "siteSquare.h"
#include "game/Game_local.h"

void siteSquare::digSquare(char* tool) {
	gameLocal.Printf("tool used %s", tool);
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

void siteSquare::dropLoot() {
	gameLocal.Printf("droping %s ", siteSquare::getLootStr());
}
