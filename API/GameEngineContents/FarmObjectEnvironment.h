#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>


class EnvironmentTile : public Tile
{
public:
	EnvironmentTile()
		:EnvironmentType_(EnvironmentTileType::Max),
		TreeTop_(nullptr),
		TreeTopCol_(nullptr),
		IsShake_(false),
		IsDestroy_(false),
		TreeTopX_(0),
		TreeTopY_(0),
		TreeAni_(nullptr),
		TileCol_(nullptr),
		DeathCount_(-1)
	{

	}
	int DeathCount_;
	EnvironmentTileType EnvironmentType_;
	GameEngineCollision* TileCol_;

	float TreeTopX_;
	float TreeTopY_;
	GameEngineRenderer* TreeTop_;
	GameEngineRenderer* TreeAni_;
	GameEngineCollision* TreeTopCol_;
	bool IsShake_;
	bool IsDestroy_;
};
// ???? :
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

	inline GameEngineRendererTileMap* ReturnFarmTileObejctMap_()
	{
		return FarmTileMap_;
	}

protected:

private:
	bool CheckMake_;
	GameEngineRendererTileMap* FarmTileMap_;

	std::vector< EnvironmentTile* > Tree;
	std::vector< EnvironmentTile* > Stone;
	std::vector< EnvironmentTile* > Grass;

	void MakeTree(int _Posx, int _Posy, int _index);
	void MakeGrass(int _Posx, int _Posy, int _index);
	void MakeStone(int _Posx, int _Posy, int _index);
	void MakeBranch(int _Posx, int _Posy, int _index);

	void TreeAni(GameEngineRenderer* _TreeTop);
	void CheckTreeAlpha();
	void CheckTreeAnimation();

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

