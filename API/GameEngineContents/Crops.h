#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Crops : public GameEngineActor
{
public:
	// constrcuter destructer
	Crops();
	~Crops();

	// delete Function
	Crops(const Crops& _Other) = delete;
	Crops(Crops&& _Other) noexcept = delete;
	Crops& operator=(const Crops& _Other) = delete;
	Crops& operator=(Crops&& _Other) noexcept = delete;
	
	inline void SetCropsType(SeedType _SeedType)
	{
		SeedType_ = _SeedType;
	}
	inline void IsHarvestOn_()
	{
		IsHarvest_ = true;
	}
	
protected:

private:
	bool IsHarvest_;
	void Harvest();
	SeedType SeedType_;
	//GameEngineRenderer* Crops_;
	//GameEngineCollision* CropsCol_;

	GameEngineRenderer* CropsHavestAni_;
	void Start() override;
	void Update() override;
	
};

