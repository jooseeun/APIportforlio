#include "SeedShopLevel.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
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
		Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });

		CreateActor<TopUI>((int)ORDER::UI, "TopUI");
		CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

		ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
		HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
		AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
		PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
		SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
		WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");

		Player* PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
		PlayerSet->SetPosition({ 414.0f,1770.f });
		PlayerSet->SetMapScale(3072.0f, 2048.0f);
		PlayerSet->SetColMapName("SeedShopColMap.bmp");
		PlayerSet->SetSideLevel(" ", "TownLevel", " ");
}

void SeedShopLevel::Update()
{
	GetItemPos<Ax>(AxSet);
	GetItemPos<Pick>(PickSet);
	GetItemPos<Hoe>(HoeSet);
	GetItemPos<Sickle>(SickleSet);
	GetItemPos<WateringCan>(WateringCanSet);

	NextSelectPivot_ = ToolUISet->getSelectPivot();
	if (CurSelectPivot_ != NextSelectPivot_)
	{
		PlayerSet->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}