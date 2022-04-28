#pragma once
#include "PlayerEnum.h"
#include "MineTile.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>


class Mine1Object : public GameEngineActor
{
public:
	static Mine1Object* MainMine1Tile;
	// constrcuter destructer
	Mine1Object();
	~Mine1Object();

	// delete Function
	Mine1Object(const Mine1Object& _Other) = delete;
	Mine1Object(Mine1Object&& _Other) noexcept = delete;
	Mine1Object& operator=(const Mine1Object& _Other) = delete;
	Mine1Object& operator=(Mine1Object&& _Other) noexcept = delete;
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

