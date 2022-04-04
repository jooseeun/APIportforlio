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
	{
		BackGround* Back = CreateActor<BackGround>(1);
		Back->GetRenderer()->SetImage("FarmHouse.bmp");
		Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x/2, Back->GetRenderer()->GetImage()->GetScale().y/2 });

	}

	CreateActor<ToolUI>( (int)ORDER::UI, "ToolUI" );
	CreateActor<TopUI>( (int)ORDER::UI,"TopUI");
	CreateActor<EnergyUI>( (int)ORDER::UI, "EnergyUI");

	
	Player* PlayerPos = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerPos->SetPosition({ 750.0f,520.f });
	PlayerPos->SetMapScale(1280.0f, 5000.0f);
	

}

void FarmHouseLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");

	}

	
	
}

void FarmHouseLevel::LevelChangeStart()
{
}