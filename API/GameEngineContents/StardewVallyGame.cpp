#include "StardewVallyGame.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"

StardewVallyGame::StardewVallyGame() 
{
}

StardewVallyGame::~StardewVallyGame() 
{
}

void StardewVallyGame::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}