#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>


TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0,"TitleBackground");
	CreateActor<TitleLogo>(1,"TitleLogo");
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("FarmHouseLevel"))
	{
		GameEngine::GlobalEngine().ChangeLevel("FarmHouseLevel");
	}
}

void TitleLevel::LevelChangeStart()
{
}