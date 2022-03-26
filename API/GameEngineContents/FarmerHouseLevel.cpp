#include "FarmerHouseLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	TOOLUI,
	TOPUI,
	ENERGYUI
};
FarmerHouseLevel::FarmerHouseLevel() 
{
}

FarmerHouseLevel::~FarmerHouseLevel() 
{
}

void FarmerHouseLevel::Loading()
{

}

void FarmerHouseLevel::Update()
{

}
void FarmerHouseLevel::LevelChangeStart()
{
	CreateActor<Player>("Player", (int)ORDER::PLAYER);
	CreateActor<ToolUI>("ToolUI", (int)ORDER::TOOLUI);
	CreateActor<TopUI>("TopUI", (int)ORDER::TOPUI);
	CreateActor<EnergyUI>("EnergyUI", (int)ORDER::ENERGYUI);
}