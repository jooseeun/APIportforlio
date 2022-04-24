#include "DropItem.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Tool.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
DropItem::DropItem() 
{
}

DropItem::~DropItem() 
{
}

void DropItem::Start()// 감자 192
{
	Crops_ = CreateRendererToScale("Objects.bmp",{16,16},static_cast<int>(ORDER::ITEM));

	if (SeedType::Photato == DropSeedType_)
	{
		IndexNum_ = 192;
	}
	else if (SeedType::Kale == DropSeedType_)
	{
		IndexNum_ = 45;
	}
	else if (SeedType::Cauliflower == DropSeedType_)
	{
		IndexNum_ = 22;
	}

	Crops_->SetIndex(IndexNum_);
	CropsCol_ = CreateCollision("DropItem", { 16,16 });
}

void DropItem::Update()
{
	MoveToPlayer();
}

void DropItem::MoveToPlayer()
{
	float4 MoveDir_ = Player::MainPlayer->GetPosition() - GetPosition();
	float CheckDir_ = MoveDir_.Len2D();
	if (CheckDir_ >= 400)
	{
		return;
	}
	if (CheckDir_ <= 16)
	{
		ItemData* _Item = new ItemData();
		_Item->ItemKind_ = DropItemKind_;
		_Item->ItemName_ = DropItem_;
		_Item->Click_ = false;
		Tool::ToolSet->CreateItem(_Item, "Objects.bmp", IndexNum_);

		Death();
		return;
	}

	MoveDir_.Normal2D();
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 80.0f); // 속도

}