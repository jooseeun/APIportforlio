#include "TitleLevel.h"
#include "TitleLogo.h"
#include "PlayerCreate.h"
#include "Mouse.h"
#include "ContentsEnums.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>



TitleLevel::TitleLevel()
	:count(0),
	IsBGM_(false),
	IsCreate_(false)
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	TitleBackGround::TitleBackGroundSet=CreateActor<TitleBackGround>(0,"TitleBackground");

	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

}

void TitleLevel::Update()
{
	if (TitleBackGround::TitleBackGroundSet->IsBGM() == true&& IsBGM_==false)
	{
		BgmPlayer = GameEngineSound::SoundPlayControl("Stardew Valley Overture.mp3");
		BgmPlayer.Volume(0.4f);
		IsBGM_ = true;
	}

	if (TitleBackGround::TitleBackGroundSet->IsLogo() == true&& IsCreate_==false)
	{

		Logo = CreateActor<TitleLogo>(1, "TitleLogo");
		IsCreate_=true;
		
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	IsCreate_ = false;
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	
	Logo->Death();
	Logo = nullptr;
	BgmPlayer.Stop();
}
