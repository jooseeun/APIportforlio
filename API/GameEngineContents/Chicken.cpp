#include "Chicken.h"
#include "PlayerEnum.h"
#include "ContentsEnums.h"
#include "Time.h"
#include "DropItem.h"
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
	FirstDay_(0),
	IsEgg_(false),
	CurHour_(0)
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
	if (FirstDay_ != Time::TimeSet->GetGameDay_()&&IsBaby_==true)
	{
		IsBaby_ = false;
		FirstHour_ = Time::TimeSet->GetGameHour_();
		ChickenRender_->ChangeAnimation(GetDirString());
	}
	else if (IsBaby_ == false)
	{
		if (CurHour_ != Time::TimeSet->GetGameHour_())//시간이 바뀌는 순간에 체크
		{
			IsEgg_ = true;
			if ((Time::TimeSet->GetGameHour_() - FirstHour_) % 12 == 0) 
			{
				CreateEgg();
			}
		}
	}

	StateUpdate();
	CurHour_ = Time::TimeSet->GetGameHour_();
}
void Chicken::CreateEgg()
{
	if (IsEgg_ == true)
	{
		DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
		DropItem_->SetPosition(GetPosition());
		DropItem_->SetItem(PlayerItem::EggItem);
		DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
		IsEgg_ = false;
	}

	IsEgg_ = false;
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
		if (true == GameEngineInput::GetInst()->IsPress("TimeFast"))
		{
			Time -= 1.0 * GameEngineTime::GetDeltaTime()*5.0f;
		}
		else
		{
			Time -= 1.0 * GameEngineTime::GetDeltaTime();
		}
		return;
	}

	NextPos_ = GetPosition();
	CurPos_ = GetPosition();


	if (CurDir_ == AnimalDir::Front)
	{
		NextPos_.y = 461.0f;
	}
	else if (CurDir_ == AnimalDir::Back)
	{
		NextPos_.y = 293.0f;
	}
	else if (CurDir_ == AnimalDir::Right)
	{
		NextPos_.x = 852.0f;
	}
	else if (CurDir_ == AnimalDir::Left)
	{
		NextPos_.x = 360.0f;
	}

	ChangeState(AnimalState::Walk);
	
}

void Chicken::WalkUpdate()
{
	float4 MoveDir_ = NextPos_ - GetPosition();
	float CheckDir_ = MoveDir_.Len2D();

	if (CheckDir_ < 5)
	{
		if (CurDir_ == AnimalDir::Front)
		{
			CurDir_ = AnimalDir::Right;
		}
		else if (CurDir_ == AnimalDir::Back)
		{
			CurDir_ = AnimalDir::Left;
		}
		else if (CurDir_ == AnimalDir::Right)
		{
			CurDir_ = AnimalDir::Back;
		}
		else if (CurDir_ == AnimalDir::Left)
		{
			CurDir_ = AnimalDir::Front;
		}

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