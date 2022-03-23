#include "FarmerHouseLevel.h"
#include "Player.h"
#include "ToolUI.h"
enum class ORDER
{
	BACKGROUND,
	PLAYER,
	TOOLUI
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
}