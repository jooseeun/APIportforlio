#include "NPCShopOnner.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
NPCShopOnner::NPCShopOnner() 
{
}

NPCShopOnner::~NPCShopOnner() 
{
}

void NPCShopOnner::Start()
{
	SetPosition({ 256.0f,1090.f });
	GameEngineRenderer* Renderer = CreateRenderer("ShopOnner.bmp");
	GameEngineCollision* Col_ = CreateCollision("ShopNPC", { 64,128 });
}
void NPCShopOnner::Update()
{

}