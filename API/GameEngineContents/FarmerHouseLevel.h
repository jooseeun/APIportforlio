#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class FarmerHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FarmerHouseLevel();
	~FarmerHouseLevel();

	// delete Function
	FarmerHouseLevel(const FarmerHouseLevel& _Other) = delete;
	FarmerHouseLevel(FarmerHouseLevel&& _Other) noexcept = delete;
	FarmerHouseLevel& operator=(const FarmerHouseLevel& _Other) = delete;
	FarmerHouseLevel& operator=(FarmerHouseLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:

};

