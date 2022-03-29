#include "FarmHouseLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"
#include "ContentsEnums.h"

FarmHouseLevel::FarmHouseLevel() 
{
}

FarmHouseLevel::~FarmHouseLevel() 
{
}

void FarmHouseLevel::Loading()
{
	CreateActor<Player>( (int)ORDER::PLAYER,"Player");
	CreateActor<ToolUI>( (int)ORDER::UI, "ToolUI" );
	CreateActor<TopUI>( (int)ORDER::UI,"TopUI");
	CreateActor<EnergyUI>( (int)ORDER::UI, "EnergyUI");

}

void FarmHouseLevel::Update()
{

}
void FarmHouseLevel::LevelChangeStart()
{
}