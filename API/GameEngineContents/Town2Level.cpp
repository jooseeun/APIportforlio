#include "Town2Level.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include "ContentsEnums.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

Town2Level::Town2Level() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

Town2Level::~Town2Level() 
{
}

void Town2Level::Loading()
{
	Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Town2.bmp");
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

	}
}

void Town2Level::Update()
{
	GetItemPos();
	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();

	if (CurSelectPivot_ != NextSelectPivot_)
	{
		Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;;
}
void Town2Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetPosition({ 1006.0f,2380.f });
	Player::MainPlayer->SetMapScale(5448.0f, 2620.0f);
	Player::MainPlayer->SetColMapName("Town2ColMap.bmp");
	Player::MainPlayer->SetSideLevel("TownLevel", "MineEntryLevel", "LobinHouseLevel");
}

void Town2Level::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();
		EnergyUI::EnergyUISet->NextLevelOn();
		Tool::ToolSet->NextLevelOn();

	}
}
