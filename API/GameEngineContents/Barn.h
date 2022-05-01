#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Barn : public GameEngineActor
{
public:
	static Barn* MainBarn;
	// constrcuter destructer
	Barn();
	~Barn();

	// delete Function
	Barn(const Barn& _Other) = delete;
	Barn(Barn&& _Other) noexcept = delete;
	Barn& operator=(const Barn& _Other) = delete;
	Barn& operator=(Barn&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

