#pragma once
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineCollision.h"
#include <GameEngine/GameEngineActor.h>
#include "ShopUIMoney.h"

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
	bool IsShopOpen_;
	void Start() override;
	void Update() override;

	int Page_;
	void CheckPage();
	GameEngineRenderer* ParsnipSeed_;
	GameEngineRenderer* PhotatoSeed_;
	GameEngineRenderer* CauliFlowerSeed_;
	GameEngineRenderer* BeanSeed_;
	GameEngineRenderer* KaleSeed_;
	GameEngineRenderer* BlueberrieSeed_;
	GameEngineRenderer* MelonSeed_;
	GameEngineRenderer* PepperSeed_;

	GameEngineRenderer* FadeIn_;
	GameEngineRenderer* ShopUI_;
	GameEngineRenderer* Exit_;
	GameEngineRenderer* MoneyUI_;
	GameEngineRenderer* InvenUI_;
	GameEngineRenderer* ShopScroll_;
	GameEngineRenderer* ScroppButton_;
	GameEngineCollision* ExitCol_;

};

