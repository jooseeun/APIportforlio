#include "FarmLevel.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "BackGround.h"
#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include "ContentsEnums.h"
#include "Mouse.h"
#include "Tool.h"
#include "Time.h"
#include "FrontMap.h"
#include "FadeIn.h"
#include "Money.h"
#include "Barn.h"
#include "Coop.h"
#include "FarmObjectEnvironment.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
FarmLevel::FarmLevel():
	CurSelectPivot_(0),
	NextSelectPivot_(1),
	Back(nullptr)
{
	for (int _Num = 0; _Num < 13; _Num++)
	{
		ItemPos_[_Num] = PlayerItem::Max;
	}
}

FarmLevel::~FarmLevel() 
{

}

void FarmLevel::Loading()
{
	Back = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("Farm.bmp");
	float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
	Back->GetRenderer()->SetPivot(BackImageScale.Half());

	Back->GroundTileMap_.TileRangeSetting(80, 65, { 64,64 });
	Back->CropsTileMap_.TileRangeSetting(80, 65, { 64,64 });

	FrontMap* Front_ = CreateActor<FrontMap>(static_cast<int>(ORDER::PLAYER));

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
	Barn::MainBarn = CreateActor<Barn>(static_cast<int>(ORDER::PLAYER), "Barn");
	Coop::MainCoop = CreateActor<Coop>(static_cast<int>(ORDER::PLAYER), "Coop");
	Barn::MainBarn->Off();
	Coop::MainCoop->Off();
	FarmObjectEnvironment::MainFarmObject = CreateActor< FarmObjectEnvironment>();
	FarmObjectEnvironment::MainFarmObject->SetTileMap(&Back->GroundTileMap_);
	YSortOn(static_cast<int>(ORDER::PLAYER));
	
}

void FarmLevel::Update()
{

	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();
	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;


}

void FarmLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (_PrevLevel->GetNameCopy() == "FarmHouseLevel")
	{
		Player::MainPlayer->SetPosition({ 4120.0f,1020.f });
	}
	else if (_PrevLevel->GetNameCopy() == "BusStopLevel")
	{
		Player::MainPlayer->SetPosition({ 4920.0f,1146.0f });
	}
	else if (_PrevLevel->GetNameCopy() == "BackWoodLevel")
	{
		Player::MainPlayer->SetPosition({ 2616.0f,202.0f});
	}
	else if (_PrevLevel->GetNameCopy() == "CoopLevel")
	{
		Player::MainPlayer->SetPosition({ 3320.0f,1070.0f });
	}
	else if (_PrevLevel->GetNameCopy() == "BarnLevel")
	{
		Player::MainPlayer->SetPosition({ 2790.0f,1070.0f });
	}
	else if (_PrevLevel->GetNameCopy() == "ForestLevel")
	{
		Player::MainPlayer->SetPosition({ 2616.0f,3959.0f});
	}
	Player::MainPlayer->SetMapScale(5120.0f, 4160.0f);
	Player::MainPlayer->SetColMapName("FarmColMap.bmp");
	Player::MainPlayer->SetSideLevel("BackWoodLevel", "BusStopLevel", "FarmHouseLevel");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);

	FadeIn* FadeInSet = CreateActor<FadeIn>(static_cast<int>(ORDER::FADE), "FADE");
}

void FarmLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
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
