#include "Time.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
Time* Time::TimeSet = nullptr;

Time::Time() 
	:CurTime_(0.0f),
	GameHour_(6),
	GameMinute_(0),
	GameDay_(1)
{
}

Time::~Time() 
{
}

void Time::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("TimeFast"))
	{
		GameEngineInput::GetInst()->CreateKey("TimeFast", 'T');
	}
}

void Time::Update()
{
	CurTime_ += GameEngineTime::GetDeltaTime(); //10초씩 재주는 타이머, 10초에 게임시간은 10분이다.
	UpdateGameTime();

	if (true == GameEngineInput::GetInst()->IsPress("TimeFast"))
	{
		CurTime_ += 100.0f;
	}
}
void Time::UpdateGameTime()
{
	if (CurTime_ > 10.0f)
	{
		GameMinute_ += 10;
		CurTime_ = 0.0f;
	}

	if (GameMinute_ == 60)
	{
		GameHour_ += 1;
		GameMinute_ = 0;
	}
	
	if (GameHour_ == 24)
	{
		GameDay_ += 1;
		GameHour_ = 0;
	}
	
}

void Time::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	TimeSet = this;
}