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
	SetPosition({ 260,664 });

	GameEngineRenderer* ren1 = CreateRendererToScale("Menutile.bmp", {256,256});
	ren1->SetIndex(16);

}

void ToolUI::Render()
{
}