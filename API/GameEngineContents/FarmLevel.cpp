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
#include "Photato.h"
#include "Kale.h"
#include "Cauliflower.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
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

void FarmLevel::Update()
{

	GetItemPos();

	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();
	Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);

	CurSelectPivot_ = NextSelectPivot_;

	CreateCropActorUpdate();

}
void FarmLevel::CreateCropActorUpdate()
{
	if (true == Player::MainPlayer->IsCreateCropTile_)
	{
		if (SeedType::Photato == Player::MainPlayer->CreateSeedType_)
		{
			Photato* Crop = CreateActor<Photato>(static_cast<int>(ORDER::CROP), "Photato");
			Crop->SetPosition(Player::MainPlayer->CreateCropPos_);
		}
		else if (SeedType::Kale == Player::MainPlayer->CreateSeedType_)
		{
			Kale* Crop = CreateActor<Kale>(static_cast<int>(ORDER::CROP), "Kale");
			Crop->SetPosition(Player::MainPlayer->CreateCropPos_);
		}
		else if (SeedType::Cauliflower == Player::MainPlayer->CreateSeedType_)
		{
			Cauliflower* Crop = CreateActor<Cauliflower>(static_cast<int>(ORDER::CROP), "Cauliflower");
			Crop->SetPosition(Player::MainPlayer->CreateCropPos_);
		}

		Player::MainPlayer->IsCreateCropTile_ = false;
	}
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
		TopUI::TopUISet->NextLevelOn();
		EnergyUI::EnergyUISet->NextLevelOn();
		Tool::ToolSet->NextLevelOn();
		Time::TimeSet->NextLevelOn();
	}
}
