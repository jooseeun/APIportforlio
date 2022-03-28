#include "StardewVallyGame.h"
#include "FarmHouseLevel.h"
#include "TitleLevel.h"
#include "IntroLevel.h"
#include "FarmLevel.h"
#include "BusStopLevel.h"
#include "CoopLevel.h"
#include "Mine1Level.h"
#include "Mine2Level.h"
#include "PlayerCreateLevel.h"
#include "ShopLevel.h"
#include "TownLevel.h"
#include "Town2Level.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
StardewVallyGame::StardewVallyGame() 
{
}

StardewVallyGame::~StardewVallyGame() 
{
}

void StardewVallyGame::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	

	// ���� ���丮
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Body.bmp");
	Image->Cut({ 64, 128 });

	if (false == GameEngineInput::GetInst()->IsKey("FarmHouseLevel"))
	{
		// �̶� �빮�ڿ��� �մϴ�.
		GameEngineInput::GetInst()->CreateKey("FarmHouseLevel", '1');
		GameEngineInput::GetInst()->CreateKey("TitleLevel", '2');
	}


	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<FarmHouseLevel>("FarmHouseLevel");
	CreateLevel<PlayerCreateLevel>("PlayerCreateLevel");
	CreateLevel<IntroLevel>("IntroLevel");
	CreateLevel<FarmLevel>("FarmLevel");
	CreateLevel<CoopLevel>("CoopLevel");
	CreateLevel<BusStopLevel>("BusStopLevel");
	CreateLevel<ShopLevel>("ShopLevel");
	CreateLevel<Mine1Level>("Mine1Level");
	CreateLevel<Mine2Level>("Mine2Level");
	ChangeLevel("TitleLevel");

}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}