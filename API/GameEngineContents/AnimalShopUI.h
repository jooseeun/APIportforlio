#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// ���� :
class GameEngineCollision;
class GameEngineRenderer;
class AnimalShopUI : public GameEngineActor
{
public:
	static AnimalShopUI* AnimalShopUISet;
	// constrcuter destructer
	AnimalShopUI();
	~AnimalShopUI();

	// delete Function
	AnimalShopUI(const AnimalShopUI& _Other) = delete;
	AnimalShopUI(AnimalShopUI&& _Other) noexcept = delete;
	AnimalShopUI& operator=(const AnimalShopUI& _Other) = delete;
	AnimalShopUI& operator=(AnimalShopUI&& _Other) noexcept = delete;

	int ChickenNum_;
	int CowNum_;
protected:

private:

	GameEngineSoundPlayer Sound_;
	GameEngineCollision* Chicken_;
	GameEngineCollision* Cow_;
	GameEngineRenderer* ChickenName_;
	GameEngineRenderer* ChickenMoney_;
	GameEngineRenderer* CowName_;
	GameEngineRenderer* CowMoney_;
	void CheckMouse();
	void BuyCheck();
	void Start() override;
	void Update() override;
};

