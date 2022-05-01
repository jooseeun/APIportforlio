#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Coop : public GameEngineActor
{
public:
	static Coop* MainCoop;
	// constrcuter destructer
	Coop();
	~Coop();

	// delete Function
	Coop(const Coop& _Other) = delete;
	Coop(Coop&& _Other) noexcept = delete;
	Coop& operator=(const Coop& _Other) = delete;
	Coop& operator=(Coop&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

