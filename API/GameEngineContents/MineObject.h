#pragma once
#include "PlayerEnum.h"
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
	MineTileType TileType_;
	int DeathCount_;
	GameEngineCollision* TileCol_;
	GameEngineRenderer* TileRender_;
	bool IsDestroy_;
};

class MineObject : public GameEngineActor
{
public:
	// constrcuter destructer
	MineObject();
	~MineObject();

	// delete Function
	MineObject(const MineObject& _Other) = delete;
	MineObject(MineObject&& _Other) noexcept = delete;
	MineObject& operator=(const MineObject& _Other) = delete;
	MineObject& operator=(MineObject&& _Other) noexcept = delete;
	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		MineTileMap_ = _TileMap;
	}

	inline GameEngineRendererTileMap* ReturnMineTileObejctMap_()
	{
		return MineTileMap_;
	}
protected:

private:
	bool CheckMake_;
	GameEngineRendererTileMap* MineTileMap_;

	void MakeObject(int _Posx, int _Posy, int _index, MineTileType _TileType);
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

