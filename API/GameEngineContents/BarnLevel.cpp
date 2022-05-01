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
	Back->GetRenderer()->SetImage("MineEntry.bmp");
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


	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void BarnLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
}

void BarnLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel->GetNameCopy() == "Town2Level")
	{
		Player::MainPlayer->SetPosition({ 1176.0f,800 });
	}
	else
	{
		Player::MainPlayer->SetPosition({ 1412.0f,565.0f });
	}

	Player::MainPlayer->SetMapScale(3200.0f, 1280.0f);
	Player::MainPlayer->SetColMapName("MineEntryColMap.bmp");
	Player::MainPlayer->SetSideLevel("Town2Level", "Mine1Level", " ");
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
