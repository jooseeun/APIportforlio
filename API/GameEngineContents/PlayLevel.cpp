#include "PlayLevel.h"
#include "Player.h"
#include "ToolUI.h"
#include "TopUI.h"
#include "EnergyUI.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI,
	NPC,
	TOOL
};
PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{

}

void PlayLevel::Update()
{

}
void PlayLevel::LevelChangeStart()
{
	CreateActor<Player>("Player", (int)ORDER::PLAYER);
	CreateActor<ToolUI>("ToolUI", (int)ORDER::UI);
	CreateActor<TopUI>("TopUI", (int)ORDER::UI);
	CreateActor<EnergyUI>("EnergyUI", (int)ORDER::UI);
}