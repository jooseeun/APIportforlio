#include "SeedShopUI.h"
#include "ContentsEnums.h"
#include "ShopUIMoney.h"
#include <GameEngineBase/GameEngineInput.h>

SeedShopUI::SeedShopUI() :
	IsShopOpen_(false),
	Page_(1)
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
	ScroppButton_->SetPivot({ 530,-252 });
	

	ParsnipSeed_ = CreateRenderer("ParsnipSeed.bmp", static_cast<int>(ORDER::ITEM));
	ParsnipSeed_->SetPivot({ 0,-252 });

	PhotatoSeed_ = CreateRenderer("PhotatoSeed.bmp", static_cast<int>(ORDER::ITEM));
	PhotatoSeed_->SetPivot({ 0,-157 });

	CauliFlowerSeed_ = CreateRenderer("CauliFlowerSeed.bmp", static_cast<int>(ORDER::ITEM));
	CauliFlowerSeed_->SetPivot({ 0,-62 });

	BeanSeed_ = CreateRenderer("BeanSeed.bmp", static_cast<int>(ORDER::ITEM));
	BeanSeed_->SetPivot({ 0,34 });

	KaleSeed_ = CreateRenderer("KaleSeed.bmp", static_cast<int>(ORDER::ITEM));
	KaleSeed_->SetPivot({ 0,-252 });

	BlueberrieSeed_ = CreateRenderer("BlueberrieSeed.bmp", static_cast<int>(ORDER::ITEM));
	BlueberrieSeed_->SetPivot({ 0,-157 });

	MelonSeed_ = CreateRenderer("MelonSeed.bmp", static_cast<int>(ORDER::ITEM));
	MelonSeed_->SetPivot({ 0,-62 });

	PepperSeed_ = CreateRenderer("PepperSeed.bmp", static_cast<int>(ORDER::ITEM));
	PepperSeed_->SetPivot({ 0,34 });

	FadeIn_->CameraEffectOff();
	ShopUI_->CameraEffectOff();
	Exit_->CameraEffectOff();
	ExitCol_->CameraEffectOff();
	MoneyUI_->CameraEffectOff();
	ExitCol_->CameraEffectOff();
	InvenUI_->CameraEffectOff();
	ShopScroll_->CameraEffectOff();
	ScroppButton_->CameraEffectOff();
	ParsnipSeed_->CameraEffectOff();
	PhotatoSeed_->CameraEffectOff();
	CauliFlowerSeed_->CameraEffectOff();
	BeanSeed_->CameraEffectOff();
	KaleSeed_->CameraEffectOff();
	BlueberrieSeed_->CameraEffectOff();
	MelonSeed_->CameraEffectOff();
	PepperSeed_->CameraEffectOff();
}
void SeedShopUI::CheckPage()
{

	if (GameEngineInput::GetInst()->GetMouseWheel() > 100)
	{
		Page_ = 1;
		ScroppButton_->SetPivot({ 530,-252 });
	}
	else if (GameEngineInput::GetInst()->GetMouseWheel() < -100)
	{
		Page_ = 2;
		ScroppButton_->SetPivot({ 530,30 });
	}
}
void SeedShopUI::Update()
{
	CheckPage();
	if (Page_ == 1)
	{
		ParsnipSeed_->On();
		PhotatoSeed_->On();
		CauliFlowerSeed_->On();
		BeanSeed_->On();

		KaleSeed_->Off();
		BlueberrieSeed_->Off();
		MelonSeed_->Off();
		PepperSeed_->Off();
	}
	if (Page_ == 2)
	{
		ParsnipSeed_->Off();
		PhotatoSeed_->Off();
		CauliFlowerSeed_->Off();
		BeanSeed_->Off();

		KaleSeed_->On();
		BlueberrieSeed_->On();
		MelonSeed_->On();
		PepperSeed_->On();
	}
}