#include "BarnLevel.h"
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
#include "Money.h"
#include "AnimalShopUI.h"
#include "Cow.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

BarnLevel::BarnLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

BarnLevel::~BarnLevel()
{
}


void BarnLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("BarnLevel.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());
	FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));

	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

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
	GameEngineRandom Ran_;
	float4 Pos_;
	Pos_.x = Ran_.RandomFloat(360, 852);
	Pos_.y = Ran_.RandomFloat(293, 461);
	Cow* Cow_ = CreateActor<Cow>(static_cast<int>(ORDER::PLAYER), "Cow");
	Cow_->SetPosition(Pos_);

	YSortOn(static_cast<int>(ORDER::PLAYER));
}
void BarnLevel::CreateAnimal()
{
	if (0 != AnimalShopUI::AnimalShopUISet->ChickenNum_)
	{
		for (int i = 0; i < AnimalShopUI::AnimalShopUISet->ChickenNum_; i++)
		{
			GameEngineRandom Ran_;
			float4 Pos_;
			Pos_.x = Ran_.RandomFloat(360, 852);
			Pos_.y = Ran_.RandomFloat(293, 461);
			Cow* Cow_ = CreateActor<Cow>(static_cast<int>(ORDER::PLAYER), "Cow");
			Cow_->SetPosition(Pos_);
		}
		AnimalShopUI::AnimalShopUISet->ChickenNum_ = 0;
	}
}
void BarnLevel::Update()
{
	GetItemPos();
	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();
	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	CurSelectPivot_ = NextSelectPivot_;
	CreateAnimal();
}

void BarnLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	Player::MainPlayer->SetPosition({ 797.0f,843.0f});


	Player::MainPlayer->SetMapScale(1280.0f, 960.0f);
	Player::MainPlayer->SetColMapName("BarnColMap.bmp");
	Player::MainPlayer->SetSideLevel("", "FarmLevel", " ");
}

void BarnLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
