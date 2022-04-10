#include "StardewVallyGame.h"
#include "FarmHouseLevel.h"
#include "TitleLevel.h"
#include "IntroLevel.h"
#include "FarmLevel.h"
#include "BusStopLevel.h"
#include "CoopLevel.h"
#include "MineEntryLevel.h"
#include "Mine1Level.h"
#include "Mine2Level.h"
#include "SeedShopLevel.h"
#include "TownLevel.h"
#include "Town2Level.h"
#include "AnimalShopLevel.h"
#include "ForestLevel.h"
#include "LobinHouseLevel.h"
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

	{
	// 현재 디렉토리
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");
	ResourcesDir.Move("Player");

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}
	}
	{

		// 현재 디렉토리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Title");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		// 현재 디렉토리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("UI");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Item");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		// 현재 디렉토리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Map");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	GameEngineImage* Body = GameEngineImageManager::GetInst()->Find("Body.bmp");
	Body->Cut({ 64, 128 });
	GameEngineImage* Hair = GameEngineImageManager::GetInst()->Find("Hair.bmp");
	Hair->Cut({ 64, 128 });
	GameEngineImage* Body2 = GameEngineImageManager::GetInst()->Find("Body2.bmp");
	Body2->Cut({ 64, 128 });
	GameEngineImage* Hair2 = GameEngineImageManager::GetInst()->Find("Hair2.bmp");
	Hair2->Cut({ 64, 128 });
	GameEngineImage* Shirts = GameEngineImageManager::GetInst()->Find("Shirts.bmp");
	Shirts->Cut({ 32, 32 });
	GameEngineImage* TitleButton = GameEngineImageManager::GetInst()->Find("TitleButton.bmp");
	TitleButton->Cut({ 222, 174 });
	GameEngineImage* CreateTile = GameEngineImageManager::GetInst()->Find("Menutile.bmp");
	CreateTile->Cut({ 64, 64 });
	GameEngineImage* BigLeaf = GameEngineImageManager::GetInst()->Find("BigLeaf.bmp");
	BigLeaf->CutCount(3,1);
	GameEngineImage* SmallLeaf = GameEngineImageManager::GetInst()->Find("SmallLeaf.bmp");
	SmallLeaf->CutCount(3, 1);
	GameEngineImage* Tools = GameEngineImageManager::GetInst()->Find("Tools.bmp");
	Tools->CutCount(21, 12);
	GameEngineImage* WeaPons = GameEngineImageManager::GetInst()->Find("WeaPons.bmp");
	WeaPons->CutCount(8, 9);

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<FarmHouseLevel>("FarmHouseLevel");
	CreateLevel<IntroLevel>("IntroLevel");
	CreateLevel<FarmLevel>("FarmLevel");
	CreateLevel<CoopLevel>("CoopLevel");
	CreateLevel<AnimalShopLevel>("AnimalShopLevel");
	CreateLevel<ForestLevel>("ForestLevel");
	CreateLevel<TownLevel>("TownLevel");
	CreateLevel<Town2Level>("Town2Level");
	CreateLevel<LobinHouseLevel>("LobinHouseLevel");
	CreateLevel<BusStopLevel>("BusStopLevel");
	CreateLevel<SeedShopLevel>("SeedShopLevel");
	CreateLevel<MineEntryLevel>("MineEntryLevel");
	CreateLevel<Mine1Level>("Mine1Level");
	CreateLevel<Mine2Level>("Mine2Level");
	ChangeLevel("FarmLevel");
}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}