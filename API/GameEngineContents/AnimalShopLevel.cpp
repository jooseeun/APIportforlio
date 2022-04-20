#include "AnimalShopLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>

AnimalShopLevel::AnimalShopLevel():
	CurSelectPivot_(1),
	NextSelectPivot_(1)
{
}

AnimalShopLevel::~AnimalShopLevel() 
{
}


void AnimalShopLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(1);
	Back->GetRenderer()->SetImage("AnimalShop.bmp");
	Back->SetPosition(float4{ Back->GetRenderer()->GetImage()->GetScale().x / 2, Back->GetRenderer()->GetImage()->GetScale().y / 2 });

	CreateActor<TopUI>((int)ORDER::UI, "TopUI");
	CreateActor<EnergyUI>((int)ORDER::UI, "EnergyUI");

	ToolUISet = CreateActor<ToolUI>((int)ORDER::UI, "ToolUI");
	PlayerSet =CreateActor<Player>((int)ORDER::PLAYER, "Player");
	PlayerSet->SetPosition({ 862.0f,1202.f });
	PlayerSet->SetMapScale(2240.0f, 1280.0f);
	PlayerSet->SetColMapName("AnimalShopColMap.bmp");
	PlayerSet->SetSideLevel(" ", "ForestLevel", " ");
}

void AnimalShopLevel::Update()
{

	NextSelectPivot_ = ToolUISet->getSelectPivot();
	if (CurSelectPivot_ != NextSelectPivot_)
	{
		PlayerSet->SetSelectItem(ItemPos_[NextSelectPivot_]);
	}

	CurSelectPivot_ = NextSelectPivot_;
}