#include "Cauliflower.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
Cauliflower::Cauliflower() 
{
}

Cauliflower::~Cauliflower() 
{
}

void Cauliflower::Start()
{
	GameEngineRenderer* Cauliflower_ = CreateRenderer("Crops.bmp");
	Cauliflower_->SetIndex(22);

	GameEngineCollision* CauliflowerCol_ = CreateCollision("Cauliflower", { 64,64 });
}
void Cauliflower::Update()
{

}