#include "Cow.h"
#include "PlayerEnum.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
Cow::Cow() 
{
}

Cow::~Cow() 
{
}


void Cow::Start()
{
	CowRender_ = CreateRenderer("BabyCow.bmp", static_cast<int>(ORDER::PLAYER));
	CowCol_ = CreateCollision("Cow", { 64,64 });

}
void Cow::Update()
{

}