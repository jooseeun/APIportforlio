#include "Chicken.h"
#include "PlayerEnum.h"
#include "ContentsEnums.h"
#include "Time.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineInput.h>
Chicken::Chicken()
	:CurState_(AnimalState::Idle),
	CurDir_(AnimalDir::Front),
	IsBaby_(true),
	Time(5.0f),
	FirstDay_(0)
{

}

Chicken::~Chicken() 
{
}

void Chicken::Start()
{
	ChickenRender_ = CreateRenderer("BabyChicken.bmp", static_cast<int>(ORDER::PLAYER));
	ChickenCol_ = CreateCollision("Chicken", { 64,64 });

	ChickenRender_->CreateAnimation("BabyChicken.bmp", "BabyIdle", 16, 17, 0.3f, false);
	ChickenRender_->CreateAnimation("BabyChicken.bmp", "BabyWalkFront", 0, 3, 0.3f, true);
	ChickenRender_->CreateAnimation("BabyChicken.bmp", "BabyWalkRight", 4, 7, 0.3f, true);
	ChickenRender_->CreateAnimation("BabyChicken.bmp", "BabyWalkBack", 8, 11, 0.3f, true);
	ChickenRender_->CreateAnimation("BabyChicken.bmp", "BabyWalkLeft", 12, 15, 0.3f, true);

	ChickenRender_->CreateAnimation("Chicken.bmp", "Idle", 16, 17, 0.3f, false);
	ChickenRender_->CreateAnimation("Chicken.bmp", "WalkFront", 0, 3, 0.3f, true);
	ChickenRender_->CreateAnimation("Chicken.bmp", "WalkRight", 4, 7, 0.3f, true);
	ChickenRender_->CreateAnimation("Chicken.bmp", "WalkBack", 8, 11, 0.3f, true);
	ChickenRender_->CreateAnimation("Chicken.bmp", "WalkLeft", 12, 15, 0.3f, true);
	ChickenRender_->ChangeAnimation("BabyIdle");
	FirstDay_ = Time::TimeSet->GetGameDay_();

}  
void Chicken::Update()
{
	if (FirstDay_ != Time::TimeSet->GetGameDay_())
	{
		IsBaby_ = false;
		ChickenRender_->ChangeAnimation(GetDirString());
	}
	if (IsBaby_ == false)
	{
		if (Time::TimeSet->GetGameHour_() == 6)
		{
			//¾Ë »ý¼º
		}
	}
	StateUpdate();
}

void Chicken::ChangeState(AnimalState _State)
{
	if (CurState_ != _State)
	{
		CurState_ = _State;
		ChangeAni();
		switch (_State)
		{
		case AnimalState::Idle:
			IdleStart();
			break;
		case AnimalState::Walk:
			WalkStart();
			break;
		case AnimalState::Max:
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

void Chicken::StateUpdate()
{
	switch (CurState_)
	{
	case AnimalState::Idle:
		IdleUpdate();
		break;
	case AnimalState::Walk:
		WalkUpdate();
		break;
	case AnimalState::Max:
		break;
	default:
		break;
	}
}

void Chicken::IdleUpdate()
{
	while (Time > 0)
	{
		Time -= 1.0 * GameEngineTime::GetDeltaTime();
		return;
	}
	//GameEngineRandom Ran_= GameEngineRandom();
	GameEngineRandom Ran_;
	NextPos_.x = Ran_.RandomFloat(360, 852);
	NextPos_.y = Ran_.RandomFloat(293, 461);
	CurPos_ = GetPosition();
	if (GetPosition().y >= NextPos_.y)
	{
		CurDir_  == AnimalDir::Back;
	}
	else
	{
		CurDir_ == AnimalDir::Front;
	}
	ChangeState(AnimalState::Walk);
	
}

void Chicken::WalkUpdate()
{
	float4 MoveDir_ = NextPos_ - GetPosition();
	float CheckDir_ = MoveDir_.Len2D();
	if (CheckDir_ < 0)
	{
		CurDir_ = AnimalDir::Front;
		ChangeState(AnimalState::Idle);
	}
	MoveDir_.Normal2D();
	if (true == GameEngineInput::GetInst()->IsPress("TimeFast"))
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 500.0f);
	}
	else
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 50.0f);
	}

}

void Chicken::IdleStart()
{
	Time = 5.0f;
}


void Chicken::WalkStart()
{

}

void Chicken::ChangeAni()
{
	if (IsBaby_ == true)
	{
		ChickenRender_->ChangeAnimation("Baby" + GetDirString());
	}
	else if(IsBaby_ == false)
	{
		ChickenRender_->ChangeAnimation(GetDirString());
	}
}
std::string Chicken::GetDirString()
{
	if (CurState_ == AnimalState::Idle)
	{
		return "Idle";
	}

	if (CurDir_ == AnimalDir::Front)
	{
		return "WalkFront";
	}
	else if (CurDir_ == AnimalDir::Back)
	{
		return "WalkBack";
	}
	else if (CurDir_ == AnimalDir::Left)
	{
		return "WalkLeft";
	}
	else if (CurDir_ == AnimalDir::Right)
	{
		return "WalkRight";
	}
	return "";
}