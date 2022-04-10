#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "PlayerCreate.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>



TitleLevel::TitleLevel()
	:count(0)
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
	if (true == GameEngineInput::GetInst()->IsDown("GoPlay"))
	{
		if (count == 1)
		{
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
		}
		count++;
	}
	
}

void TitleLevel::LevelChangeStart()
{
	BgmPlayer = GameEngineSound::SoundPlayControl("Stardew Valley Overture.MP3");
}