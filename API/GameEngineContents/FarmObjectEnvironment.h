#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>
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
	GameEngineRendererTileMap* FarmTileMap_;

	std::list< GameEngineRendererTileMap* > Tree;
	std::list< GameEngineRendererTileMap* > Stone;
	std::list< GameEngineRendererTileMap* > Grass;

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

