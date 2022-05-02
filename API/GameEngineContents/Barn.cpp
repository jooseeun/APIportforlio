#include "Barn.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

Barn* Barn::MainBarn = nullptr;

Barn::Barn() 
{
}

Barn::~Barn() 
{
}

void Barn::Start()
{
	SetPosition({ 2920,830 });
	GameEngineRenderer* Renderer = CreateRenderer("Barn.bmp");
	GameEngineCollision* Col_ = CreateCollision("Object", { 446,261 },{0,100});
	GameEngineCollision* MoveMapCol_ = CreateCollision("BarnDoor", { 64,64 }, { -132,200 });
}
void Barn::Update()
{
}