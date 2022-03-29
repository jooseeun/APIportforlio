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
	CreateRenderer("ToolUI.bmp");

}

void ToolUI::Render()
{
}