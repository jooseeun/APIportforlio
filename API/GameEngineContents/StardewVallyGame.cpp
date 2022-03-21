#include "StardewVallyGame.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

StardewVallyGame::StardewVallyGame() 
{
}

StardewVallyGame::~StardewVallyGame() 
{
}

void StardewVallyGame::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}