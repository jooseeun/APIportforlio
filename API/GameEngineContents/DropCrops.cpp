#include "DropCrops.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "Tool.h"

#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
DropCrops::DropCrops() 
{
}

DropCrops::~DropCrops() 
{
}

void DropCrops::Start()// ���� 192
{
	Crops_ = CreateRendererToScale("Objects.bmp",{16,16},static_cast<int>(ORDER::ITEM));

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

	CropsCol_ = CreateCollision("DropCrops", { 16,16 });
}

void DropCrops::Update()
{
	MoveToPlayer();
}

void DropCrops::MoveToPlayer()
{
	float4 MoveDir_ = Player::MainPlayer->GetPosition() - GetPosition();
	float CheckDir_ = MoveDir_.Len2D();
	if (CheckDir_ >= 400)
	{
		return;
	}
	if (CheckDir_ <= 16)
	{
		//ItemData* _Item = new ItemData();
		////_Item->InvenPivot_ = 6;
		////_Item->InvenFloor_ = InvenFloor::First; -> ���ڸ� ä���ִ� �Լ� �������
		//_Item->ItemKind_ = PlayerItemKind::SeedItem;
		//_Item->ItemName_ = PlayerItem::KaleSeedItem;
		//_Item->Render = CreateRenderer("Objects.bmp");
		//_Item->Render->SetIndex(477);
		//_Item->Render->CameraEffectOff();
		//_Item->Click_ = false;
		//Tool::ToolSet->CreateItem(_Item);
		Death();
		return;
	}

	MoveDir_.Normal2D();
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 80.0f); // �ӵ�

}