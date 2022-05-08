#include "NoMoney.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

NoMoney::NoMoney() 
	:Time(2.0f)
{
}

NoMoney::~NoMoney() 
{
}

void NoMoney::Start()
{
	SetPosition({ 167,560 });
	GameEngineRenderer* Renderer_ = CreateRenderer("NoMoney.bmp", static_cast<int>(ORDER::FRONTUI));
	Renderer_->CameraEffectOff();
	Sound_ = GameEngineSound::SoundPlayControl("daggerswipe.wav");
	Sound_.Volume(0.8f);
}

void NoMoney::Update()
{

	if (Time > 0)
	{
		Time -= 1.0f * GameEngineTime::GetDeltaTime();
		return;
	}

	Death();
}