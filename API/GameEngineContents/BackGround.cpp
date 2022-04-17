#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

BackGround::BackGround()
	:GroundTileMap_(this),
	 CropsTileMap_(this)
{
	
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	Image_ = CreateRenderer();

}


void BackGround::Render()
{
	
}
