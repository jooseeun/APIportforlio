#pragma once
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineCollision.h"
#include <GameEngine/GameEngineActor.h>

// ���� :
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
	inline void ShopOpen()
	{
		IsShopOpen_ = true;
	}
protected:

private:
	bool IsShopOpen_;
	void Start() override;
	void Update() override;

	GameEngineRenderer* FadeIn_;
	GameEngineRenderer* ShopUI_;
	GameEngineRenderer* Exit_;
	GameEngineCollision* ExitCol_;

};

