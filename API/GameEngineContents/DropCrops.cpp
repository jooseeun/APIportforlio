#include "DropCrops.h"
#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
DropCrops::DropCrops() 
{
}

DropCrops::~DropCrops() 
{
}

void DropCrops::Start()// 감자 192
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

	CropsCol_ = CreateCollision("Crops", { 64,64 });
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
		Death();
		return;
	}

	MoveDir_.Normal2D();
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 80.0f); // 속도

}