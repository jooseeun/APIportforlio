#include "Bug.h"
#include "Player.h"
#include "DropItem.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineTime.h>
Bug::Bug()
	:CurDir_(MonsterDir::Front),
	PreDir_(MonsterDir::Left),
	Move_(float4::ZERO),
	Start_(false),
	Hp_(16),
	Hit_(false),
	IsDeath_(false)
{
}

Bug::~Bug()
{
}

void Bug::Start()
{
	BugRender_ = CreateRenderer("Bug.bmp");

	BugRender_->CreateAnimation("Bug.bmp", "BugFront", 0, 3, 0.3f, true);
	BugRender_->CreateAnimation("Bug.bmp", "BugBack", 8, 11, 0.3f, true);
	BugRender_->CreateAnimation("Bug.bmp", "BugHit", 4, 7, 0.1f, true);
	BugRender_->CreateAnimation("Bug.bmp", "BugDeath", 16, 16, 0.2f, true);
	BugRender_->ChangeAnimation("BugFront");
	BugCol_ = CreateCollision("Monster", { 60,48 }, { 0,24 });

}
void Bug::Update() // 렌더링 해준곳에서 무조건 좌 우로 움직이기 , 플레이어 일정거리 가까이 가면 공격하기
{//766
	if (Start_ == false)
	{
		InitPos_ = GetPosition();
		Start_ = true; 
		Move_ = InitPos_;
	}
	DeathCheck();
	CurAniUpdate();
	MoveUpdate();
}
void Bug::DeathCheck()
{
	if (Player::MainPlayer->IsHitReturn() == true && BugCol_->CollisionCheck("LongSword"))
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
void Bug::CurAniUpdate()
{
	if (Hit_ == true)
	{
		BugRender_->ChangeAnimation("BugHit");
		return;
	}
	if (IsDeath_ == true)
	{
		BugRender_->SetPivot({ 0,32 });
		BugRender_->ChangeAnimation("BugDeath");
		return;
	}
	if (CurDir_ == MonsterDir::Front)
	{
		BugRender_->ChangeAnimation("BugFront");
	}
	else if (CurDir_ == MonsterDir::Back)
	{
		BugRender_->ChangeAnimation("BugBack");
	}


}
void Bug::MoveUpdate()
{
	if (Hit_ == true)
	{
		if (true == BugRender_->IsEndAnimation())
		{

			Hit_ = false;
		}
		return;
	}
	if (IsDeath_ == true)
	{
		if (true == BugRender_->IsEndAnimation())
		{
			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
			DropItem_->SetPosition(GetPosition());
			DropItem_->SetItem(PlayerItem::BugItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			Death();
		}
		return;
	}



	if (CurDir_ == MonsterDir::Front)
	{
		if (Move_.y > InitPos_.y + 180.0f)
		{
			PreDir_ = CurDir_; 
			Move_ = InitPos_;
			CurDir_ = MonsterDir::Back;
		}
		Move_ += float4::DOWN;
		MoveSet_ = float4::DOWN;
		SetMove(MoveSet_ * GameEngineTime::GetDeltaTime() * 100.0f);
	}

	else if (CurDir_ == MonsterDir::Back) // 왼쪽이동
	{
		if(Move_.y < InitPos_.y - 180.0f)
		{
			PreDir_ = CurDir_;
			Move_ = InitPos_;
			CurDir_ = MonsterDir::Front;
		}
		Move_ += float4::UP;
		MoveSet_ = float4::UP;
		SetMove(MoveSet_ * GameEngineTime::GetDeltaTime() * 100.0f);

	}


}