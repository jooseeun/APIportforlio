#include "Crops.h"
#include "DropItem.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
Crops::Crops()
{
	CurSeedType_ = SeedType::Max;
}

Crops::~Crops()
{
}

void Crops::Start()
{
	Crops_ = CreateRenderer("Crops.bmp", static_cast<int>(ORDER::CROP));
	Crops_->CreateAnimation("Crops.bmp", "Photato", 30, 30, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Kale", 45, 45, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "CauliFlower", 20, 20, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Max", 6, 6, 0.8f, true);

	Crops_->ChangeAnimation("Max");
	GameEngineCollision* CropsCol_ = CreateCollision("Crops", { 64,64 });
}

void Crops::Update()
{
	if (CurSeedType_ != SeedType_)
	{
		Crops_->ChangeAnimation(CropToString(SeedType_));
		CurSeedType_ = SeedType_;
	}
}

std::string Crops::CropToString(SeedType _SeedType)
{
	if (SeedType::Photato == _SeedType)
	{
		IndexNum_ = 30;
		Item_ = PlayerItem::PhotatoItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Photato";
	}
	else if (SeedType::Cauliflower == _SeedType)
	{
		IndexNum_ = 45;
		Item_ = PlayerItem::KaleItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Kale";
	}
	else if (SeedType::Kale == _SeedType)
	{
		IndexNum_ = 20;
		Item_ = PlayerItem::CauliFlowerItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "CauliFlower";
	}
}