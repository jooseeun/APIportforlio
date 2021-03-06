#pragma once
#include "PlayerEnum.h"
#include "MineTile.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>


class Mine2Object : public GameEngineActor
{
public:
	static Mine2Object* MainMine2Tile;
	// constrcuter destructer
	Mine2Object();
	~Mine2Object();

	// delete Function
	Mine2Object(const Mine2Object& _Other) = delete;
	Mine2Object(Mine2Object&& _Other) noexcept = delete;
	Mine2Object& operator=(const Mine2Object& _Other) = delete;
	Mine2Object& operator=(Mine2Object&& _Other) noexcept = delete;
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
	void RenderObject();
	void MakeObject(int _Posx, int _Posy, int _index, MineTileType _TileType);
	void Start() override;
	void Update() override;
};

