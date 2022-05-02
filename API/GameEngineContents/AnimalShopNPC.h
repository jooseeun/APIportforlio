#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class AnimalShopNPC : public GameEngineActor
{
public:
	// constrcuter destructer
	AnimalShopNPC();
	~AnimalShopNPC();

	// delete Function
	AnimalShopNPC(const AnimalShopNPC& _Other) = delete;
	AnimalShopNPC(AnimalShopNPC&& _Other) noexcept = delete;
	AnimalShopNPC& operator=(const AnimalShopNPC& _Other) = delete;
	AnimalShopNPC& operator=(AnimalShopNPC&& _Other) noexcept = delete;

protected:

private:

	void Start() override;
	void Update() override;
};

