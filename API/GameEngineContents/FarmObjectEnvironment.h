#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>


class EnvironmentTile : public Tile
{
public:
	

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
protected:

private:
	bool CheckMake_;
	GameEngineRendererTileMap* FarmTileMap_;

	std::list< EnvironmentTile* > Tree;
	std::list< EnvironmentTile* > Stone;
	std::list< EnvironmentTile* > Grass;
	void MakeTree(int _Posx, int _Posy, int _index);
	void MakeGrass(float4 _Pos);
	void MakeStone(float4 _Pos);
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

