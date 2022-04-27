#pragma once
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineCollision.h"
#include <GameEngine/GameEngineActor.h>
#include "ShopUIMoney.h"
#include "Tool.h"

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
	ItemData* _Item;
	bool IsShopOpen_;
	void Start() override;
	void Update() override;

	int Page_;
	void CheckPage();
	void BuySeed();

	GameEngineRenderer* ParsnipSeed_;
	GameEngineRenderer* PhotatoSeed_;
	GameEngineRenderer* CauliFlowerSeed_;
	GameEngineRenderer* BeanSeed_;
	GameEngineRenderer* KaleSeed_;
	GameEngineRenderer* BlueberrieSeed_;
	GameEngineRenderer* MelonSeed_;
	GameEngineRenderer* PepperSeed_;

	GameEngineCollision* ParsnipSeedCol_;
	GameEngineCollision* PhotatoSeedCol_;
	GameEngineCollision* CauliFlowerSeedCol_;
	GameEngineCollision* BeanSeedCol_;
	GameEngineCollision* KaleSeedCol_;
	GameEngineCollision* BlueberrieSeedCol_;
	GameEngineCollision* MelonSeedCol_;
	GameEngineCollision* PepperSeedCol_;

	GameEngineRenderer* FadeIn_;
	GameEngineRenderer* ShopUI_;
	GameEngineRenderer* Exit_;
	GameEngineRenderer* MoneyUI_;
	GameEngineRenderer* InvenUI_;
	GameEngineRenderer* ShopScroll_;
	GameEngineRenderer* ScroppButton_;
	GameEngineCollision* ExitCol_;

};

