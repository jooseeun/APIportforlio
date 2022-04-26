#include "Money.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>


Money* Money::MoneySet = nullptr;

Money::Money()
	:PlayerMoney_(500),
	Index_(0)
{
}

Money::~Money() 
{
}

void Money::Start()
{ //숫자는 8자리
	SetPosition({ 1226,217 });
	for (int i = 0; i < 8; i++)
	{
		MoneyIndex_[i] = 0;
		MoneyList_[i] = CreateRenderer("Money.bmp",static_cast<int>(ORDER::UIFONT));
		MoneyList_[i]->SetIndex(MoneyIndex_[i]);
		MoneyList_[i]->SetPivot({-24*static_cast<float>(i),0});
		MoneyList_[i]->CameraEffectOff();
	}
	MoneyList_[2]->SetIndex(5); // 처음 500원 지급
	MoneyIndex_[2] = 5;
}

void Money::Update()
{
	MoneySeatUpdate();
	MoneyStringUpdate();
}
void Money::MoneyStringUpdate()
{
	size_t _Temp = PlayerMoney_;

	for (int i = 0; i < Index_ +1; i++)//앞에서 부터 검사
	{
		MoneyIndex_[i] = _Temp % 10;
		_Temp /= 10;
	}

	for (int i = 0; i < Index_+1; i++)
	{
		MoneyList_[i]->SetIndex(MoneyIndex_[i]);
	}

}
void Money::MoneySeatUpdate()
{
	Index_ = 0;

	for (int i = 7; i > 0; i--)//앞에서 부터 검사
	{
		if (MoneyIndex_[i] != 0)
		{
			Index_ = i;

		}
	}
	for (int i = Index_ + 1; i < 8; i++)
	{
		MoneyList_[i]->Off();
	}
	for (int i = 0; i < Index_ + 1; i++)
	{
		MoneyList_[i]->On();
	}
}