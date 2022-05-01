#pragma once
#include "GameEngine/GameEngineRenderer.h"
#include "GameEngine/GameEngineCollision.h"
#include <GameEngine/GameEngineActor.h>
#include "ShopUIMoney.h"
#include "Tool.h"
#include "FadeIn.h"

// Ό³Έν :
class RobinShopUI : public GameEngineActor
{
public:
	// constrcuter destructer
	RobinShopUI();
	~RobinShopUI();

	// delete Function
	RobinShopUI(const RobinShopUI& _Other) = delete;
	RobinShopUI(RobinShopUI&& _Other) noexcept = delete;
	RobinShopUI& operator=(const RobinShopUI& _Other) = delete;
	RobinShopUI& operator=(RobinShopUI&& _Other) noexcept = delete;

protected:

private:
	ItemData* _Item;
	bool IsShopOpen_;
	void Start() override;
	void Update() override;

	int Page_;
	void CheckPage();
	void Create();
	GameEngineRenderer* FadeIn_;
	GameEngineRenderer* LeftButton_;
	GameEngineRenderer* RightButton_;
	GameEngineRenderer* CreateButton_;
	GameEngineRenderer* Page1_;
	GameEngineRenderer* Page2_;
	GameEngineCollision* ExitCol_;
	GameEngineCollision* LeftCol_;
	GameEngineCollision* RightCol_;
	GameEngineCollision* CreateCol_;
};

