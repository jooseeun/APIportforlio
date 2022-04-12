#include "ForestLevel.h"
#include "Player.h"
#include "ToolUI.h"
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

ForestLevel::ForestLevel() 
{
}

ForestLevel::~ForestLevel() 
{
}

void ForestLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Forest.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });
	Back->TileMap_.TileRangeSetting(90, 34, { 48,48 });
	CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	Player* PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 4324.0f,1664.f });
	PlayerSet->SetMapScale(4536.0f, 3084.0f);
	PlayerSet->SetColMapName("ForestColMap.bmp");
	PlayerSet->SetSideLevel("TownLevel", "FarmLevel", "AnimalShopLevel");
}

void ForestLevel::Update()
{

}