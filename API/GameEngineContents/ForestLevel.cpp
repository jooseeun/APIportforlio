#include "ForestLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

ForestLevel::ForestLevel() :
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
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

	Mouse* MouseSet = CreateActor<Mouse>(static_cast<int>(ORDER::MOUSE));

	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	HoeSet = CreateActor<Hoe>((int)ORDER::ITEM, "Hoe");
	AxSet = CreateActor<Ax>((int)ORDER::ITEM, "Ax");
	PickSet = CreateActor<Pick>((int)ORDER::ITEM, "Pick");
	SickleSet = CreateActor<Sickle>((int)ORDER::ITEM, "Sickle");
	WateringCanSet = CreateActor<WateringCan>((int)ORDER::ITEM, "WateringCan");

	PlayerSet = CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 4324.0f,1664.f });
	PlayerSet->SetMapScale(4536.0f, 3084.0f);
	PlayerSet->SetColMapName("ForestColMap.bmp");
	PlayerSet->SetSideLevel("TownLevel", "FarmLevel", "AnimalShopLevel");
}

void ForestLevel::Update()
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