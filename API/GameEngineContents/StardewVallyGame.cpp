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
#include "LobinHouseLevel.h"
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
		GameEngineImage* HairB = GameEngineImageManager::GetInst()->Find("HairBlack.bmp");
		HairB->Cut({ 64, 128 });
		GameEngineImage* HairBL = GameEngineImageManager::GetInst()->Find("HairLBlack.bmp");
		HairBL->Cut({ 64, 128 });
		GameEngineImage* HairBDown = GameEngineImageManager::GetInst()->Find("HairDownBlack.bmp");
		HairBDown->Cut({ 64, 128 });
		GameEngineImage* HairBDownL = GameEngineImageManager::GetInst()->Find("HairDownLBlack.bmp");
		HairBDownL->Cut({ 64, 128 });
	
		GameEngineImage* HairR = GameEngineImageManager::GetInst()->Find("HairRed.bmp");
		HairR->Cut({ 64, 128 });
		GameEngineImage* HairRL = GameEngineImageManager::GetInst()->Find("HairLRed.bmp");
		HairRL->Cut({ 64, 128 });
		GameEngineImage* HairRDown = GameEngineImageManager::GetInst()->Find("HairDownRed.bmp");
		HairRDown->Cut({ 64, 128 });
		GameEngineImage* HairRDownL = GameEngineImageManager::GetInst()->Find("HairDownLRed.bmp");
		HairRDownL->Cut({ 64, 128 });

		GameEngineImage* HairG = GameEngineImageManager::GetInst()->Find("HairGrey.bmp");
		HairG->Cut({ 64, 128 });
		GameEngineImage* HairGL = GameEngineImageManager::GetInst()->Find("HairLGrey.bmp");
		HairGL->Cut({ 64, 128 });
		GameEngineImage* HairGDown = GameEngineImageManager::GetInst()->Find("HairDownGrey.bmp");
		HairGDown->Cut({ 64, 128 });
		GameEngineImage* HairGDownL = GameEngineImageManager::GetInst()->Find("HairDownLGrey.bmp");
		HairGDownL->Cut({ 64, 128 });

		GameEngineImage* HairBB = GameEngineImageManager::GetInst()->Find("HairBlue.bmp");
		HairBB->Cut({ 64, 128 });
		GameEngineImage* HairBBL = GameEngineImageManager::GetInst()->Find("HairLBlue.bmp");
		HairBBL->Cut({ 64, 128 });
		GameEngineImage* HairBBDown = GameEngineImageManager::GetInst()->Find("HairDownBlue.bmp");
		HairBBDown->Cut({ 64, 128 });
		GameEngineImage* HairBBDownL = GameEngineImageManager::GetInst()->Find("HairDownLBlue.bmp");
		HairBBDownL->Cut({ 64, 128 });


		GameEngineImage* Hair1AniB = GameEngineImageManager::GetInst()->Find("HairAniFirstBlack.bmp");
		Hair1AniB->Cut({ 64, 128 });
		GameEngineImage* Hair1AniR = GameEngineImageManager::GetInst()->Find("HairAniFirstRed.bmp");
		Hair1AniR->Cut({ 64, 128 });
		GameEngineImage* Hair1AniG = GameEngineImageManager::GetInst()->Find("HairAniFirstGrey.bmp");
		Hair1AniG->Cut({ 64, 128 });
		GameEngineImage* Hair1AniBB = GameEngineImageManager::GetInst()->Find("HairAniFirstBlue.bmp");
		Hair1AniBB->Cut({ 64, 128 });

		GameEngineImage* Hair1AniLB = GameEngineImageManager::GetInst()->Find("HairAniLFirstBlack.bmp");
		Hair1AniLB->Cut({ 64, 128 });
		GameEngineImage* Hair1AniLR = GameEngineImageManager::GetInst()->Find("HairAniLFirstRed.bmp");
		Hair1AniLR->Cut({ 64, 128 });
		GameEngineImage* Hair1AniLG = GameEngineImageManager::GetInst()->Find("HairAniLFirstGrey.bmp");
		Hair1AniLG->Cut({ 64, 128 });
		GameEngineImage* Hair1AniLBB = GameEngineImageManager::GetInst()->Find("HairAniLFirstBlue.bmp");
		Hair1AniLBB->Cut({ 64, 128 });
	
		
	}

	GameEngineImage* Body = GameEngineImageManager::GetInst()->Find("Body.bmp");
	Body->Cut({ 64, 128 });
	GameEngineImage* Body2 = GameEngineImageManager::GetInst()->Find("Body2.bmp");
	Body2->Cut({ 64, 128 });
	GameEngineImage* Body3 = GameEngineImageManager::GetInst()->Find("Body3.bmp");
	Body3->Cut({ 64, 128 });
	GameEngineImage* Shirts = GameEngineImageManager::GetInst()->Find("BodyShirts.bmp");
	Shirts->Cut({ 64, 128 });
	GameEngineImage* Shirts2 = GameEngineImageManager::GetInst()->Find("Body2Shirts.bmp");
	Shirts2->Cut({ 64, 128 });
	GameEngineImage* Shirts3 = GameEngineImageManager::GetInst()->Find("Body3Shirts.bmp");
	Shirts3->Cut({ 64, 128 });
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
	ItemNum->CutCount(10, 1);
	if (false == GameEngineInput::GetInst()->IsKey("GoPlay"))
	{
		GameEngineInput::GetInst()->CreateKey("GoPlay", VK_SPACE);
	}

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<FarmHouseLevel>("FarmHouseLevel");
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