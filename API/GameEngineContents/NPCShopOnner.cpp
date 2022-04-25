#include "NPCShopOnner.h"
#include <GameEngine/GameEngineRenderer.h>

NPCShopOnner::NPCShopOnner() 
{
}

NPCShopOnner::~NPCShopOnner() 
{
}

void NPCShopOnner::Start()
{
	GameEngineRenderer* Renderer = CreateRenderer("ShopOnner.bmp");
	Renderer->CameraEffectOff();
}
void NPCShopOnner::Update()
{

}