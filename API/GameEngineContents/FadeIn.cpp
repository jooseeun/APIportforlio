#include "FadeIn.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
FadeIn::FadeIn() 
	:IsFadeIn(false),
	Alpha_(255)
{
}

FadeIn::~FadeIn() 
{
}

void FadeIn::Start()
{
	SetPosition({ 640,360 });
	Renderer_ = CreateRenderer("FadeIn.bmp");
	Renderer_->SetAlpha(Alpha_);
	Renderer_->CameraEffectOff();
	StartfadeIn();
}
void FadeIn::Update()
{
	if (IsFadeIn == true)
	{
		if (Alpha_ <= 0)
		{
			Death();
		}

		Alpha_ -= (80.0f * GameEngineTime::GetDeltaTime());
		Renderer_->SetAlpha(Alpha_);
	}
	

}

