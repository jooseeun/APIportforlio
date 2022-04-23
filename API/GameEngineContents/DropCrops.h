#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class DropCrops : public GameEngineActor
{
public:
	// constrcuter destructer
	DropCrops();
	~DropCrops();

	// delete Function
	DropCrops(const DropCrops& _Other) = delete;
	DropCrops(DropCrops&& _Other) noexcept = delete;
	DropCrops& operator=(const DropCrops& _Other) = delete;
	DropCrops& operator=(DropCrops&& _Other) noexcept = delete;
	inline void SetCropsType(SeedType _SeedType)
	{
		SeedType_ = _SeedType;
	}
protected:

private:
	SeedType SeedType_;

	GameEngineRenderer* Crops_;
	GameEngineCollision* CropsCol_;

	void Start() override;
	void Update() override;
	void MoveToPlayer();
};

