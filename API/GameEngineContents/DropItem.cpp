#include "DropItem.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Tool.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
DropItem::DropItem()
	:SellValue_(0),
	IsStop_(false),
	IndexNum_(0),
	DropSeedType_(SeedType::Max),
	DropItem_(PlayerItem::Max),
	DropItemKind_(PlayerItemKind::NoItem),
	CurDropItem_(PlayerItem::Max),
	ObjectCol_(nullptr),
	Object_(nullptr)
{

}

DropItem::~DropItem() 
{

}

void DropItem::Start()// ???? 192
{
	Object_ = CreateRendererToScale("Objects.bmp",{48,48},static_cast<int>(ORDER::DROPITEM));

	Object_->CreateAnimation("Objects.bmp", "PhotatoItem", 192, 192, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "KaleItem", 250, 250, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "CauliFlowerItem", 190, 190, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "ParsnipItem", 24, 24, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "BeanItem", 188, 188, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "MelonItem", 254, 254, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "PepperItem", 260, 260, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "BlueberrieItem", 258, 258, 0.8f, true);


	Object_->CreateAnimation("Objects.bmp", "amethystItem", 66, 66, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "CoalItem", 382, 382, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "CopperItem", 378, 378, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "DiamondItem", 72, 72, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "EmeraldItem", 60, 60, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "RubyItem", 64, 64, 0.8f, true);

	Object_->CreateAnimation("Objects.bmp", "SlimeItem", 766, 766, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "BugItem", 684, 684, 0.8f, true);

	Object_->CreateAnimation("Objects.bmp", "StoneItem", 390, 390, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "BranchItem", 388, 388, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "GrassItem", 771, 771, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "Max", 23, 23, 0.8f, true);

	Object_->CreateAnimation("Objects.bmp", "EggItem", 174, 174, 0.8f, true);
	Object_->CreateAnimation("Objects.bmp", "MilkItem", 184, 184, 0.8f, true);

	Object_->ChangeAnimation("Max");
	ObjectCol_ = CreateCollision("DropItem", { 48,48 });

	
}
std::string DropItem::ItemToString(PlayerItem _Item)
{
	if (PlayerItem::PhotatoItem == _Item)
	{
		IndexNum_= 192;
		SellValue_ = 80;
		return "PhotatoItem";
	}
	else if (PlayerItem::KaleItem == _Item)
	{
		IndexNum_ = 250;
		SellValue_ = 110;
		return "KaleItem";
	}
	else if (PlayerItem::CauliFlowerItem == _Item)
	{
		IndexNum_ = 190;
		SellValue_ = 175;
		return "CauliFlowerItem";
	}
	else if (PlayerItem::ParsnipItem == _Item)
	{
		IndexNum_ = 24;
		SellValue_ = 35;
		return "ParsnipItem";
	}
	else if (PlayerItem::BeanItem == _Item)
	{
		IndexNum_ = 188;
		SellValue_ = 40;
		return "BeanItem";
	}
	else if (PlayerItem::MelonItem == _Item)
	{
		IndexNum_ = 254;
		SellValue_ = 250;
		return "MelonItem";
	}
	else if (PlayerItem::PepperItem == _Item)
	{
		IndexNum_ = 260;
		SellValue_ = 40;
		return "PepperItem";
	}
	else if (PlayerItem::BlueberrieItem == _Item)
	{
		IndexNum_ = 258;
		SellValue_ = 50;
		return "BlueberrieItem";
	}
	else if (PlayerItem::StoneItem == _Item)
	{
		IndexNum_ = 390;
		SellValue_ = 10;
		return "StoneItem";
		
	}
	else if (PlayerItem::GrassItem == _Item)
	{
		IndexNum_ = 771;
		SellValue_ = 10;
		return "GrassItem";

	}
	else if (PlayerItem::BranchItem == _Item || PlayerItem::TreeItem == _Item)
	{
		IndexNum_ = 388;
		SellValue_ = 10;
		return "BranchItem";
	}
	else if (PlayerItem::amethystItem == _Item)
	{
		IndexNum_ = 66;
		SellValue_ = 100;
		return "amethystItem";
	}
	else if (PlayerItem::CoalItem == _Item)
	{
		IndexNum_ = 382;
		SellValue_ = 10;
		return "CoalItem";
	}
	else if (PlayerItem::CopperItem == _Item)
	{
		IndexNum_ = 378;
		SellValue_ = 15;
		return "CopperItem";
	}
	else if (PlayerItem::DiamondItem == _Item)
	{
		IndexNum_ = 72;
		SellValue_ = 750;
		return "DiamondItem";
	}
	else if (PlayerItem::EmeraldItem == _Item)
	{
		IndexNum_ = 60;
		SellValue_ = 250;
		return "EmeraldItem";
	}
	else if (PlayerItem::RubyItem == _Item)
	{
		IndexNum_ = 64;
		SellValue_ = 250;
		return "RubyItem";
	}
	else if (PlayerItem::SlimeItem == _Item)
	{
		IndexNum_ = 766;
		SellValue_ = 200;
		return "SlimeItem";
	}
	else if (PlayerItem::BugItem == _Item)
	{
		IndexNum_ = 684;
		SellValue_ = 400;
		return "BugItem";
	}
	else if (PlayerItem::EggItem == _Item)
	{
	IndexNum_ = 174;
	SellValue_ = 200;
	return "EggItem";
	}
	else if (PlayerItem::MilkItem == _Item)
	{
	IndexNum_ = 184;
	SellValue_ = 300;
	return "MilkItem";
	}
	else
	{
	return "";
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

	if (IsStop_ == false&& PlayerItem::EggItem != CurDropItem_ && PlayerItem::MilkItem != CurDropItem_)
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
	if (CheckDir_ >= 150)
	{
		return;
	}
	if (CheckDir_ <= 30.0f)
	{

		Tool::ToolSet->CreateItem(CurDropItem_,DropItemKind_, "Objects.bmp", IndexNum_, SellValue_);
		Sound_ = GameEngineSound::SoundPlayControl("coin.wav");
		Sound_.Volume(0.8f);
		Death();
		return;
	}

	MoveDir_.Normal2D();
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 400.0f); // ?ӵ?

}