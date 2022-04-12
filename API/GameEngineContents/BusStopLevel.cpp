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
BusStopLevel::BusStopLevel() 
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
		Back->TileMap_.TileRangeSetting(35, 30, { 48,48 });
	}

	CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");


	Player* PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 50.0f,1516.f });
	PlayerSet->SetMapScale(2240.0f, 1920.0f);
	PlayerSet->SetColMapName("BusStopColMap.bmp");
	PlayerSet->SetSideLevel("FarmLevel", "TownLevel"," ");

}

void BusStopLevel::Update()
{
}

