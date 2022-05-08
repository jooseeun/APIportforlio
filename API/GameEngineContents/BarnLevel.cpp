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
	float4 Pos_ = { 370,460 };

	Cow_[0] = CreateActor<Cow>(static_cast<int>(ORDER::PLAYER), "Cow");
	Cow_[0]->SetPosition(Pos_);
	Cow_[0]->SetCurDir(AnimalDir::Right);
	Cow_[0]->Off();

	Pos_ = { 900,315 };
	Cow_[1] = CreateActor<Cow>(static_cast<int>(ORDER::PLAYER), "Cow");
	Cow_[1]->SetPosition(Pos_);
	Cow_[1]->SetCurDir(AnimalDir::Left);
	Cow_[1]->Off();

	Pos_ = { 750,500 };
	Cow_[2] = CreateActor<Cow>(static_cast<int>(ORDER::PLAYER), "Cow");
	Cow_[2]->SetPosition(Pos_);
	Cow_[2]->SetCurDir(AnimalDir::Front);
	Cow_[2]->Off();

	Pos_ = { 500,600 };
	Cow_[3] = CreateActor<Cow>(static_cast<int>(ORDER::PLAYER), "Cow");
	Cow_[3]->SetPosition(Pos_);
	Cow_[3]->SetCurDir(AnimalDir::Back);
	Cow_[3]->Off();

	YSortOn(static_cast<int>(ORDER::PLAYER));
}
void BarnLevel::CreateAnimal()
{
	if (0 != AnimalShopUI::AnimalShopUISet->CowNum_)
	{
		for (int i = 0; i < AnimalShopUI::AnimalShopUISet->CowNum_; i++)
		{
			Cow_[i]->On();
			Cow_[i]->SetFirstDay();
		}
		AnimalShopUI::AnimalShopUISet->CowNum_ = 0;
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
