#include "FarmLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include "BlackBackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

FarmLevel::FarmLevel() 
{
}

FarmLevel::~FarmLevel() 
{

}

void FarmLevel::Loading()
{
	CreateActor<BlackBackground>((int)ORDER::BACKGROUND, "Black");
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Farm.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });

	CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	Player* PlayerPos = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerPos->SetPosition({ 4120.0f,1020.f });
	PlayerPos->MapSizeX = 5120.0f;
	PlayerPos->MapSizeY = 4160.0f;
}

void FarmLevel::Update()
{

}