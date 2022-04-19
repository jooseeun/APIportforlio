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
#include "WateringCan.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

FarmHouseLevel::FarmHouseLevel() :
	CurSelectPivot_(1),
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
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });
	Back->GroundTileMap_.TileRangeSetting(26, 15, { 48,48 });
	Back->CropsTileMap_.TileRangeSetting(26, 15, { 48,48 });
	

	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
	AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
	PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
	SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
	WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");
	PhotatoSeedSet = CreateActor<PhotatoSeed>((int)ORDER::ITEM, "PhotatoSeed");


	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
	}

	Player::MainPlayer->SetPosition({ 750.0f,520.f });
	Player::MainPlayer->SetMapScale(1280.0f, 840.0f);
	Player::MainPlayer->SetColMapName("FarmHouseColMap.bmp");
	Player::MainPlayer->SetSideLevel("BusStopLevel", "FarmLevel", " ");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
}

void FarmHouseLevel::Update()
{
	GetItemPos<Ax>(AxSet);
	GetItemPos<Pick>(PickSet);
	GetItemPos<Hoe>(HoeSet);
	GetItemPos<Sickle>(SickleSet);
	GetItemPos<WateringCan>(WateringCanSet);
	GetItemPos<PhotatoSeed>(PhotatoSeedSet);

	NextSelectPivot_ = ToolUISet->getSelectPivot();
	if (CurSelectPivot_ != NextSelectPivot_)
	{
		Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}
void FarmHouseLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetPosition({ 750.0f,520.f });
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
	}
}
