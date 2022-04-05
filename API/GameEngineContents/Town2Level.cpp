#include "Town2Level.h"
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

Town2Level::Town2Level() 
{
}

Town2Level::~Town2Level() 
{
}

void Town2Level::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Town2.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });

	CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	Player* PlayerPos = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerPos->SetPosition({ 1020.0f,2500.f });
	PlayerPos->SetMapScale(5448.0f, 2620.0f);
}

void Town2Level::Update()
{

}