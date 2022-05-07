#include "PlayHelpBar.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


PlayHelpBar::PlayHelpBar()
	:PosX_(0),
	PosY_(360),
	Up_(false)
{
}

PlayHelpBar::~PlayHelpBar() 
{
}

void PlayHelpBar::Start()
{
	SetPosition({ -67,360 });
	Render_ = CreateRenderer("HelpBar.bmp", static_cast<int>(ORDER::FRONTUI));
	Render_->CameraEffectOff();
}
void PlayHelpBar::Update()
{
	if (PosX_ >= 0 && Up_==false)
	{
		if (PosX_ >= 134)
		{
			Up_ = true;
			return;
		}

		PosX_ += 1 * GameEngineTime::GetDeltaTime() * 50.0f;
		Render_->SetPivot({ PosX_, 0 });
		return;
	}
	static float Time_ = 4.0f;
	if (Time_ > 0)
	{
		Time_ -= 1 * GameEngineTime::GetDeltaTime();
		return;
	}
	if (PosX_ >= 0 && Up_ == true)
	{

		PosX_ -= 1 * GameEngineTime::GetDeltaTime() * 50.0f;
		Render_->SetPivot({ PosX_, 0 });
		return;
	}
}