#include "Slime.h"
#include "Player.h"
#include "DropItem.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineTime.h>
Slime::Slime()
	:CurDir_(MonsterDir::Front),
	PreDir_(MonsterDir::Left),
	Move_(float4::ZERO),
	Start_(false),
	Hp_(16),
	Hit_(false),
	IsDeath_(false)
{
}

Slime::~Slime() 
{
}

void Slime::Start()
{
	SlimeRender_ = CreateRenderer("Slime.bmp");

	SlimeRender_->CreateAnimation("Slime.bmp", "Slimedefault", 0, 3, 0.3f, true);
	SlimeRender_->CreateAnimation("Slime.bmp", "SlimeLeft", 4, 7, 0.3f, true);
	SlimeRender_->CreateAnimation("Slime.bmp", "SlimeRight", 8, 11, 0.3f, true);
	SlimeRender_->CreateAnimation("Slime.bmp", "SlimeHit", 16, 19, 0.1f, true);
	SlimeRender_->CreateAnimation("Slime.bmp", "SlimeDeath", 20, 20, 0.1f, true);
	SlimeRender_->ChangeAnimation("Slimedefault");
	SlimeCol_ = CreateCollision("Monster", { 60,48 },{0,24});

}
void Slime::Update() // 렌더링 해준곳에서 무조건 좌 우로 움직이기 , 플레이어 일정거리 가까이 가면 공격하기
{//766
	if (Start_ == false)
	{
		InitPos_ = GetPosition();
		Start_ = true;
	}
	DeathCheck();
	CurAniUpdate();
	MoveUpdate();
}
void Slime::DeathCheck()
{
	if (Player::MainPlayer->IsHitReturn() == true&& SlimeCol_->CollisionCheck("LongSword"))
	{
		Hp_ -= 4;
		if (Hp_ <= 0)
		{
		
			IsDeath_ = true;
			return;
		}

		Hit_ = true;
		Player::MainPlayer->IsHitOff();
	}
	
	

	
}
void Slime::CurAniUpdate()
{
	if (Hit_ == true)
	{
		SlimeRender_->ChangeAnimation("SlimeHit");
		return;
	}
	if (IsDeath_ == true)
	{
		SlimeRender_->SetPivot({ 0,32 });
		SlimeRender_->ChangeAnimation("SlimeDeath");
		return;
	}
	if (CurDir_ == MonsterDir::Front)
	{
		SlimeRender_->ChangeAnimation("Slimedefault");
	}
	else if (CurDir_ == MonsterDir::Right)
	{
		SlimeRender_->ChangeAnimation("SlimeRight");
	}
	else if (CurDir_ == MonsterDir::Left)
	{
		SlimeRender_->ChangeAnimation("SlimeLeft");
	}

}
void Slime::MoveUpdate()
{
	if (Hit_ == true)
	{
		if (true == SlimeRender_->IsEndAnimation())
		{
			
			Hit_ = false;
		}
		return;
	}
	if (IsDeath_ == true )
	{
		if (true == SlimeRender_->IsEndAnimation())
		{
			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
			DropItem_->SetPosition(GetPosition());
			DropItem_->SetItem(PlayerItem::SlimeItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			Death();
		}
		return;
	}
	float Time = 5.0f;
	float4 MoveSet_;
	if (CurDir_ == MonsterDir::Front) // 오른쪽 이동
	{
		if (0 < Time)
		{
			Time -= GameEngineTime::GetDeltaTime();
		}
		Move_ = InitPos_;

		if (PreDir_ == MonsterDir::Left)
		{
			CurDir_ = MonsterDir::Right;
		}

		else if (PreDir_ == MonsterDir::Right)
		{
			CurDir_ = MonsterDir::Left;
		}
	}
	
	else if(CurDir_ == MonsterDir::Right)
	{
		if (Move_.x > InitPos_.x+180.0f)
		{
			PreDir_ = CurDir_;
			CurDir_ = MonsterDir::Front;
		}
		Move_ += float4::RIGHT;
		MoveSet_ = float4::RIGHT;
		SetMove(MoveSet_ * GameEngineTime::GetDeltaTime() * 100.0f);
	}

	else if (CurDir_ == MonsterDir::Left) // 왼쪽이동
	{
		if (Move_.x < InitPos_ .x - 180.0f)
		{
			PreDir_ = CurDir_;
			CurDir_ = MonsterDir::Front;
		}
		Move_ += float4::LEFT;
		MoveSet_ = float4::LEFT;
		SetMove(MoveSet_ * GameEngineTime::GetDeltaTime() * 100.0f);

	}


}