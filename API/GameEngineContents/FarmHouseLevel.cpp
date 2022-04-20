#include "FarmHouseLevel.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Ax.h"
#include "Hoe.h"
#include "Pick.h"
#include "Sickle.h"
#include "Player.h"
#include "ToolUI.h"
#include "PhotatoSeed.h"
#include "ContentsEnums.h"
#include "WateringCan.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

FarmHouseLevel::FarmHouseLevel() :
	CurSelectPivot_(0),
	NextSelectPivot_(1)
{
}

FarmHouseLevel::~FarmHouseLevel() 
{
}

void FarmHouseLevel::Loading()
{
	Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("FarmHouse.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());

	Back->GroundTileMap_.TileRangeSetting(26, 15, { 48,48 });
	Back->CropsTileMap_.TileRangeSetting(26, 15, { 48,48 });
	
	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
		ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
		TopUI::TopUISet = CreateActor<TopUI>((int)ORDER::UI, "TopUI");
		EnergyUI::EnergyUISet = CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
		Hoe::HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
		Ax::AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
		Pick::PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
		Sickle::SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
		WateringCan::WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");
		PhotatoSeed::PhotatoSeedSet = CreateActor<PhotatoSeed>((int)ORDER::ITEM, "PhotatoSeed");
		
	}


}

void FarmHouseLevel::Update()
{

	GetItemPos<Ax>(Ax::AxSet);
	GetItemPos<Pick>(Pick::PickSet);
	GetItemPos<Hoe>(Hoe::HoeSet);
	GetItemPos<Sickle>(Sickle::SickleSet);
	GetItemPos<WateringCan>(WateringCan::WateringCanSet);
	GetItemPos<PhotatoSeed>(PhotatoSeed::PhotatoSeedSet);

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();

	if (CurSelectPivot_ != NextSelectPivot_)
	{
		Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}

void FarmHouseLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetPosition({ 474.0f,648.f });
	//Player::MainPlayer->SetPosition({ 750.0f,520.f });
	Player::MainPlayer->SetMapScale(1280.0f, 840.0f);
	Player::MainPlayer->SetColMapName("FarmHouseColMap.bmp");
	Player::MainPlayer->SetSideLevel("BusStopLevel", "FarmLevel", " ");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
}

void FarmHouseLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();
		Hoe::HoeSet->NextLevelOn();
		Ax::AxSet->NextLevelOn();
		Pick::PickSet->NextLevelOn();
		Sickle::SickleSet->NextLevelOn();
		WateringCan::WateringCanSet->NextLevelOn();
		PhotatoSeed::PhotatoSeedSet->NextLevelOn();
	}
}
