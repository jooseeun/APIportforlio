#include "ShopUIMoney.h"
#include "ContentsEnums.h"
#include "Money.h"
#include <GameEngine/GameEngineRenderer.h>


ShopUIMoney::ShopUIMoney()
	:PlayerShopUIMoney_(0),
	Index_(0)
{
}

ShopUIMoney::~ShopUIMoney()
{
}

void ShopUIMoney::Start()
{ //숫자는 8자리
	SetPosition({ 333,493 });
	for (int i = 0; i < 8; i++)
	{
		ShopUIMoneyIndex_[i] = 0;
		ShopUIMoneyList_[i] = CreateRenderer("Money.bmp", static_cast<int>(ORDER::FRONTUI));
		ShopUIMoneyList_[i]->SetIndex(ShopUIMoneyIndex_[i]);
		ShopUIMoneyList_[i]->SetPivot({ -24 * static_cast<float>(i),0 });
		ShopUIMoneyList_[i]->CameraEffectOff();
	}
	PlayerShopUIMoney_ = Money::MoneySet->GetMoney();
}

void ShopUIMoney::Update()
{
	PlayerShopUIMoney_ = Money::MoneySet->GetMoney();
	ShopUIMoneyStringUpdate();
	ShopUIMoneySeatUpdate();
		

}
void ShopUIMoney::ShopUIMoneyStringUpdate()
{
	size_t _Temp = PlayerShopUIMoney_;
	for (int i = 0; i < 8; i++)
	{
		ShopUIMoneyIndex_[i] = 0;
	}

	for (int i = 0; _Temp >= 1; i++)//앞에서 부터 검사
	{
		ShopUIMoneyIndex_[i] = _Temp % 10;

		_Temp /= 10;
	}

	for (int i = 0; i < Index_ + 1; i++)
	{
		ShopUIMoneyList_[i]->SetIndex(ShopUIMoneyIndex_[i]);
	}

}
void ShopUIMoney::ShopUIMoneySeatUpdate()
{
	Index_ = 0;

	for (int i = 7; i > 0; i--)//앞에서 부터 검사
	{
		if (ShopUIMoneyIndex_[i] != 0)
		{
			Index_ = i;
			i = 0;

		}
	}
	for (int i = Index_ + 1; i < 8; i++)
	{
		ShopUIMoneyList_[i]->Off();
	}
	for (int i = 0; i < Index_ + 1; i++)
	{
		ShopUIMoneyList_[i]->On();
	}
}