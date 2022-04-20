#include "FarmLevel.h"
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
#include <GameEngine/GameEngineRendererTileMap.h>
FarmLevel::FarmLevel():
	CurSelectPivot_(0),
	NextSelectPivot_(1)
{

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

	Mouse* MouseSet= CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE), "Mouse");

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
		ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
		TopUI::TopUISet=CreateActor<TopUI>((int)ORDER::UI, "TopUI");
		EnergyUI::EnergyUISet=CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
	}

}

void FarmLevel::Update()
{

	NextSelectPivot_= ToolUI::ToolUISet->getSelectPivot();
	
	if (CurSelectPivot_ != NextSelectPivot_)
	{
		Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}

void FarmLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->SetPosition({ 4120.0f,1020.f });
	Player::MainPlayer->SetMapScale(5120.0f, 4160.0f);
	Player::MainPlayer->SetColMapName("FarmColMap.bmp");
	Player::MainPlayer->SetSideLevel("FarmHouseLevel", "BusStopLevel", " ");
	Player::MainPlayer->SetGroundTileMap(&Back->GroundTileMap_);
	Player::MainPlayer->SetCropsTileMap(&Back->CropsTileMap_);
}

void FarmLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();
	}
}
