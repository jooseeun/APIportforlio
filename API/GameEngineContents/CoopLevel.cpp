#include "CoopLevel.h"
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
#include "Chicken.h"
#include "AnimalShopUI.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

CoopLevel::CoopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1),
	Back(nullptr)
{
	for (int _Num = 0; _Num < 13; _Num++)
	{
		ItemPos_[_Num] = PlayerItem::Max;
	}
	for (int _Num = 0; _Num < 4; _Num++)
	{
		Chicken_[_Num] = nullptr;
	}
}

CoopLevel::~CoopLevel()
{
}


void CoopLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("CoopLevel.bmp");
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

	float4 Pos_ = { 370,350 };
	Chicken_[0] = CreateActor<Chicken>(static_cast<int>(ORDER::PLAYER), "Chicken");
	Chicken_[0]->SetPosition(Pos_);
	Chicken_[0]->SetCurDir(AnimalDir::Right);
	Chicken_[0]->Off();

	Pos_ = { 800,440 };
	Chicken_[1] = CreateActor<Chicken>(static_cast<int>(ORDER::PLAYER), "Chicken");
	Chicken_[1]->SetPosition(Pos_);
	Chicken_[1]->SetCurDir(AnimalDir::Left);
	Chicken_[1]->Off();

	Pos_ = { 450,290 };
	Chicken_[2] = CreateActor<Chicken>(static_cast<int>(ORDER::PLAYER), "Chicken");
	Chicken_[2]->SetPosition(Pos_);
	Chicken_[2]->SetCurDir(AnimalDir::Front);
	Chicken_[2]->Off();

	Pos_ = { 500,380 };
	Chicken_[3] = CreateActor<Chicken>(static_cast<int>(ORDER::PLAYER), "Chicken");
	Chicken_[3]->SetPosition(Pos_);
	Chicken_[3]->SetCurDir(AnimalDir::Back);
	Chicken_[3]->Off();

	YSortOn(static_cast<int>(ORDER::PLAYER));
}
void CoopLevel::CreateAnimal()
{
	if (0 != AnimalShopUI::AnimalShopUISet->ChickenNum_)
	{
		for(int i = 0 ; i < AnimalShopUI::AnimalShopUISet->ChickenNum_;i++)
		{
			Chicken_[i]->On();
			Chicken_[i]->SetFirstDay();
		}
			AnimalShopUI::AnimalShopUISet->ChickenNum_ = 0;
	}
}
void CoopLevel::Update()
{
	GetItemPos();
	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();
	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	CurSelectPivot_ = NextSelectPivot_;
	CreateAnimal();
}

void CoopLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Sound_ = GameEngineSound::SoundPlayControl("doorClose.wav");
	Sound_.Volume(0.7f);
	Player::MainPlayer->SetPosition({ 416.0f, 500.0f});
	Player::MainPlayer->SetMapScale(1280.0f, 720.0f);
	Player::MainPlayer->SetColMapName("CoopColMap.bmp");
	Player::MainPlayer->SetSideLevel("", "FarmLevel", " ");
}

void CoopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
