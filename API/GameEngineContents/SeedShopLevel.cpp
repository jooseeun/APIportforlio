#include "SeedShopLevel.h"
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

SeedShopLevel::SeedShopLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

SeedShopLevel::~SeedShopLevel() 
{
}

void SeedShopLevel::Loading()
{
		BackGround* Back = CreateActor<BackGround>(1);
		Back->GetRenderer()->SetImage("SeedShop.bmp");
		float4 BackImageScale = Back->GetRenderer()->GetImage()->GetScale();
		Back->GetRenderer()->SetPivot(BackImageScale.Half());

		Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE));

		if (nullptr == Player::MainPlayer)
		{
			Player::MainPlayer = CreateActor<Player>(static_cast<int>(ORDER::PLAYER), "Player");
			ToolUI::ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
			TopUI::TopUISet = CreateActor<TopUI>((int)ORDER::UI, "TopUI");
			EnergyUI::EnergyUISet = CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");
		
		}

		
}


void SeedShopLevel::Update()
{


	NextSelectPivot_ = ToolUI::ToolUISet->getSelectPivot();

	if (CurSelectPivot_ != NextSelectPivot_)
	{
		Player::MainPlayer->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}

void SeedShopLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	Player::MainPlayer->SetPosition({ 414.0f,1770.f });
	Player::MainPlayer->SetMapScale(3072.0f, 2048.0f);
	Player::MainPlayer->SetColMapName("SeedShopColMap.bmp");
	Player::MainPlayer->SetSideLevel(" ", "TownLevel", " ");
}

void SeedShopLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (_NextLevel->GetNameCopy() != "TitleLevel")
	{
		Player::MainPlayer->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		ToolUI::ToolUISet->NextLevelOn();
		TopUI::TopUISet->NextLevelOn();

	}
}
