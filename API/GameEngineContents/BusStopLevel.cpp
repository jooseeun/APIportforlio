#include "BusStopLevel.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
BusStopLevel::BusStopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

BusStopLevel::~BusStopLevel() 
{
}

void BusStopLevel::Loading()
{
	{
		BackGround* Back = CreateActor<BackGround>(1);
		Back->GetRenderer()->SetImage("BusStop.bmp");
		Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });
		Back->GroundTileMap_.TileRangeSetting(35, 30, { 48,48 });
		Back->CropsTileMap_.TileRangeSetting(35, 30, { 48,48 });
	}

	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
	AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
	PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
	SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
	WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");


	Player* PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 50.0f,1516.f });
	PlayerSet->SetMapScale(2240.0f, 1920.0f);
	PlayerSet->SetColMapName("BusStopColMap.bmp");
	PlayerSet->SetSideLevel("FarmLevel", "TownLevel"," ");

}

void BusStopLevel::Update()
{
	GetItemPos<Ax>(AxSet);
	GetItemPos<Pick>(PickSet);
	GetItemPos<Hoe>(HoeSet);
	GetItemPos<Sickle>(SickleSet);
	GetItemPos<WateringCan>(WateringCanSet);

	NextSelectPivot_ = ToolUISet->getSelectPivot();
	if (CurSelectPivot_ != NextSelectPivot_)
	{
		PlayerSet->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}

