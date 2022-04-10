#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class AnimalShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	AnimalShopLevel();
	~AnimalShopLevel();

	// delete Function
	AnimalShopLevel(const AnimalShopLevel& _Other) = delete;
	AnimalShopLevel(AnimalShopLevel&& _Other) noexcept = delete;
	AnimalShopLevel& operator=(const AnimalShopLevel& _Other) = delete;
	AnimalShopLevel& operator=(AnimalShopLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

