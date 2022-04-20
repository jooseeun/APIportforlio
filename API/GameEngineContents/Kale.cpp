#include "Kale.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
Kale::Kale() 
{
}

Kale::~Kale() 
{
}

void Kale::Start()
{
	GameEngineRenderer* Kale_ = CreateRenderer("Crops.bmp");
	Kale_->SetIndex(45);

	GameEngineCollision* KaleCol_= CreateCollision("Kale", { 64,64 });
}
void Kale::Update()
{

}