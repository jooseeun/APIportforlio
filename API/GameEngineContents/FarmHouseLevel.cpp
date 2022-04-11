#include "FarmHouseLevel.h"
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

FarmHouseLevel::FarmHouseLevel() 
{
}

FarmHouseLevel::~FarmHouseLevel() 
{
}

void FarmHouseLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("FarmHouse.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });


	
	CreateActor<TopUI>(static_cast<int>(ORDER::UI), "TopUI");
	CreateActor<EnergyUI>(static_cast<int>(ORDER::UI), "EnergyUI");
	CreateActor<ToolUI>(static_cast<int> (ORDER::UI), "ToolUI");

	
	Player* PlayerSet = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
	PlayerSet->SetPosition({ 750.0f,520.f });
	PlayerSet->SetMapScale(1280.0f, 840.0f);
	PlayerSet->SetColMapName("FarmHouseColMap.bmp");
	PlayerSet->SetSideLevel("BusStopLevel", "FarmLevel", " ");

}

void FarmHouseLevel::Update()
{

}

void FarmHouseLevel::LevelChangeStart()
{
}

