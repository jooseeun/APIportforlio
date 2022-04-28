#include "BusStopLevel.h"
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
#include "FadeIn.h"
#include "Money.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

BusStopLevel::BusStopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

BusStopLevel::~BusStopLevel() 
{
}

void BusStopLevel::Loading()
{
	{
		BackGround* Back = CreateActor<BackGround>(1);
		Back->GetRenderer()->SetImage("BusStop.bmp");
		float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
		Back->GetRenderer()->SetPivot(BackImageScale.Half());
		Back->GroundTileMap_.TileRangeSetting(35, 30, { 48,48 });
		Back->CropsTileMap_.TileRangeSetting(35, 30, { 48,48 });

		FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));
	}

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
void BusStopLevel::Update()
{

	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
}

void BusStopLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel->GetNameCopy() == "FarmLevel")
	{
		Player::MainPlayer->SetPosition({ 100.0f,1516.f });
	}
	else if (_PrevLevel->GetNameCopy() == "TownLevel")
	{
		Player::MainPlayer->SetPosition({ 2100.0f,1516.f });
	}
	Player::MainPlayer->SetMapScale(2240.0f, 1920.0f);
	Player::MainPlayer->SetColMapName("BusStopColMap.bmp");
	Player::MainPlayer->SetSideLevel("FarmLevel", "TownLevel", " ");

	FadeIn* FadeInSet = CreateActor<FadeIn>(static_cast<int>(ORDER::FADE), "FADE");


}

void BusStopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
