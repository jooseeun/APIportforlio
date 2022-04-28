#include "FrontMap.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

FrontMap::FrontMap() 
{
}

FrontMap::~FrontMap() 
{
}

void FrontMap::Start()
{
	GameEngineRenderer* Image_ = CreateRenderer();

	if (GetLevel()->GetNameCopy() == "FarmHouseLevel")
	{
		Image_->SetImage("FarmHouseFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "FarmLevel")
	{
		Image_->SetImage("FarmFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "BusStopLevel")
	{
		Image_->SetImage("BusStopFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "TownLevel")
	{
		Image_->SetImage("TownFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Town2Level")
	{
		Image_->SetImage("BusStopFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "SeedShopLevel")
	{
		Image_->SetImage("SeedShopFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "MineEntryLevel")
	{
		Image_->SetImage("MineEntryFront.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Mine1Level")
	{
		Image_->SetImage("Mine1Front.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "Mine2Level")
	{
		Image_->SetImage("Mine2Front.bmp");
	}
	else if (GetLevel()->GetNameCopy() == "BackWoodLevel")
	{
		Image_->SetImage("BackWoodFront.bmp");
	}
	else
	{
		return;
	}

	Image_->SetOrder(static_cast<int>(ORDER::FRONTMAP));
	float4 FrontImageScale = Image_->GetScale();
	Image_->SetPivot(FrontImageScale.Half());
}


void FrontMap::Render()
{

}
