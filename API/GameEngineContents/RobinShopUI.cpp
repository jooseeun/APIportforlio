#include "RobinShopUI.h"
#include "ContentsEnums.h"
#include "ShopUIMoney.h"
#include "Tool.h"
#include "Money.h"
#include "Barn.h"
#include "Coop.h"
#include <GameEngineBase/GameEngineInput.h>

RobinShopUI::RobinShopUI() :
	IsShopOpen_(false),
	Page_(1)
{
}

RobinShopUI::~RobinShopUI()
{

}

void RobinShopUI::Start()
{
	SetPosition({ 640,360 });
	FadeIn_ = CreateRenderer("FadeIn.bmp", static_cast<int>(ORDER::FRONTUI));
	FadeIn_->SetAlpha(150);

	Page1_ = CreateRenderer("RobinShop1.bmp",static_cast<int>(ORDER::FRONTUI));
	Page2_ = CreateRenderer("RobinShop2.bmp", static_cast<int>(ORDER::FRONTUI));
	ExitCol_ = CreateCollision("RobinShopExit", { 44,44 }, { 512,-260 });

	RightButton_ = CreateRenderer("RightButton.bmp", static_cast<int>(ORDER::FRONTUI));
	LeftButton_ = CreateRenderer("LeftButton.bmp", static_cast<int>(ORDER::FRONTUI));
	RightButton_->SetPivot({-180,320});
	LeftButton_->SetPivot({ -380,320 });

	RightCol_=CreateCollision("RobinShopRightButton", { 44,30 }, { -180,320 });
	LeftCol_ = CreateCollision("RobinShopLeftButton", { 44,30 }, { -380,320 });

	CreateButton_= CreateRenderer("CreateButton.bmp", static_cast<int>(ORDER::FRONTUI));
	CreateButton_->SetPivot({ 470,320 });
	CreateCol_= CreateCollision("CreateButton", { 44,30 }, { 470,320 });
	FadeIn_->CameraEffectOff();
	Page1_->CameraEffectOff();
	Page2_->CameraEffectOff();
	ExitCol_->CameraEffectOff();
	LeftButton_->CameraEffectOff();
	RightButton_->CameraEffectOff();
	RightCol_->CameraEffectOff();
	LeftCol_->CameraEffectOff();
	CreateButton_->CameraEffectOff();
	CreateCol_->CameraEffectOff();

	Page1_->Off();
	Page2_->Off();
}
void RobinShopUI::Create()
{
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		if (CreateCol_->CollisionCheck("MouseCol"))
		{
			if (Page_ == 1)
			{
				size_t LeftMoney_ = Money::MoneySet->GetMoney() - 400;
				if (LeftMoney_ < 0)
				{
					return;
				}
				Money::MoneySet->SetMoney(LeftMoney_);
				Coop::MainCoop->On();
			}
			else if (Page_ == 2)
			{
				size_t LeftMoney_ = Money::MoneySet->GetMoney() - 600;
				if (LeftMoney_ < 0)
				{
					return;
				}
				Money::MoneySet->SetMoney(LeftMoney_);
				Barn::MainBarn->On();
			}
		}
		
	}
	
}

void RobinShopUI::CheckPage()
{
	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		if (RightCol_->CollisionCheck("MouseCol"))
		{
			Page_ = 2;
		}
		else if (LeftCol_->CollisionCheck("MouseCol"))
		{
			Page_ = 1;
		}
	}
}

void RobinShopUI::Update()
{
	Create();
	CheckPage();
	if (Page_ == 1)
	{
		Page1_->On();
		Page2_->Off();
	}
	else if (Page_ == 2)
	{
		Page1_->Off();
		Page2_->On();
	}
}