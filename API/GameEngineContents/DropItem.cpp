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
	if (_Item != nullptr)
	{
		delete _Item;
		_Item = nullptr;
	}
}

void DropItem::Start()// ���� 192
{
	Object_ = CreateRendererToScale("Objects.bmp",{48,48},static_cast<int>(ORDER::DROPITEM));

	Object_->CreateAnimation("Objects.bmp", "PhotatoItem", 192, 192, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "KaleItem", 250, 250, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "CauliFlowerItem", 190, 190, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "StoneItem", 390, 390, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "BranchItem", 388, 388, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "GrassItem", 771, 771, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "Max", 23, 23, 0.8f, true);

	Object_->ChangeAnimation("Max");
	ObjectCol_ = CreateCollision("DropItem", { 48,48 });

	
}
std::string DropItem::ItemToString(PlayerItem _Item)
{
	if (PlayerItem::PhotatoItem == _Item)
	{
		IndexNum_= 192;
		return "PhotatoItem";
	}
	else if (PlayerItem::KaleItem == _Item)
	{
		IndexNum_ = 250;
		return "KaleItem";
	}
	else if (PlayerItem::CauliFlowerItem == _Item)
	{
		IndexNum_ = 190;
		return "CauliFlowerItem";
	}
	else if (PlayerItem::StoneItem == _Item)
	{
		IndexNum_ = 390;
		return "StoneItem";
		
	}
	else if (PlayerItem::GrassItem == _Item)
	{
		IndexNum_ = 771;
		return "GrassItem";

	}
	else if (PlayerItem::BranchItem == _Item || PlayerItem::TreeItem == _Item)
	{
		IndexNum_ = 388;
		return "BranchItem";
	}


}
void DropItem::Update()
{
	
	if (CurDropItem_ != DropItem_)
	{
		Object_->ChangeAnimation(ItemToString(DropItem_));
		InitPos_ = GetPosition();
		Move_ = float4{ 50,-200 };
		IsStop_ = false;
		CurDropItem_ = DropItem_;
	}

	if (IsStop_ == false)
	{
		DropMove();
	}
	else
	{
		MoveToPlayer();
	}
	
}
void DropItem::DropMove()
{
	Move_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 500.0f;
	SetMove(Move_ * GameEngineTime::GetDeltaTime());

	if (GetPosition().y > InitPos_.y)
	{
		IsStop_ = true;
	}
}
void DropItem::MoveToPlayer()
{
	float4 MoveDir_ = Player::MainPlayer->GetPosition() - GetPosition();
	float CheckDir_ = MoveDir_.Len2D();
	if (CheckDir_ >= 100)
	{
		return;
	}
	if (CheckDir_ <= 30)
	{
		 _Item = new ItemData();
		_Item->ItemKind_ = DropItemKind_;
		_Item->ItemName_ = CurDropItem_;
		_Item->Click_ = false;
		Tool::ToolSet->CreateItem(_Item, "Objects.bmp", IndexNum_);


		Death();
		return;
	}

	MoveDir_.Normal2D();
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 120.0f); // �ӵ�

}