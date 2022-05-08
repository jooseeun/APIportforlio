#include "RobinShopLevel.h"
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
#include "NPCRobin.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

RobinShopLevel::RobinShopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1),
	IsOpenShop_(false)
{
}

RobinShopLevel::~RobinShopLevel()
{
}


void RobinShopLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("RobinShop.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());
	FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));

	MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");
	NPCRobin* NPC = CreateActor<NPCRobin>(static_cast<int>(ORDER::PLAYER), "Robin");
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
	ShopUI_ = CreateActor<RobinShopUI>(static_cast<int>(ORDER::FRONTUI), "RobinShopUI");
	ShopUI_->Off();

	YSortOn(static_cast<int>(ORDER::PLAYER));
}

void RobinShopLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;

	CheckOpenRobinShop_();
	if (IsOpenShop_ == true)
	{
		ShopUI_->On();
		ToolUI::ToolUISet->Off();
		Tool::ToolSet->Off();
	}
	else if (IsOpenShop_ == false)
	{
		ShopUI_->Off();
		ToolUI::ToolUISet->On();
		Tool::ToolSet->On();
	}
}

void RobinShopLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	sound = GameEngineSound::SoundPlayControl("doorClose.wav");
	sound.Volume(0.7);
	Player::MainPlayer->SetPosition({ 415.0f,1485.0f});
	Player::MainPlayer->SetMapScale(2048.0f, 1600.0f);
	Player::MainPlayer->SetColMapName("RobinShopColMap.bmp");
	Player::MainPlayer->SetSideLevel("", "Town2Level", " ");
}

void RobinShopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
