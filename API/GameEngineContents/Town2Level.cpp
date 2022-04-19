#include "Town2Level.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Ax.h"
#include "Hoe.h"
#include "Pick.h"
#include "Sickle.h"
#include "Player.h"
#include "ToolUI.h"
#include "PhotatoSeed.h"
#include "ContentsEnums.h"
#include "WateringCan.h"
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


	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
		ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
		TopUI::TopUISet = CreateActor<TopUI>((int)ORDER::UI, "TopUI");
		EnergyUI::EnergyUISet = CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
		Hoe::HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
		Ax::AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
		Pick::PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
		Sickle::SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
		WateringCan::WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");
		PhotatoSeed::PhotatoSeedSet = CreateActor<PhotatoSeed>((int)ORDER::ITEM, "PhotatoSeed");
	}
}

void Town2Level::Update()
{
	GetItemPos<Ax>(Ax::AxSet);
	GetItemPos<Pick>(Pick::PickSet);
	GetItemPos<Hoe>(Hoe::HoeSet);
	GetItemPos<Sickle>(Sickle::SickleSet);
	GetItemPos<WateringCan>(WateringCan::WateringCanSet);
	GetItemPos<PhotatoSeed>(PhotatoSeed::PhotatoSeedSet);

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
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();
		Hoe::HoeSet->NextLevelOn();
		Ax::AxSet->NextLevelOn();
		Pick::PickSet->NextLevelOn();
		Sickle::SickleSet->NextLevelOn();
		WateringCan::WateringCanSet->NextLevelOn();
		PhotatoSeed::PhotatoSeedSet->NextLevelOn();
	}
}
