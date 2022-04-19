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

	Player::MainPlayer->SetPosition({ 4120.0f,1020.f });
	Player::MainPlayer->SetMapScale(5120.0f, 4160.0f);
	Player::MainPlayer->SetColMapName("FarmColMap.bmp");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
	Player::MainPlayer->SetSideLevel("FarmHouseLevel", "BusStopLevel", " ");
}

void FarmLevel::Update()
{
	GetItemPos<Ax>(AxSet);
	GetItemPos<Pick>(PickSet);
	GetItemPos<Hoe>(HoeSet);
	GetItemPos<Sickle>(SickleSet);
	GetItemPos<WateringCan>(WateringCanSet);
	GetItemPos<PhotatoSeed>(PhotatoSeedSet);

	NextSelectPivot_=ToolUISet->getSelectPivot();
	
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
	}
}
