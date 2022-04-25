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


	PlayerItemKind ItemKind_;
	PlayerItem Item_;
protected:

private:

	GameEngineRenderer* Crops_;

	int IndexNum_;
	SeedType SeedType_;
	SeedType CurSeedType_;
	std::string CropToString(SeedType _SeedType);
	GameEngineRenderer* CropsHavestAni_;
	void Start() override;
	void Update() override;

};

