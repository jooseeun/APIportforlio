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
	SetPosition({1247,593});
	CreateRenderer("EnergyUI.bmp");

}

void EnergyUI::Render()
{
	//DebugRectRender();
}