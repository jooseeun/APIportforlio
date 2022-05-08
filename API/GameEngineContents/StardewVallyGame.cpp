#include "StardewVallyGame.h"
#include "FarmHouseLevel.h"
#include "TitleLevel.h"
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
#include "RobinShopLevel.h"
#include "BackWoodLevel.h"
#include "BarnLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>

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
		// 현재 디렉토리
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Animal");

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
		ResourcesDir.Move("Mine");

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
		ResourcesDir.Move("NPC");

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
	{

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Sound");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}

	}
	{

		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Environment");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

	}


	GameEngineImage* BodyShirts1 = GameEngineImageManager::GetInst()->Find("BodyShirts1.bmp");
	BodyShirts1->Cut({ 64, 128 });
	GameEngineImage* BodyShirts2 = GameEngineImageManager::GetInst()->Find("BodyShirts2.bmp");
	BodyShirts2->Cut({ 64, 128 });
	GameEngineImage* BodyShirts3 = GameEngineImageManager::GetInst()->Find("BodyShirts3.bmp");
	BodyShirts3->Cut({ 64, 128 });

	GameEngineImage* BodyLShirts1 = GameEngineImageManager::GetInst()->Find("BodyLShirts1.bmp");
	BodyLShirts1->Cut({ 64, 128 });
	GameEngineImage* BodyLShirts2 = GameEngineImageManager::GetInst()->Find("BodyLShirts2.bmp");
	BodyLShirts2->Cut({ 64, 128 });
	GameEngineImage* BodyLShirts3 = GameEngineImageManager::GetInst()->Find("BodyLShirts3.bmp");
	BodyLShirts3->Cut({ 64, 128 });

	GameEngineImage* Hair1Black = GameEngineImageManager::GetInst()->Find("Hair1Black.bmp");
	Hair1Black->Cut({ 64, 128 });
	GameEngineImage* Hair1Red = GameEngineImageManager::GetInst()->Find("Hair1Red.bmp");
	Hair1Red->Cut({ 64, 128 });
	GameEngineImage* Hair1Blue = GameEngineImageManager::GetInst()->Find("Hair1Blue.bmp");
	Hair1Blue->Cut({ 64, 128 });

	GameEngineImage* HairL1Black = GameEngineImageManager::GetInst()->Find("HairL1Black.bmp");
	HairL1Black->Cut({ 64, 128 });
	GameEngineImage* HairL1Red = GameEngineImageManager::GetInst()->Find("HairL1Red.bmp");
	HairL1Red->Cut({ 64, 128 });
	GameEngineImage* HairL1Blue = GameEngineImageManager::GetInst()->Find("HairL1Blue.bmp");
	HairL1Blue->Cut({ 64, 128 });

	GameEngineImage* Hair2Black = GameEngineImageManager::GetInst()->Find("Hair2Black.bmp");
	Hair2Black->Cut({ 64, 128 });
	GameEngineImage* Hair2Red = GameEngineImageManager::GetInst()->Find("Hair2Red.bmp");
	Hair2Red->Cut({ 64, 128 });
	GameEngineImage* Hair2Blue = GameEngineImageManager::GetInst()->Find("Hair2Blue.bmp");
	Hair2Blue->Cut({ 64, 128 });

	GameEngineImage* HairL2Black = GameEngineImageManager::GetInst()->Find("HairL2Black.bmp");
	HairL2Black->Cut({ 64, 128 });
	GameEngineImage* HairL2Red = GameEngineImageManager::GetInst()->Find("HairL2Red.bmp");
	HairL2Red->Cut({ 64, 128 });
	GameEngineImage* HairL2Blue = GameEngineImageManager::GetInst()->Find("HairL2Blue.bmp");
	HairL2Blue->Cut({ 64, 128 });


	GameEngineImage* Shirts1 = GameEngineImageManager::GetInst()->Find("Shirts1.bmp");
	Shirts1->Cut({ 64, 128 });
	GameEngineImage* Shirts2 = GameEngineImageManager::GetInst()->Find("Shirts2.bmp");
	Shirts2->Cut({ 64, 128 });
	GameEngineImage* Shirts3 = GameEngineImageManager::GetInst()->Find("Shirts3.bmp");
	Shirts3->Cut({ 64, 128 });
	GameEngineImage* ShirtsL1 = GameEngineImageManager::GetInst()->Find("ShirtsL1.bmp");
	ShirtsL1->Cut({ 64, 128 });
	GameEngineImage* ShirtsL2 = GameEngineImageManager::GetInst()->Find("ShirtsL2.bmp");
	ShirtsL2->Cut({ 64, 128 });
	GameEngineImage* ShirtsL3 = GameEngineImageManager::GetInst()->Find("ShirtsL3.bmp");
	ShirtsL3->Cut({ 64, 128 });

	GameEngineImage* Pants1 = GameEngineImageManager::GetInst()->Find("Pants1.bmp");
	Pants1->Cut({ 64, 128 });
	GameEngineImage* Pants2 = GameEngineImageManager::GetInst()->Find("Pants2.bmp");
	Pants2->Cut({ 64, 128 });
	GameEngineImage* PantsL1 = GameEngineImageManager::GetInst()->Find("PantsL1.bmp");
	PantsL1->Cut({ 64, 128 });
	GameEngineImage* PantsL2 = GameEngineImageManager::GetInst()->Find("PantsL2.bmp");
	PantsL2->Cut({ 64, 128 });


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
	GameEngineImage* LeftTools = GameEngineImageManager::GetInst()->Find("LeftTools.bmp");
	LeftTools->CutCount(21, 12);
	GameEngineImage* WeaPons = GameEngineImageManager::GetInst()->Find("WeaPons.bmp");
	WeaPons->CutCount(8, 9);
	GameEngineImage* hoeDirt = GameEngineImageManager::GetInst()->Find("hoeDirt.bmp");
	hoeDirt->CutCount(12, 4);
	GameEngineImage* hoeDirtDark = GameEngineImageManager::GetInst()->Find("hoeDirtDark.bmp");
	hoeDirtDark->CutCount(12, 4);
	GameEngineImage* Crops = GameEngineImageManager::GetInst()->Find("Crops.bmp");
	Crops->Cut({ 64, 192 });
	GameEngineImage* Objects = GameEngineImageManager::GetInst()->Find("Objects.bmp");
	Objects->CutCount(24, 39);

	GameEngineImage* RightHoe = GameEngineImageManager::GetInst()->Find("RightHoe.bmp");
	RightHoe->CutCount(1, 5);
	GameEngineImage* LeftHoe = GameEngineImageManager::GetInst()->Find("LeftHoe.bmp");
	LeftHoe->CutCount(1, 5);
	GameEngineImage* FrontHoe = GameEngineImageManager::GetInst()->Find("FrontHoe.bmp");
	FrontHoe->CutCount(1, 5);

	GameEngineImage* RightAx = GameEngineImageManager::GetInst()->Find("RightAx.bmp");
	RightAx->CutCount(1, 5);
	GameEngineImage* LeftAx = GameEngineImageManager::GetInst()->Find("LeftAx.bmp");
	LeftAx->CutCount(1, 5);
	GameEngineImage* FrontAx = GameEngineImageManager::GetInst()->Find("FrontAx.bmp");
	FrontAx->CutCount(1, 5);

	GameEngineImage* RightPick = GameEngineImageManager::GetInst()->Find("RightPick.bmp");
	RightPick->CutCount(1, 5);
	GameEngineImage* LeftPick = GameEngineImageManager::GetInst()->Find("LeftPick.bmp");
	LeftPick->CutCount(1, 5);
	GameEngineImage* FrontPick = GameEngineImageManager::GetInst()->Find("FrontPick.bmp");
	FrontPick->CutCount(1, 5);

	GameEngineImage* RightSickle = GameEngineImageManager::GetInst()->Find("RightSickle.bmp");
	RightSickle->CutCount(1, 6);
	GameEngineImage* LeftSickle = GameEngineImageManager::GetInst()->Find("LeftSickle.bmp");
	LeftSickle->CutCount(1, 6);
	GameEngineImage* FrontSickle = GameEngineImageManager::GetInst()->Find("FrontSickle.bmp");
	FrontSickle->CutCount(1, 6);
	GameEngineImage* BackSickle = GameEngineImageManager::GetInst()->Find("BackSickle.bmp");
	BackSickle->CutCount(1, 6);

	GameEngineImage* RightSword = GameEngineImageManager::GetInst()->Find("RightSword.bmp");
	RightSword->CutCount(1, 6);
	GameEngineImage* LeftSword = GameEngineImageManager::GetInst()->Find("LeftSword.bmp");
	LeftSword->CutCount(1, 6);
	GameEngineImage* FrontSword = GameEngineImageManager::GetInst()->Find("FrontSword.bmp");
	FrontSword->CutCount(1, 6);
	GameEngineImage* BackSword = GameEngineImageManager::GetInst()->Find("BackSword.bmp");
	BackSword->CutCount(1, 6);

	GameEngineImage* FrontWateringCan = GameEngineImageManager::GetInst()->Find("FrontWateringCan.bmp");
	FrontWateringCan->CutCount(1, 1);
	GameEngineImage* LeftWateringCan = GameEngineImageManager::GetInst()->Find("LeftWateringCan.bmp");
	LeftWateringCan->CutCount(1, 1);
	GameEngineImage* RightWateringCan = GameEngineImageManager::GetInst()->Find("RightWateringCan.bmp");
	RightWateringCan->CutCount(1, 1);

	GameEngineImage* Font = GameEngineImageManager::GetInst()->Find("Font.bmp");
	Font->CutCount(16, 29);
	GameEngineImage* Date = GameEngineImageManager::GetInst()->Find("Date.bmp");
	Date->CutCount(1, 14);
	GameEngineImage* Time = GameEngineImageManager::GetInst()->Find("Time.bmp");
	Time->CutCount(2, 13);
	GameEngineImage* ItemNum = GameEngineImageManager::GetInst()->Find("ItemCountNum.bmp");
	ItemNum->CutCount(11, 1);


	GameEngineImage* TreeTop = GameEngineImageManager::GetInst()->Find("TreeTop.bmp");
	TreeTop->CutCount(2, 1);
	GameEngineImage* TreeBot = GameEngineImageManager::GetInst()->Find("TreeBot.bmp");
	TreeBot->CutCount(2, 1);
	GameEngineImage* CutTree = GameEngineImageManager::GetInst()->Find("CutTree.bmp");
	CutTree->CutCount(2, 1); 
	GameEngineImage* FarmObject = GameEngineImageManager::GetInst()->Find("FarmObject.bmp");
	FarmObject->CutCount(8, 1);

	GameEngineImage* Money = GameEngineImageManager::GetInst()->Find("Money.bmp");
	Money->CutCount(10, 1); //32,64
	GameEngineImage* TreeAni = GameEngineImageManager::GetInst()->Find("TreeAni.bmp");
	TreeAni->CutCount(6, 1); 
	
	GameEngineImage* WateringAni = GameEngineImageManager::GetInst()->Find("WateringCanTileAni.bmp");
	WateringAni->CutCount(10, 1);
	GameEngineImage* GrassAni = GameEngineImageManager::GetInst()->Find("GrassAni.bmp");
	GrassAni->CutCount(10, 1);
	GameEngineImage* GroundAni = GameEngineImageManager::GetInst()->Find("GroundAni.bmp");
	GroundAni->CutCount(10, 1);
	GameEngineImage* StoneAni = GameEngineImageManager::GetInst()->Find("StoneAni.bmp");
	StoneAni->CutCount(10, 1);

	GameEngineImage* MineObject = GameEngineImageManager::GetInst()->Find("MineObject.bmp");
	MineObject->CutCount(8, 2);
	GameEngineImage* Bug = GameEngineImageManager::GetInst()->Find("Bug.bmp");
	Bug->CutCount(4, 5);
	GameEngineImage* Slime = GameEngineImageManager::GetInst()->Find("Slime.bmp");
	Slime->CutCount(4, 11);
	GameEngineImage* Cow = GameEngineImageManager::GetInst()->Find("Cow.bmp");
	Cow->CutCount(4, 5);
	GameEngineImage* Chicken = GameEngineImageManager::GetInst()->Find("Chicken.bmp");
	Chicken->CutCount(4, 7);
	GameEngineImage* BabyChicken = GameEngineImageManager::GetInst()->Find("BabyChicken.bmp");
	BabyChicken->CutCount(4, 14);
	GameEngineImage* BabyCow = GameEngineImageManager::GetInst()->Find("BabyCow.bmp");
	BabyCow->CutCount(4, 5);
	GameEngineImage* BabyCowL = GameEngineImageManager::GetInst()->Find("BabyCowL.bmp");
	BabyCowL->CutCount(4, 5);
	GameEngineImage* CowL = GameEngineImageManager::GetInst()->Find("CowL.bmp");
	CowL->CutCount(4, 5);
	GameEngineImage* TitleStart2 = GameEngineImageManager::GetInst()->Find("TitleStart2.bmp");
	TitleStart2->CutCount(2, 1);
	GameEngineImage* TitleStartFish = GameEngineImageManager::GetInst()->Find("TitleStartFish.bmp");
	TitleStartFish->CutCount(2, 1);
	GameEngineImage* TitleStart1 = GameEngineImageManager::GetInst()->Find("TitleStart1.bmp");
	TitleStart1->CutCount(3, 2);

	if (false == GameEngineInput::GetInst()->IsKey("Skip"))
	{
		GameEngineInput::GetInst()->CreateKey("Skip", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("CheckTest", 'P');
	}

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<FarmHouseLevel>("FarmHouseLevel");
	CreateLevel<FarmLevel>("FarmLevel");
	CreateLevel<CoopLevel>("CoopLevel"); 
	CreateLevel<AnimalShopLevel>("AnimalShopLevel");
	CreateLevel<ForestLevel>("ForestLevel");
	CreateLevel<TownLevel>("TownLevel");
	CreateLevel<Town2Level>("Town2Level");
	CreateLevel<RobinShopLevel>("RobinShopLevel");
	CreateLevel<BusStopLevel>("BusStopLevel");
	CreateLevel<SeedShopLevel>("SeedShopLevel");
	CreateLevel<MineEntryLevel>("MineEntryLevel");
	CreateLevel<Mine1Level>("Mine1Level");
	CreateLevel<Mine2Level>("Mine2Level");
	CreateLevel<BarnLevel>("BarnLevel");
	CreateLevel< BackWoodLevel>("BackWoodLevel");
	//ChangeLevel("FarmHouseLevel");
	ChangeLevel("TitleLevel");
	//ChangeLevel("FarmLevel");
}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}