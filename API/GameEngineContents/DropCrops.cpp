#include "DropCrops.h"
#include "Player.h"
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
	Crops_ = CreateRendererToScale("Objects.bmp",{16,16});

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
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 100.0f); // 100은 속도

}