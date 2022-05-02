#include "AnimalShopUI.h"
#include "ContentsEnums.h"
#include "ShopUIMoney.h"
#include "Tool.h"
#include "Money.h"
#include "Barn.h"
#include "Coop.h"
#include "Tool.h"
#include "FadeIn.h"
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineCollision.h"
AnimalShopUI::AnimalShopUI() 
{
}

AnimalShopUI::~AnimalShopUI() 
{
}

void AnimalShopUI::Start()
{
	SetPosition({ 640,300 });

	GameEngineRenderer* ShopUI_ = CreateRenderer("AnimalShopUI.bmp", static_cast<int>(ORDER::FRONTUI));
	ChickenName_ = CreateRenderer("ChickenNameUI.bmp", static_cast<int>(ORDER::FRONTUI));
	ChickenMoney_ = CreateRenderer("ChickenMoneyUI.bmp", static_cast<int>(ORDER::FRONTUI));
	CowName_ = CreateRenderer("CowNameUI.bmp", static_cast<int>(ORDER::FRONTUI));
	CowMoney_ = CreateRenderer("CowMoneyUI.bmp", static_cast<int>(ORDER::FRONTUI));

	GameEngineCollision* ExitButoon = CreateCollision("AnimalShopExit", { 48,48 }, { 128,128 });

	ChickenName_->SetPivot({ 0,260 });
	ChickenMoney_->SetPivot({ 0,350 });
	CowName_->SetPivot({ 0,260 });
	CowMoney_->SetPivot({ 0,350 });

	Chicken_ = CreateCollision("BuyChicken", { 80,64 }, { -200,-58 });
	Cow_ = CreateCollision("BuyCow", { 64,64 }, { -62,-58 });

	ShopUI_->CameraEffectOff();
	Chicken_->CameraEffectOff();
	Cow_->CameraEffectOff();
	ChickenName_->CameraEffectOff();
	ChickenMoney_->CameraEffectOff();
	CowName_->CameraEffectOff();
	CowMoney_->CameraEffectOff();
	ExitButoon->CameraEffectOff();
	ChickenName_->Off();
	ChickenMoney_->Off();
	CowName_->Off();
	CowMoney_->Off();

}
void AnimalShopUI::CheckMouse()
{
	if (Chicken_->CollisionCheck("MouseCol"))
	{
		ChickenName_->On();
		ChickenMoney_->On();
		CowName_->Off();
		CowMoney_->Off();
	}
	else if(Cow_->CollisionCheck("MouseCol"))
	{
		ChickenName_->Off();
		ChickenMoney_->Off();
		CowName_->On();
		CowMoney_->On();
	}
	else
	{
		ChickenName_->Off();
		ChickenMoney_->Off();
		CowName_->Off();
		CowMoney_->Off();
	}
}
void AnimalShopUI::Update()
{
	CheckMouse();
}