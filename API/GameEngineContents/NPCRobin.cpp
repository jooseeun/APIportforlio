#include "NPCRobin.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
NPCRobin::NPCRobin() 
{
}

NPCRobin::~NPCRobin() 
{
}

void NPCRobin::Start()
{
	SetPosition({ 545,1147 });
	GameEngineRenderer* Renderer = CreateRenderer("Robin.bmp");
	GameEngineCollision* Col_ = CreateCollision("Robin", { 64,128 });
}
void NPCRobin::Update()
{
}