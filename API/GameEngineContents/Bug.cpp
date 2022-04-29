#include "Bug.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

Bug::Bug() 
{
}

Bug::~Bug() 
{
}

void Bug::Start()
{
	SetPosition({ 640,320 });
	//SetPosition({ 256.0f,1090.f });
	GameEngineRenderer* Renderer = CreateRenderer("Bug.bmp");
	GameEngineCollision* Col_ = CreateCollision("SeedShopNPC", { 64,128 });
}
void Bug::Update()
{
}