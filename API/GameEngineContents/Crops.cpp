#include "Crops.h"
#include "DropItem.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
Crops::Crops()
	:IsHarvest_(false),
	SeedType_(SeedType::Max)
{
}

Crops::~Crops()
{
}

void Crops::Start()
{
	
}

void Crops::Update()
{
	if (SeedType::Max != SeedType_&& IsHarvest_==false)
	{
		Harvest();
		IsHarvest_ = true;

	}
}

void Crops::Harvest() 
{
	Crops_ = CreateRenderer("Crops.bmp", static_cast<int>(ORDER::CROP));

	if (SeedType::Photato == SeedType_)
	{
		Crops_->SetIndex(30);
		Item_ = PlayerItem::PhatatoItem;
		ItemKind_ = PlayerItemKind::CropsItem;
	}
	else if (SeedType::Kale == SeedType_)
	{
		Crops_->SetIndex(45);
		Item_ = PlayerItem::KaleItem;
		ItemKind_ = PlayerItemKind::CropsItem;
	}
	else if (SeedType::Cauliflower == SeedType_)
	{
		Crops_->SetIndex(22);
		Item_ = PlayerItem::CauliFlowerItem;
		ItemKind_ = PlayerItemKind::CropsItem;
	}

	CropsCol_ = CreateCollision("Crops", { 64,64 });
	
}