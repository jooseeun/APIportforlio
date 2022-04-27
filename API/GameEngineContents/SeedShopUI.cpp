#include "SeedShopUI.h"
#include "ContentsEnums.h"


SeedShopUI::SeedShopUI():
	IsShopOpen_(false)
{
}

SeedShopUI::~SeedShopUI() 
{
}

void SeedShopUI::Start()
{
	SetPosition({ 640,360 });
	FadeIn_ = CreateRenderer("FadeIn.bmp", static_cast<int>(ORDER::FRONTUI));
	FadeIn_->SetAlpha(150);
	ShopUI_ = CreateRenderer("ShopUI.bmp", static_cast<int>(ORDER::FRONTUI));
	ShopUI_->SetPivot({ 0,-90 });
	Exit_ = CreateRenderer("Exit.bmp", static_cast<int>(ORDER::FRONTUI),RenderPivot::CENTER, { 580,-320 });
	ExitCol_ = CreateCollision("ShopExit", { 44,44 }, { 580,-320 });

	FadeIn_->CameraEffectOff();
	ShopUI_->CameraEffectOff();
	Exit_->CameraEffectOff();
	ExitCol_->CameraEffectOff();
}

void SeedShopUI::Update()
{
	if (IsShopOpen_ = false)
	{
		FadeIn_->Off();
		ShopUI_->Off();
		Exit_->Off();
		ExitCol_->Off();
	}
	else
	{
		FadeIn_->On();
		ShopUI_->On();
		Exit_->On();
		ExitCol_->On();
	}
}