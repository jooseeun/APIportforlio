#include "EnergyUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

EnergyUI::EnergyUI() 
{
}

EnergyUI::~EnergyUI() 
{
}

void EnergyUI::Start()
{
	SetPosition({1248,592});
	SetScale({ 48, 224 });

	CreateRendererToScale("EnergyUI.bmp", float4(48.0f, 224.0f));

}

void EnergyUI::Render()
{
	//DebugRectRender();
}