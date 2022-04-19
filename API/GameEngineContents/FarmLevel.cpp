#include "FarmLevel.h"
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
#include "WateringCan.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRendererTileMap.h>
FarmLevel::FarmLevel():
	CurSelectPivot_(0),
	NextSelectPivot_(1)
{

}

FarmLevel::~FarmLevel() 
{

}

void FarmLevel::Loading()
{
	Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Farm.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());
	Back->GroundTileMap_.TileRangeSetting(80, 65, { 64,64 });
	Back->CropsTileMap_.TileRangeSetting(80, 65, { 64,64 });

	Mouse* Cursor = CreateActor<Mouse>(200 );

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
		ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
		TopUI::TopUISet=CreateActor<TopUI>((int)ORDER::UI, "TopUI");
		EnergyUI::EnergyUISet=CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
		Hoe::HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
		Ax::AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
		Pick::PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
		Sickle::SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
		WateringCan::WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");
		PhotatoSeed::PhotatoSeedSet = CreateActor<PhotatoSeed>((int)ORDER::ITEM, "PhotatoSeed");
	}

	Player::MainPlayer->SetPosition({ 4120.0f,1020.f });
	Player::MainPlayer->SetMapScale(5120.0f, 4160.0f);
	Player::MainPlayer->SetColMapName("FarmColMap.bmp");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
	Player::MainPlayer->SetSideLevel("FarmHouseLevel", "BusStopLevel", " ");
}

void FarmLevel::Update()
{
	GetItemPos<Ax>(Ax::AxSet);
	GetItemPos<Pick>(Pick::PickSet);
	GetItemPos<Hoe>(Hoe::HoeSet);
	GetItemPos<Sickle>(Sickle::SickleSet);
	GetItemPos<WateringCan>(WateringCan::WateringCanSet);
	GetItemPos<PhotatoSeed>(PhotatoSeed::PhotatoSeedSet);

	NextSelectPivot_= ToolUI::ToolUISet->getSelectPivot();
	
	if (CurSelectPivot_ != NextSelectPivot_)
	{
		Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}

void FarmLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetPosition({ 4120.0f,1020.f });
	Player::MainPlayer->SetMapScale(5120.0f, 4160.0f);
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
	Player::MainPlayer->SetColMapName("FarmColMap.bmp");
	Player::MainPlayer->SetSideLevel("FarmHouseLevel", "BusStopLevel", " ");
}

void FarmLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
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
