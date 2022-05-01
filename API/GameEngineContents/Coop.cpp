#include "Coop.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>

Coop* Coop::MainCoop = nullptr;

Coop::Coop() 
{
}

Coop::~Coop() 
{
}

void Coop::Start()
{
	SetPosition({ 3420,830 });
	GameEngineRenderer* Renderer = CreateRenderer("Coop.bmp");
	GameEngineCollision* Col_ = CreateCollision("Object", { 381,261 },{0,100});
	GameEngineCollision* MoveMapCol_ = CreateCollision("CoopDoor", { 128,64}, { -240,224 });
}
void Coop::Update()
{
}