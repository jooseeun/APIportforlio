#include "TitleLevel.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "PlayerCreate.h"
#include "Mouse.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineCollision.h>



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

	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

	IsDebugModeSwitch();

}

void TitleLevel::Update()
{
	

}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
