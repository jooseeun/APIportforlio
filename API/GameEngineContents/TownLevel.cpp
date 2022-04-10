#include "TownLevel.h"
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

TownLevel::TownLevel() 
{
}

TownLevel::~TownLevel() 
{
}

void TownLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Town.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });

	CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	Player* PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 144.0f,3492.f });
	PlayerSet->SetMapScale(5544.0f, 6200.0f);
	PlayerSet->SetColMapName("TownColMap.bmp");
	PlayerSet->SetSideLevel("BusStopLevel", "Town2Level","SeedShopLevel");
}

void TownLevel::Update()
{

}