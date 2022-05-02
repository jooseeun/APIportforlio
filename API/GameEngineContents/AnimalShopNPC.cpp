#include "AnimalShopNPC.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
AnimalShopNPC::AnimalShopNPC() 
{
}

AnimalShopNPC::~AnimalShopNPC() 
{
}

void AnimalShopNPC::Start()
{
	SetPosition({ 858,890});
	GameEngineRenderer* Renderer = CreateRenderer("AnimalShopOnner.bmp");
	GameEngineCollision* Col_ = CreateCollision("AnimalShopOnner", { 64,128 });
}
void AnimalShopNPC::Update()
{
}