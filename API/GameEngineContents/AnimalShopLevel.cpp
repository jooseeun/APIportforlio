#include "AnimalShopLevel.h"
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
#include "AnimalShopNPC.h"
#include "AnimalShopUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

AnimalShopLevel::AnimalShopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1),
	IsOpenShop_(false),
	MouseSet(nullptr),
	Back(nullptr)
{
	for (int _Num = 0; _Num < 13; _Num++)
	{
		ItemPos_[_Num] = PlayerItem::Max;
	}
}

AnimalShopLevel::~AnimalShopLevel()
{
}


void AnimalShopLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("AnimalShop.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());
	FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));

	MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");
	if (nullptr == AnimalShopUI::AnimalShopUISet)
	{
		AnimalShopUI::AnimalShopUISet= CreateActor<AnimalShopUI>(static_cast<int>(ORDER::FRONTUI), "AnimalShopUI");
	}
	AnimalShopNPC* NPC = CreateActor<AnimalShopNPC>(static_cast<int>(ORDER::PLAYER), "Marnie");
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

	AnimalShopUI::AnimalShopUISet->Off();

	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void AnimalShopLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;

	CheckOpenAnimalShop_();
	if (IsOpenShop_ == true)
	{
		AnimalShopUI::AnimalShopUISet->On();
		ToolUI::ToolUISet->Off();
		Tool::ToolSet->Off();
	}
	else if (IsOpenShop_ == false)
	{
		AnimalShopUI::AnimalShopUISet->Off();
		ToolUI::ToolUISet->On();
		Tool::ToolSet->On();
	}
}

void AnimalShopLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	sound = GameEngineSound::SoundPlayControl("doorClose.wav");
	sound.Volume(0.7f);
	Player::MainPlayer->SetPosition({ 864.0f,1180.0f});
	Player::MainPlayer->SetMapScale(2240.0f, 1280.0f);
	Player::MainPlayer->SetColMapName("AnimalShopColMap.bmp");
	Player::MainPlayer->SetSideLevel("", "ForestLevel", " ");
}

void AnimalShopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
