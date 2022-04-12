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
	// ���� ���丮
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");
	ResourcesDir.Move("Player");

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}
	}
	{

		// ���� ���丮
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Title");

		// �����ȿ� ��� �̹��� ������ ã�´�.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		// ���� ���丮
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("UI");

		// �����ȿ� ��� �̹��� ������ ã�´�.
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

		// �����ȿ� ��� �̹��� ������ ã�´�.
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}
	{
		// ���� ���丮
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("API");
		ResourcesDir.Move("Resources");
		ResourcesDir.Move("Image");
		ResourcesDir.Move("Map");

		// �����ȿ� ��� �̹��� ������ ã�´�.
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

		// �����ȿ� ��� �̹��� ������ ã�´�.
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


	if (false == GameEngineInput::GetInst()->IsKey("GoPlay"))
	{
		GameEngineInput::GetInst()->CreateKey("GoPlay", VK_SPACE);
	}

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
	ChangeLevel("TitleLevel");
	//ChangeLevel("FarmLevel");
}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}