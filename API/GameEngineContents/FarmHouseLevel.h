#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class FarmHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FarmHouseLevel();
	~FarmHouseLevel();

	// delete Function
	FarmHouseLevel(const FarmHouseLevel& _Other) = delete;
	FarmHouseLevel(FarmHouseLevel&& _Other) noexcept = delete;
	FarmHouseLevel& operator=(const FarmHouseLevel& _Other) = delete;
	FarmHouseLevel& operator=(FarmHouseLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:
};

