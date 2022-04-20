#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Cauliflower : public GameEngineActor
{
public:
	// constrcuter destructer
	Cauliflower();
	~Cauliflower();

	// delete Function
	Cauliflower(const Cauliflower& _Other) = delete;
	Cauliflower(Cauliflower&& _Other) noexcept = delete;
	Cauliflower& operator=(const Cauliflower& _Other) = delete;
	Cauliflower& operator=(Cauliflower&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

