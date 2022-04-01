#include "ToolUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

ToolUI::ToolUI() 
{
}

ToolUI::~ToolUI() 
{
}

void ToolUI::Start()
{
	SetPosition({ 640,664 });
	GameEngineRenderer* Renderer = CreateRenderer("ToolUI.bmp");
	Renderer->CameraEffectOff();
}

void ToolUI::Render()
{
}