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
	SetPosition({ 640,320 });
	FadeIn_ = CreateRenderer("FadeIn.bmp", static_cast<int>(ORDER::TOOLUI));
	FadeIn_->SetAlpha(80);
	ShopUI_ = CreateRenderer("ShopUI.bmp", static_cast<int>(ORDER::TOOLUI));
	Exit_ = CreateRenderer("Exit.bmp", static_cast<int>(ORDER::TOOLUI),RenderPivot::CENTER, {500,-200});
	ExitCol_ = CreateCollision("ShopExit", { 44,44 }, { 500,-200 });
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