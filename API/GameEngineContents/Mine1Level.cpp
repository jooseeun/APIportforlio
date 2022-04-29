#include "Mine1Level.h"
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
#include "Mine1Object.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

Mine1Level::Mine1Level() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

Mine1Level::~Mine1Level() 
{
}

void Mine1Level::Loading()
{

	Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Mine1.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());

	Back->GroundTileMap_.TileRangeSetting(20, 20, { 64,64 });

	FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::FRONTMAP));
	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

	if(nullptr == Mine1Object::MainMine1Tile)
	{
		Mine1Object::MainMine1Tile = CreateActor<Mine1Object>(static_cast<int>(ORDER::GROUND), "Mine1Object");
		Mine1Object::MainMine1Tile->SetTileMap(&Back->GroundTileMap_);
	}

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

void Mine1Level::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
}

void Mine1Level::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	Player::MainPlayer->SetPosition({ 672.0f,265.0f});
	Player::MainPlayer->SetMapScale(1280.0f, 1280.0f);
	Player::MainPlayer->SetColMapName("Mine1ColMap.bmp");
	Player::MainPlayer->SetSideLevel("", "Mine2Level", " ");
	Player::MainPlayer->SetMineTileMap(&Back->GroundTileMap_);
	FadeIn* FadeInSet = CreateActor<FadeIn>(static_cast<int>(ORDER::FADE), "FADE");
	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

}

void Mine1Level::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
