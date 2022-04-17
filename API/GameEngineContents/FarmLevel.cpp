#include "FarmLevel.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"
#include "BackGround.h"

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
void FarmLevel::LevelChangeStart()
{
	//BgmPlayer = GameEngineSound::SoundPlayControl("Spring (The Valley Comes Alive).MP3");

}
void FarmLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Farm.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());
	Back->GroundTileMap_.TileRangeSetting(80, 65, { 64,64 });
	Back->CropsTileMap_.TileRangeSetting(80, 65, { 64,64 });

	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
	AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
	PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
	SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
	WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");
	PhotatoSeedSet = CreateActor<PhotatoSeed>((int)ORDER::ITEM, "PhotatoSeed");

	PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 4120.0f,1020.f });
	PlayerSet->SetMapScale(5120.0f,4160.0f);
	PlayerSet->SetColMapName("FarmColMap.bmp");
	PlayerSet->SetGroundTileMap(&Back->GroundTileMap_);
	PlayerSet->SetCropsTileMap(&Back->CropsTileMap_);
	PlayerSet->SetSideLevel("FarmHouseLevel","BusStopLevel"," ");
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
		PlayerSet->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}


