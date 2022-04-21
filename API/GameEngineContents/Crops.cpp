#include "Crops.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
Crops::Crops()
{
}

Crops::~Crops()
{
}

void Crops::Start()
{
	GameEngineRenderer* Crops_ = CreateRenderer("Crops.bmp");

	if (SeedType::Photato == SeedType_)
	{
		Crops_->SetIndex(30);
	}
	else if (SeedType::Kale == SeedType_)
	{
		Crops_->SetIndex(45);
	}
	else if (SeedType::Cauliflower == SeedType_)
	{
		Crops_->SetIndex(22);
	}

	GameEngineCollision* CropsCol_ = CreateCollision("Crops", { 64,64 });
}
void Crops::Update()
{

}
void Crops::Harvest()
{

}