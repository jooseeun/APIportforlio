#include "Crops.h"
#include "DropCrops.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
Crops::Crops()
	:IsHarvest_(false)
{
}

Crops::~Crops()
{
}

void Crops::Start()
{
	GameEngineRenderer* Crops_ = CreateRenderer("Crops.bmp", static_cast<int>(ORDER::CROP));

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
	if (IsHarvest_ == true)
	{
		Harvest();
		Death(0.0f);
		IsHarvest_ = false;
	}
}

void Crops::Harvest() 
{
	
	DropCrops* DropCrops_ = GetLevel()->CreateActor<DropCrops>(static_cast<int>(ORDER::CROP));
	DropCrops_->SetPosition(GetPosition());
	DropCrops_->SetCropsType(SeedType_);
	
}