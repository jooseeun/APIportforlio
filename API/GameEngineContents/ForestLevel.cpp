#include "ForestLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include "Mouse.h"
#include "FrontMap.h"
#include "Time.h"
#include "Money.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

ForestLevel::ForestLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1),
	Back(nullptr)
{
	for (int _Num = 0; _Num < 13; _Num++)
	{
		ItemPos_[_Num] = PlayerItem::Max;
	}
}

ForestLevel::~ForestLevel()
{
}

void ForestLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("Forest.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });
	Back->GroundTileMap_.TileRangeSetting(90, 34, { 48,48 });
	Back->CropsTileMap_.TileRangeSetting(90, 34, { 48,48 });


	//FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::PLAYER));
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

void ForestLevel::Update()
{
	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();


	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;
}
void ForestLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel->GetNameCopy() == "TownLevel")
	{
		Player::MainPlayer->SetPosition({ 4324.0f,1664.f });
	}
	if (_PrevLevel->GetNameCopy() == "AnimalShopLevel")
	{
		Player::MainPlayer->SetPosition({ 2649,1082.0f});
	}
	
	Player::MainPlayer->SetMapScale(4536.0f, 3084.0f);
	Player::MainPlayer->SetColMapName("ForestColMap.bmp");
	Player::MainPlayer->SetSideLevel("TownLevel", "FarmLevel", "AnimalShopLevel");
}
void ForestLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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