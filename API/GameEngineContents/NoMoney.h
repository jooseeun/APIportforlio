#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class NoMoney : public GameEngineActor
{
public:
	// constrcuter destructer
	NoMoney();
	~NoMoney();

	// delete Function
	NoMoney(const NoMoney& _Other) = delete;
	NoMoney(NoMoney&& _Other) noexcept = delete;
	NoMoney& operator=(const NoMoney& _Other) = delete;
	NoMoney& operator=(NoMoney&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	float Time;
};

