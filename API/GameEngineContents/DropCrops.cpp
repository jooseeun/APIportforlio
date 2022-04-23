#include "DropCrops.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
DropCrops::DropCrops() 
{
}

DropCrops::~DropCrops() 
{
}

void DropCrops::Start()// °¨ÀÚ 192
{
	Crops_ = CreateRenderer("Objects.bmp");

	if (SeedType::Photato == SeedType_)
	{
		Crops_->SetIndex(192);
	}
	else if (SeedType::Kale == SeedType_)
	{
		Crops_->SetIndex(45);
	}
	else if (SeedType::Cauliflower == SeedType_)
	{
		Crops_->SetIndex(22);
	}

	CropsCol_ = CreateCollision("Crops", { 64,64 });
}

void DropCrops::Update()
{

}