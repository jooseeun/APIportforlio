#include "FarmHouseLevel.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include "ContentsEnums.h"
#include "Mouse.h"
#include "Tool.h"
#include "FrontMap.h"
#include "Time.h"
#include "FadeIn.h"
#include "ShopNPC.h"
#include "Money.h"
#include "PlayHelpBar.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

FarmHouseLevel::FarmHouseLevel() :
	CurSelectPivot_(0),
	NextSelectPivot_(1),
	Back(nullptr)
{
	for (int _Num = 0; _Num < 13; _Num++)
	{
		ItemPos_[_Num] = PlayerItem::Max;
	}
}

FarmHouseLevel::~FarmHouseLevel() 
{
}

void FarmHouseLevel::Loading()
{


	Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("FarmHouse.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());

	Back->GroundTileMap_.TileRangeSetting(26, 15, { 48,48 });
	Back->CropsTileMap_.TileRangeSetting(26, 15, { 48,48 });
	
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

void FarmHouseLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("CheckTest"))
	{
		GameEngine::GetInst().ChangeLevel("Mine1Level");
	}
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();
	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;

}

void FarmHouseLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


	if (_PrevLevel->GetNameCopy() == "FarmLevel")
	{
		Player::MainPlayer->SetPosition({ 474.0f,659 });
		sound = GameEngineSound::SoundPlayControl("doorClose.wav");
		sound.Volume(0.7f);

	}
	else
	{
		Player::MainPlayer->SetPosition({ 750.0f,520.f });
		PlayHelpBar* Front_ = CreateActor<PlayHelpBar>(static_cast<int>(ORDER::FRONTUI));
	}
	
	Player::MainPlayer->SetMapScale(1280.0f, 840.0f);
	Player::MainPlayer->SetColMapName("FarmHouseColMap.bmp");
	Player::MainPlayer->SetSideLevel("BusStopLevel", "FarmLevel", " ");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
	FadeIn* FadeInSet = CreateActor<FadeIn>(static_cast<int>(ORDER::FADE), "FADE"); 

}

void FarmHouseLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
