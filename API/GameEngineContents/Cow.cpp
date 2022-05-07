#include "Cow.h"
#include "PlayerEnum.h"
#include "ContentsEnums.h"
#include "Time.h"
#include "DropItem.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineInput.h>
Cow::Cow()
	:CurState_(AnimalState::Idle),
	CurDir_(AnimalDir::Front),
	IsBaby_(true),
	Time(5.0f),
	FirstDay_(0),
	IsMilk_(false)
{

}

Cow::~Cow()
{
}

void Cow::Start()
{
	CowRender_ = CreateRenderer("BabyCow.bmp", static_cast<int>(ORDER::PLAYER));
	CowCol_ = CreateCollision("Cow", { 64,64 });

	CowRender_->CreateAnimation("BabyCow.bmp", "BabyIdle", 12, 13, 0.3f, false);
	CowRender_->CreateAnimation("BabyCow.bmp", "BabyWalkFront", 0, 3, 0.3f, true);
	CowRender_->CreateAnimation("BabyCow.bmp", "BabyWalkRight", 4, 7, 0.3f, true);
	CowRender_->CreateAnimation("BabyCow.bmp", "BabyWalkBack", 8, 11, 0.3f, true);
	CowRender_->CreateAnimation("BabyCowL.bmp", "BabyWalkLeft", 4, 7, 0.3f, true);

	CowRender_->CreateAnimation("Cow.bmp", "Idle", 12, 13, 0.3f, false);
	CowRender_->CreateAnimation("Cow.bmp", "WalkFront", 0, 3, 0.3f, true);
	CowRender_->CreateAnimation("Cow.bmp", "WalkRight", 4, 7, 0.3f, true);
	CowRender_->CreateAnimation("Cow.bmp", "WalkBack", 8, 11, 0.3f, true);
	CowRender_->CreateAnimation("CowL.bmp", "WalkLeft", 4, 7, 0.3f, true);
	CowRender_->ChangeAnimation("BabyIdle");
	FirstDay_ = Time::TimeSet->GetGameDay_();

}
void Cow::Update()
{
	if (FirstDay_ != Time::TimeSet->GetGameDay_() && IsBaby_ == true)
	{
		IsBaby_ = false;
		FirstHour_ = Time::TimeSet->GetGameHour_();
		CowRender_->ChangeAnimation(GetDirString());
	}
	if (IsBaby_ == false)
	{
		if (CurHour_ != Time::TimeSet->GetGameHour_())
		{
			if ((Time::TimeSet->GetGameHour_() - FirstHour_) % 12 == 0) // 12시간마다 우유 가능
			{
				IsMilk_ = true;
			}
		}

		float4 M = { -1,-1 };
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			if (true == CowCol_->NextPosCollisionCheck("MouseCol", { GetLevel()->GetCameraPos().x * M.x ,GetLevel()->GetCameraPos().y * M.y },
				CollisionType::Rect, CollisionType::Rect))//카메라 이펙트 꺼져있는건 이렇게 충돌체크해야됨
			{
				CreateMilk();
			}
		}
	}

	StateUpdate();
	CurHour_ = Time::TimeSet->GetGameHour_();
}
void Cow::CreateMilk()
{
	if (IsMilk_ == true) 
	{
		DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
		DropItem_->SetPosition(GetPosition());
		DropItem_->SetItem(PlayerItem::MilkItem);
		DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
		IsMilk_ = false;
	}

}
void Cow::ChangeState(AnimalState _State)
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

void Cow::StateUpdate()
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

void Cow::IdleUpdate()
{
	while (Time > 0)
	{
		if (true == GameEngineInput::GetInst()->IsPress("TimeFast"))
		{
			Time -= 10.0 * GameEngineTime::GetDeltaTime();
		}
		else
		{
			Time -= 1.0 * GameEngineTime::GetDeltaTime();
		}
		return;
	}

	GameEngineRandom Ran_;
	NextPos_.x = Ran_.RandomFloat(360, 852);
	NextPos_.y = Ran_.RandomFloat(293, 461);
	CurPos_ = GetPosition();
	if (GetPosition().y >= NextPos_.y)
	{
		CurDir_ = AnimalDir::Back;
	}
	else
	{
		CurDir_ = AnimalDir::Front;
	}
	ChangeState(AnimalState::Walk);

}

void Cow::WalkUpdate()
{
	float4 MoveDir_ = NextPos_ - GetPosition();
	float CheckDir_ = MoveDir_.Len2D();
	if (CheckDir_ < 10)
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

void Cow::IdleStart()
{
	Time = 10.0f;

}


void Cow::WalkStart()
{

}

void Cow::ChangeAni()
{
	if (IsBaby_ == true)
	{
		CowRender_->ChangeAnimation("Baby" + GetDirString());
	}
	else if (IsBaby_ == false)
	{
		CowRender_->ChangeAnimation(GetDirString());
	}
}
std::string Cow::GetDirString()
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