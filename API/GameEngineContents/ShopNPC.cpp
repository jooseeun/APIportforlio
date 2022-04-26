#include "ShopNPC.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
ShopNPC::ShopNPC() 
{
}

ShopNPC::~ShopNPC() 
{
}

void ShopNPC::Start()
{
	SetPosition({ 640,320 });
	//SetPosition({ 256.0f,1090.f });
	GameEngineRenderer* Renderer = CreateRenderer("ShopOnner.bmp");
	GameEngineCollision* Col_ = CreateCollision("SeedShopNPC", { 64,128 });
}
void ShopNPC::Update()
{
}