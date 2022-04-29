#include "Slime.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineTime.h>
Slime::Slime()
	:CurDir_(SlimeDir::Front),
	PreDir_(SlimeDir::Left),
	Move_(float4::ZERO),
	Start_(false)
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
	SlimeRender_->CreateAnimation("Slime.bmp", "SlimeJump", 16, 19, 0.3f, true);
	SlimeRender_->ChangeAnimation("Slimedefault");
	SlimeCol_ = CreateCollision("Slime", { 64,64 });

	GameEngineCollision* SlimeCol_ = CreateCollision("Slime", { 64,64 });
}
void Slime::Update() // 렌더링 해준곳에서 무조건 좌 우로 움직이기 , 플레이어 일정거리 가까이 가면 공격하기
{
	if (Start_ == false)
	{
		InitPos_ = GetPosition();
		Start_ = true;
	}
	MoveUpdate();
	CurAniUpdate();
}
void Slime::CurAniUpdate()
{
	if (CurDir_ == SlimeDir::Front)
	{
		SlimeRender_->ChangeAnimation("Slimedefault");
	}
	else if (CurDir_ == SlimeDir::Right)
	{
		SlimeRender_->ChangeAnimation("SlimeRight");
	}
	else if (CurDir_ == SlimeDir::Left)
	{
		SlimeRender_->ChangeAnimation("SlimeLeft");
	}
}
void Slime::MoveUpdate()
{
	
	float Time = 5.0f;
	float4 MoveSet_;
	if (CurDir_ == SlimeDir::Front) // 오른쪽 이동
	{
		if (0 < Time)
		{
			Time -= GameEngineTime::GetDeltaTime();
		}
		Move_ = InitPos_;

		if (PreDir_ == SlimeDir::Left)
		{
			CurDir_ = SlimeDir::Right;
		}

		else if (PreDir_ == SlimeDir::Right)
		{
			CurDir_ = SlimeDir::Left;
		}
	}

	else if(CurDir_ == SlimeDir::Right)
	{
		if (Move_.x > InitPos_.x+180.0f)
		{
			PreDir_ = CurDir_;
			CurDir_ = SlimeDir::Front;
		}
		Move_ += float4::RIGHT;
		MoveSet_ = float4::RIGHT;
		SetMove(MoveSet_ * GameEngineTime::GetDeltaTime() * 100.0f);
	}

	else if (CurDir_ == SlimeDir::Left) // 왼쪽이동
	{
		if (Move_.x < InitPos_ .x - 180.0f)
		{
			PreDir_ = CurDir_;
			CurDir_ = SlimeDir::Front;
		}
		Move_ += float4::LEFT;
		MoveSet_ = float4::LEFT;
		SetMove(MoveSet_ * GameEngineTime::GetDeltaTime() * 100.0f);

	}


}