#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class NPCShopOnner : public GameEngineActor
{
public:
	// constrcuter destructer
	NPCShopOnner();
	~NPCShopOnner();

	// delete Function
	NPCShopOnner(const NPCShopOnner& _Other) = delete;
	NPCShopOnner(NPCShopOnner&& _Other) noexcept = delete;
	NPCShopOnner& operator=(const NPCShopOnner& _Other) = delete;
	NPCShopOnner& operator=(NPCShopOnner&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

