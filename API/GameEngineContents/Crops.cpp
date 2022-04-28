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
	Crops_ = CreateRenderer("Crops.bmp", static_cast<int>(ORDER::PLAYER));
	Crops_->CreateAnimation("Crops.bmp", "Photato", 30, 30, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Kale", 45, 45, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "CauliFlower", 22, 22, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Parsnip", 5, 5, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Bean", 14, 14, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Melon", 38, 38, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Pepper", 54, 54, 0.8f, true);
	Crops_->CreateAnimation("Crops.bmp", "Blueberrie", 62, 62, 0.8f, true);
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
	else if (SeedType::Kale == _SeedType)
	{
		IndexNum_ = 45;
		Item_ = PlayerItem::KaleItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Kale";
	}
	else if (SeedType::Cauliflower== _SeedType)
	{
		IndexNum_ = 22;
		Item_ = PlayerItem::CauliFlowerItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "CauliFlower";
	}
	else if (SeedType::Parsnip == _SeedType)
	{
		IndexNum_ = 5;
		Item_ = PlayerItem::ParsnipItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Parsnip";
	}
	else if (SeedType::Bean == _SeedType) 
	{
		IndexNum_ = 14;
		Item_ = PlayerItem::BeanItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Bean";
	}
	else if (SeedType::Melon == _SeedType)
	{
		IndexNum_ = 38;
		Item_ = PlayerItem::MelonItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Melon";
	}
	else if (SeedType::Pepper == _SeedType)
	{
		IndexNum_ = 54;
		Item_ = PlayerItem::PepperItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Pepper";
	}
	else if (SeedType::Blueberrie == _SeedType)
	{
		IndexNum_ = 62;
		Item_ = PlayerItem::BlueberrieItem;
		ItemKind_ = PlayerItemKind::CropsItem;
		return "Blueberrie";
	}
}