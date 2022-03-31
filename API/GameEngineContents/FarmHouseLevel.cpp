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
		BackGround* Back = CreateActor<BackGround>(0);
		Back->GetRenderer()->SetImage("FarmHouse.bmp");

		float4 BackActor = {};
		BackActor.x = (Back->GetRenderer()->GetImage()->GetScale().Half().x) - (GameEngineWindow::GetScale().Half().x);
		BackActor.y = (Back->GetRenderer()->GetImage()->GetScale().Half().y) - (GameEngineWindow::GetScale().Half().y);

		Back->GetRenderer()->SetPivot(BackActor);
	}
	CreateActor<Player>( (int)ORDER::PLAYER,"Player");
	CreateActor<ToolUI>( (int)ORDER::UI, "ToolUI" );
	CreateActor<TopUI>( (int)ORDER::UI,"TopUI");
	CreateActor<EnergyUI>( (int)ORDER::UI, "EnergyUI");

}

void FarmHouseLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleLevel"))
	{
		GameEngine::GlobalEngine().ChangeLevel("TitleLevel");

	}
}

void FarmHouseLevel::LevelChangeStart()
{
}