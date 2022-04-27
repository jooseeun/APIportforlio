#include "SeedShopUI.h"
#include "ContentsEnums.h"
#include "ShopUIMoney.h"

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
	ShopUI_->SetPivot({ 0,-110 });
	Exit_ = CreateRenderer("Exit.bmp", static_cast<int>(ORDER::FRONTUI),RenderPivot::CENTER, { 580,-330 });
	ExitCol_ = CreateCollision("ShopExit", { 44,44 }, { 580,-320 });
	MoneyUI_ = CreateRenderer("MoneyUI.bmp", static_cast<int>(ORDER::FRONTUI));
	MoneyUI_->SetPivot({ -395,128 });
	InvenUI_ = CreateRenderer("ShopInven.bmp", static_cast<int>(ORDER::FRONTUI));
	InvenUI_->SetPivot({ 150,230 });
	ShopScroll_ = CreateRenderer("ShopScroll.bmp", static_cast<int>(ORDER::FRONTUI));
	ShopScroll_->SetPivot({ 530, -110 });
	ScroppButton_ = CreateRenderer("ShopScrollButton.bmp", static_cast<int>(ORDER::FRONTUI));
	ScroppButton_->SetPivot({ 530,-110 });
	

	FadeIn_->CameraEffectOff();
	ShopUI_->CameraEffectOff();
	Exit_->CameraEffectOff();
	ExitCol_->CameraEffectOff();
	MoneyUI_->CameraEffectOff();
	ExitCol_->CameraEffectOff();
	InvenUI_->CameraEffectOff();
	ShopScroll_->CameraEffectOff();
	ScroppButton_->CameraEffectOff();
	
}

void SeedShopUI::Update()
{

}