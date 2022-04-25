#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// ���� :
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
	GameEngineCollision* CropsCol_;
	GameEngineRenderer* Crops_;

	bool IsHarvest_;
	void Harvest();
	SeedType SeedType_;
	PlayerItemKind ItemKind_;
	PlayerItem Item_;

	GameEngineRenderer* CropsHavestAni_;
	void Start() override;
	void Update() override;
	
};

