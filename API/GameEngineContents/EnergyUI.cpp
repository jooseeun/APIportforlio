#include "EnergyUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

EnergyUI::EnergyUI() 
{
}

EnergyUI::~EnergyUI() 
{
}

void EnergyUI::Start()
{
	SetPosition({1247,593});
	GameEngineRenderer* Renderer = CreateRenderer("EnergyUI.bmp");
	Renderer->CameraEffectOff();
}

void EnergyUI::Render()
{
	//DebugRectRender();
}