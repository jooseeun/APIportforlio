#include "TitleLevel.h"
#include "TitleLogo.h"
#include "PlayerCreate.h"
#include "Mouse.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>



TitleLevel::TitleLevel()
	:count(0),
	IsBGM_(false)
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	Back_=CreateActor<TitleBackGround>(0,"TitleBackground");

	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

}

void TitleLevel::Update()
{
	if (Back_->IsBGM() == true&& IsBGM_==false)
	{
		BgmPlayer = GameEngineSound::SoundPlayControl("Stardew Valley Overture.mp3");
		BgmPlayer.Volume(0.6f);
		IsBGM_ = true;
	}

	if (Back_->IsLogo() == true)
	{
		CreateActor<TitleLogo>(1, "TitleLogo");
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BgmPlayer.Stop();
}
