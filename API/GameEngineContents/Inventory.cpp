#include "Inventory.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

Inventory* Inventory::InventorySet = nullptr;

Inventory::Inventory():
	IsInventory_(false)
{
}

Inventory::~Inventory()
{
}

void Inventory::Start()
{
	SetPosition({ 640, 360 });
	GameEngineRenderer* Renderer = CreateRenderer("Inventory.bmp");
	Renderer->CameraEffectOff();
	
	
	if (false == GameEngineInput::GetInst()->IsKey("InvenSwitch"))
	{
		GameEngineInput::GetInst()->CreateKey("InvenSwitch", 'E');
	}

}

void Inventory::Update()
{

	
}
void Inventory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	InventorySet = this;
}