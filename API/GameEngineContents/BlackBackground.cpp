#include "BlackBackground.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
BlackBackground::BlackBackground() 
{
}

BlackBackground::~BlackBackground() 
{
}

void BlackBackground::Start()
{
	//
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
	GameEngineRenderer* Renderer = CreateRenderer("BlackBackground.bmp");
	Renderer->CameraEffectOff();
}

void BlackBackground::Render()
{
	// DebugRectRender();
}
