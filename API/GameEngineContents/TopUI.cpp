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
}


void TopUI::Update()
{
	DateRender_->SetIndex(Date_ - 1);
}

void TopUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	TopUISet = this;
}