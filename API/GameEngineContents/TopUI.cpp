#include "TopUI.h"
#include <GameEngine/GameEngineRenderer.h>

TopUI* TopUI::TopUISet = nullptr;
TopUI::TopUI() :
	Date_(1)
{
}

TopUI::~TopUI() 
{
}


void TopUI::Start()
{
	SetPosition({ 1124,131.5 });

	GameEngineRenderer* Renderer = CreateRenderer("TopUI.bmp");
	Renderer->CameraEffectOff();
	DateRender_ = CreateRendererToScale("Date.bmp",{160,40},1000,RenderPivot::BOT,{43,-60});
	DateRender_->SetIndex(Date_-1);
	DateRender_->CameraEffectOff();
	AMPMRender_= CreateRendererToScale("Time.bmp", { 80,40 }, 1000, RenderPivot::BOT, { 80,32 });
	AMPMRender_->SetIndex(0);
	AMPMRender_->CameraEffectOff();
	HourRender_=CreateRendererToScale("Time.bmp", { 80,40 }, 1000, RenderPivot::BOT, { 10,32 });
	HourRender_->SetIndex(10);
	HourRender_->CameraEffectOff();
	MinuteRender_= CreateRendererToScale("Time.bmp", { 80,40 }, 1000, RenderPivot::BOT, { 10,33 });
	MinuteRender_->SetIndex(15);
	MinuteRender_->CameraEffectOff();

}


void TopUI::Update()
{
	DateRender_->SetIndex(Date_ - 1);
}

void TopUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	TopUISet = this;
}