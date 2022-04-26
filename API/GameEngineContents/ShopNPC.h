#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ShopNPC : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopNPC();
	~ShopNPC();

	// delete Function
	ShopNPC(const ShopNPC& _Other) = delete;
	ShopNPC(ShopNPC&& _Other) noexcept = delete;
	ShopNPC& operator=(const ShopNPC& _Other) = delete;
	ShopNPC& operator=(ShopNPC&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

