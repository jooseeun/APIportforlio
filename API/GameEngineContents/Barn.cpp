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
	GameEngineCollision* Col_ = CreateCollision("Object", { 446,320 },{0,100});
}
void Barn::Update()
{
}