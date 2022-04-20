#pragma once
#include <GameEngine/GameEngineActor.h>
// ���� :
class Kale : public GameEngineActor
{
public:
	// constrcuter destructer
	Kale();
	~Kale();

	// delete Function
	Kale(const Kale& _Other) = delete;
	Kale(Kale&& _Other) noexcept = delete;
	Kale& operator=(const Kale& _Other) = delete;
	Kale& operator=(Kale&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

