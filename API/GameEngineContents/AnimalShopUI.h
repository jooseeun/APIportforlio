#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineCollision;
class GameEngineRenderer;
class AnimalShopUI : public GameEngineActor
{
public:
	// constrcuter destructer
	AnimalShopUI();
	~AnimalShopUI();

	// delete Function
	AnimalShopUI(const AnimalShopUI& _Other) = delete;
	AnimalShopUI(AnimalShopUI&& _Other) noexcept = delete;
	AnimalShopUI& operator=(const AnimalShopUI& _Other) = delete;
	AnimalShopUI& operator=(AnimalShopUI&& _Other) noexcept = delete;

protected:

private:

	GameEngineCollision* Chicken_;
	GameEngineCollision* Cow_;
	GameEngineRenderer* ChickenName_;
	GameEngineRenderer* ChickenMoney_;
	GameEngineRenderer* CowName_;
	GameEngineRenderer* CowMoney_;
	void CheckMouse();
	void Start() override;
	void Update() override;
};

