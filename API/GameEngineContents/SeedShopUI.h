#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class SeedShopUI : public GameEngineActor
{
public:
	// constrcuter destructer
	SeedShopUI();
	~SeedShopUI();

	// delete Function
	SeedShopUI(const SeedShopUI& _Other) = delete;
	SeedShopUI(SeedShopUI&& _Other) noexcept = delete;
	SeedShopUI& operator=(const SeedShopUI& _Other) = delete;
	SeedShopUI& operator=(SeedShopUI&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

