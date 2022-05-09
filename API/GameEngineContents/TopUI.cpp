#include "TopUI.h"
#include "Time.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

TopUI* TopUI::TopUISet = nullptr;
TopUI::TopUI() :
	Date_(1)
{
	Alpha_ = 0;
}

TopUI::~TopUI() 
{
}


void TopUI::Start()
{
	SetPosition({ 1124,131.5 });

	GameEngineRenderer* Renderer = CreateRenderer("TopUI.bmp");
	Renderer->CameraEffectOff();
	DateRender_ = CreateRendererToScale("Date.bmp",{160,40},static_cast<int>(ORDER::UIFONT),RenderPivot::BOT,{43,-60});
	DateRender_->SetIndex(Date_-1);
	DateRender_->CameraEffectOff();
	AMPMRender_= CreateRendererToScale("Time.bmp", { 80,40 }, static_cast<int>(ORDER::UIFONT), RenderPivot::BOT, { 80,32 });
	AMPMRender_->SetIndex(0);
	AMPMRender_->CameraEffectOff();
	HourRender_=CreateRendererToScale("Time.bmp", { 80,40 }, static_cast<int>(ORDER::UIFONT), RenderPivot::BOT, { 10,32 });
	HourRender_->SetIndex(10);
	HourRender_->CameraEffectOff();
	MinuteRender_= CreateRendererToScale("Time.bmp", { 80,40 }, static_cast<int>(ORDER::UIFONT), RenderPivot::BOT, { 10,33 });
	MinuteRender_->SetIndex(15);
	MinuteRender_->CameraEffectOff();

	NightAlpha_ = CreateRendererToScale("NightAlpha.bmp", { 1280,720 }, static_cast<int>(ORDER::NIGHTALPHA), RenderPivot::CENTER, { -484,588.5-360 });
	NightAlpha_->CameraEffectOff();
	NightAlpha_->SetAlpha(Alpha_);
}


void TopUI::Update()
{
	MinuteUpdate();
	HourUpdate();
	AMPMUpdate();
	DateRender_->SetIndex(Time::TimeSet->GetGameDay_() - 1);
	AlphaUpdate();
}
void TopUI::MinuteUpdate() 
{
	if (0 == Time::TimeSet->GetGameMinute_())
	{
		MinuteRender_->SetIndex(21);
	}
	else if (10 == Time::TimeSet->GetGameMinute_())
	{
		MinuteRender_->SetIndex(15);
	}
	else if (20 == Time::TimeSet->GetGameMinute_())
	{
		MinuteRender_->SetIndex(16);
	}
	else if (30 == Time::TimeSet->GetGameMinute_())
	{
		MinuteRender_->SetIndex(17);
	}
	else if (40 == Time::TimeSet->GetGameMinute_())
	{
		MinuteRender_->SetIndex(18);
	}
	else if (50 == Time::TimeSet->GetGameMinute_())
	{
		MinuteRender_->SetIndex(19);
	}

}
void TopUI::AlphaUpdate()
{
	if (Time::TimeSet->GetGameHour_() > 18 && Time::TimeSet->GetGameHour_() < 21)
	{
		if (Alpha_ < 130)
		{
			Alpha_ += 10 ;
		}

	}
	else if (Time::TimeSet->GetGameHour_() > 21 && Time::TimeSet->GetGameHour_() < 24)
	{
		if (Alpha_ < 180)
		{
			Alpha_ += 10;
		}
	}
	else if (Time::TimeSet->GetGameHour_() > 4 && Time::TimeSet->GetGameHour_() < 5)
	{
		if (Alpha_ > 100)
		{
			Alpha_ -= 1;
		}
	}
	
	else if (Time::TimeSet->GetGameHour_() > 5 && Time::TimeSet->GetGameHour_() < 8)
	{
		if (Alpha_ > 0)
		{
			Alpha_ -= 1*GameEngineTime::GetDeltaTime()*20.0f;
		}
	}
	else if (Time::TimeSet->GetGameHour_() > 8 && Time::TimeSet->GetGameHour_() < 18)
	{
		Alpha_ = 0;
	}
		NightAlpha_->SetAlpha(Alpha_);
}
void TopUI::HourUpdate()
{
	if (-1 < Time::TimeSet->GetGameHour_() && Time::TimeSet->GetGameHour_() < 13)
	{
		HourRender_->SetIndex(Time::TimeSet->GetGameHour_() + 2);

		
	}
	else
	{
		HourRender_->SetIndex(Time::TimeSet->GetGameHour_() -10);
		
	}
	
}
void TopUI::AMPMUpdate()
{
	if (-1 < Time::TimeSet->GetGameHour_() && Time::TimeSet->GetGameHour_() < 12)
	{
		AMPMRender_->SetIndex(0);

	}
	else
	{
		AMPMRender_->SetIndex(1);
	}

}
void TopUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	TopUISet = this;
}