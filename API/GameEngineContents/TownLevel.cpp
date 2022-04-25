#include "TownLevel.h"
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
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

TownLevel::TownLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

TownLevel::~TownLevel() 
{
}

void TownLevel::Loading()
{
	Back = CreateActor<BackGround>(static_cast<int>(ORDER::BACKGROUND));
	Back->GetRenderer()->SetImage("Town.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());
	//
	FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));
	Front_->GetRenderer()->SetImage("TownFront.bmp");
	float4 FrontImageScale = Front_->GetRenderer()->GetImage()->GetScale();
	Front_->GetRenderer()->SetPivot(FrontImageScale.Half());
	
	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
		ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::TOOLUI, "ToolUI");
		TopUI::TopUISet = CreateActor<TopUI>((int)ORDER::UI, "TopUI");
		EnergyUI::EnergyUISet = CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
		Tool::ToolSet = CreateActor<Tool>(static_cast<int>(ORDER::ITEM), "Tool");
		Time::TimeSet = CreateActor<Time>(static_cast<int>(ORDER::UI), "Time");

	}
}

void TownLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
}
void TownLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel->GetNameCopy() == "BusStopLevel")
	{
		Player::MainPlayer->SetPosition({ 144.0f,3442.f });
	}
	if (_PrevLevel->GetNameCopy() == "SeedShopLevel")
	{
		Player::MainPlayer->SetPosition({ 2810.0f,3720.f });
	}
	if (_PrevLevel->GetNameCopy() == "Town2Level")
	{
		Player::MainPlayer->SetPosition({ 5216.0f,269.f });
	}
	Player::MainPlayer->SetPosition({ 144.0f,3442.f });
	Player::MainPlayer->SetMapScale(5544.0f, 6200.0f);
	Player::MainPlayer->SetColMapName("TownColMap.bmp");
	Player::MainPlayer->SetSideLevel("BusStopLevel", "Town2Level", "SeedShopLevel");
}

void TownLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();
		EnergyUI::EnergyUISet->NextLevelOn();
		Tool::ToolSet->NextLevelOn();
		Time::TimeSet->NextLevelOn();

	}
}
