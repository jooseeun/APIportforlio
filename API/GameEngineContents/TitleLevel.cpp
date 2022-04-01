#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "PlayerCreate.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>


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
	CreateActor<TitleLogo>(1, "TitleLogo");
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("FarmHouseLevel"))
	{
		GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
	}
	if (true == GameEngineInput::GetInst()->IsDown("FarmLevel"))
	{
		GameEngine::GetInst().ChangeLevel("FarmLevel");
	}
}

void TitleLevel::LevelChangeStart()
{
}