#include "Crops.h"
#include "DropItem.h"
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

	GameEngineCollision* CropsCol_ = CreateCollision("Crops", { 64,64 });
}

void Crops::Update()
{
	if (IsHarvest_ == true)
	{
		Harvest();
		Death(0.0f); // �̰� �������Ѱ� ��������ϴ� �͵� �ٽ� �ؾߵ� ��
		IsHarvest_ = false;
	}
}

void Crops::Harvest() 
{
	DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::CROP));
	DropItem_->SetPosition(GetPosition());
	DropItem_->SetCropsType(SeedType_);
	DropItem_->SetItem(Item_);
	DropItem_->SetItemKind(ItemKind_);
	
}