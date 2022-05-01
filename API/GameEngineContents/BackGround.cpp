#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
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
	if (GetLevel()->GetNameCopy() == "Town2Level")
	{
		GameEngineCollision* MoveCol_ = CreateCollision("MapMoveCol", { 128,64 }, {790.0f,1645.0f});
	}

}


void BackGround::Render()
{
	
}
