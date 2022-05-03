#include "Chicken.h"
#include "PlayerEnum.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
Chicken::Chicken() 
{
}

Chicken::~Chicken() 
{
}

void Chicken::Start()
{
	ChickenRender_ = CreateRenderer("BabyChicken.bmp", static_cast<int>(ORDER::PLAYER));
	ChickenCol_ = CreateCollision("Chicken", { 64,64 });
}  
void Chicken::Update()
{

}