#include "TopUI.h"
#include <GameEngine/GameEngineRenderer.h>

TopUI* TopUI::TopUISet = nullptr;
TopUI::TopUI() 
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
}


void TopUI::Update()
{

}

void TopUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	TopUISet = this;
}