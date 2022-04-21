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

	void Harvest();
	
protected:

private:
	SeedType SeedType_;
	
	void Start() override;
	void Update() override;
	
};

