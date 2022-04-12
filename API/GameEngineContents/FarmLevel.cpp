#include "FarmLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include "Ax.h"
#include "Hoe.h"
#include "Pick.h"
#include "Sickle.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRendererTileMap.h>
FarmLevel::FarmLevel() 
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
	Back->TileMap_.TileRangeSetting(80, 65, { 64,64 });


	CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	CreateActor<Ax>((int)ORDER::ITEM, "Ax");
	CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
	CreateActor<Pick>((int)ORDER::ITEM, "Pick");
	CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");

	Player* PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 4120.0f,1020.f });
	PlayerSet->SetMapScale(5120.0f,4160.0f);
	PlayerSet->SetColMapName("FarmColMap.bmp");
	PlayerSet->SetTileMap(&Back->TileMap_);

	PlayerSet->SetSideLevel("FarmHouseLevel","BusStopLevel"," ");
}

void FarmLevel::Update()
{

}