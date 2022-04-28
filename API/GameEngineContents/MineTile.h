#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>

class MineTile : public Tile
{
public:
	MineTile()
		:IsDestroy_(false),
		DeathCount_(1),
		TileCol_(nullptr),
		TileRender_(nullptr),
		TileType_(MineTileType::Max)
	{

	}
	~MineTile()
	{

	}
	MineTileType TileType_;
	int DeathCount_;
	GameEngineCollision* TileCol_;
	GameEngineRenderer* TileRender_;
	bool IsDestroy_;
};