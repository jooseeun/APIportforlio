#include "BackWoodLevel.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include "ContentsEnums.h"
#include "Money.h"
#include "Time.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

BackWoodLevel::BackWoodLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

BackWoodLevel::~BackWoodLevel()
{
}

void BackWoodLevel::Loading()
{
	Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("BackWood.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());

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
}

void BackWoodLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
}
void BackWoodLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel->GetNameCopy() == "FarmLevel")
	{
		Player::MainPlayer->SetPosition({ 919.0f,2300.0f});
	}
	else if (_PrevLevel->GetNameCopy() == "Town2Level")
	{
		Player::MainPlayer->SetPosition({ 2981.0f,897.0f});
	}
	Player::MainPlayer->SetMapScale(3200.0f, 2560.0f);
	Player::MainPlayer->SetColMapName("BackWoodColMap.bmp");
	Player::MainPlayer->SetSideLevel("FarmLevel", "Town2Level", "");
}

void BackWoodLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
