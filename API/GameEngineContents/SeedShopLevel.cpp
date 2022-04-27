#include "SeedShopLevel.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include "ContentsEnums.h"
#include "Mouse.h"
#include "Time.h"
#include "FrontMap.h"
#include "ShopNPC.h"
#include "FadeIn.h"
#include "Money.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

SeedShopLevel::SeedShopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1),
	IsOpenShop_(false)
{
}

SeedShopLevel::~SeedShopLevel() 
{
}

void SeedShopLevel::Loading()
{
		BackGround* Back = CreateActor<BackGround>(1);
		Back->GetRenderer()->SetImage("SeedShop.bmp");
		float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
		Back->GetRenderer()->SetPivot(BackImageScale.Half());

		Back->GroundTileMap_.TileRangeSetting(48, 32, { 48,48 });
		Back->CropsTileMap_.TileRangeSetting(48, 32, { 48,48 });

		FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));
		Front_->GetRenderer()->SetImage("SeedShopFront.bmp");
		float4 FrontImageScale = Front_->GetRenderer()->GetImage()->GetScale();
		Front_->GetRenderer()->SetPivot(FrontImageScale.Half());



		MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");
		ShopNPC* NPC_= CreateActor<ShopNPC>(static_cast<int>(ORDER::PLAYER), "SeedShopOnner");
		NPC_->SetPosition({ 256.0f,1090.f });

		ShopUI_ = CreateActor<SeedShopUI>(static_cast<int>(ORDER::FRONTUI), "SeedShopUI");
		ShopUI_->Off();
		ShopMoney_ = CreateActor<ShopUIMoney>(static_cast<int>(ORDER::FRONTUI), "ShopMoney");
		ShopMoney_->Off();
		if (nullptr == Player::MainPlayer)
		{
			Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
			ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::TOOLUI, "ToolUI");
			TopUI::TopUISet = CreateActor<TopUI>((int)ORDER::UI, "TopUI");
			EnergyUI::EnergyUISet = CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
			Tool::ToolSet = CreateActor<Tool>(static_cast<int>(ORDER::ITEM), "Tool");
			Time::TimeSet = CreateActor<Time>(static_cast<int>(ORDER::UI), "Time");
			Money::MoneySet = CreateActor<Money>(static_cast<int>(ORDER::UIFONT), "Money");
		}

		
}


void SeedShopLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
	CheckOpenShop_();
	if (IsOpenShop_ == true)
	{
		ShopUI_->On();
		ShopMoney_->On();
	}
	else if (IsOpenShop_ == false)
	{
		ShopUI_->Off();
		ShopMoney_->Off();
	}
}

void SeedShopLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	Player::MainPlayer->SetPosition({ 414.0f,1770.f });
	Player::MainPlayer->SetMapScale(3072.0f, 2048.0f);
	Player::MainPlayer->SetColMapName("SeedShopColMap.bmp");
	Player::MainPlayer->SetSideLevel(" ", "TownLevel", " ");
	Player::MainPlayer->SetGroundTileMap(nullptr);
	Player::MainPlayer->SetCropsTileMap(nullptr);

	FadeIn* FadeInSet = CreateActor<FadeIn>(static_cast<int>(ORDER::FADE), "FADE");
}

void SeedShopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();
		EnergyUI::EnergyUISet->NextLevelOn();
		Tool::ToolSet->NextLevelOn();
		Time::TimeSet->NextLevelOn();
		Money::MoneySet->NextLevelOn();

	}
}
