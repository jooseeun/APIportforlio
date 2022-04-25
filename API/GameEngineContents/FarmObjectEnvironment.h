#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>


class EnvironmentTile : public Tile
{
public:
	EnvironmentTile()
		:EnvironmentType_(EnvironmentTileType::Max)
	{

	}
	int DeathCount_;
	EnvironmentTileType EnvironmentType_;
	GameEngineCollision* TileCol_;
	bool IsDestroy_;
};
// Ό³Έν :
class FarmObjectEnvironment : public GameEngineActor
{
public:
	static FarmObjectEnvironment* MainFarmObject;
	// constrcuter destructer
	FarmObjectEnvironment();
	~FarmObjectEnvironment();

	// delete Function
	FarmObjectEnvironment(const FarmObjectEnvironment& _Other) = delete;
	FarmObjectEnvironment(FarmObjectEnvironment&& _Other) noexcept = delete;
	FarmObjectEnvironment& operator=(const FarmObjectEnvironment& _Other) = delete;
	FarmObjectEnvironment& operator=(FarmObjectEnvironment&& _Other) noexcept = delete;
	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		FarmTileMap_ = _TileMap;
	}

	inline GameEngineRendererTileMap* ReturnFarTileObejctMap_()
	{
		return FarmTileMap_;
	}

protected:

private:
	bool CheckMake_;
	GameEngineRendererTileMap* FarmTileMap_;

	std::list< EnvironmentTile* > Tree;
	std::list< EnvironmentTile* > Stone;
	std::list< EnvironmentTile* > Grass;

	void MakeTree(int _Posx, int _Posy, int _index);
	void MakeGrass(int _Posx, int _Posy, int _index);
	void MakeStone(int _Posx, int _Posy, int _index);
	void MakeBranch(int _Posx, int _Posy, int _index);


	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

