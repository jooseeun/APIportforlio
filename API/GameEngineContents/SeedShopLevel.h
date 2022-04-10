#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class SeedShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SeedShopLevel();
	~SeedShopLevel();

	// delete Function
	SeedShopLevel(const SeedShopLevel& _Other) = delete;
	SeedShopLevel(SeedShopLevel&& _Other) noexcept = delete;
	SeedShopLevel& operator=(const SeedShopLevel& _Other) = delete;
	SeedShopLevel& operator=(SeedShopLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

