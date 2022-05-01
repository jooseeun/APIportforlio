#include "RobinShopUI.h"
#include "ContentsEnums.h"
#include "ShopUIMoney.h"
#include "Tool.h"
#include "Money.h"
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

	FadeIn_->CameraEffectOff();
	Page1_->CameraEffectOff();
	Page2_->CameraEffectOff();
	ExitCol_->CameraEffectOff();

	Page1_->Off();
	Page2_->Off();
	ExitCol_->Off();
}
void RobinShopUI::BuyCoop()
{
	
}

void RobinShopUI::CheckPage()
{
	if (Page_ == 1)
	{
		Page1_->On();
		Page2_->Off();
		ExitCol_->On();
	}
	else if (Page_ == 2)
	{
		Page1_->Off();
		Page2_->On();
		ExitCol_->Off();
	}
}

void RobinShopUI::Update()
{
	BuyCoop();
	CheckPage();

}