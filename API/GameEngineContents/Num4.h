#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Num4 : public GameEngineActor
{
public:
	// constrcuter destructer
	Num4();
	~Num4();

	// delete Function
	Num4(const Num4& _Other) = delete;
	Num4(Num4&& _Other) noexcept = delete;
	Num4& operator=(const Num4& _Other) = delete;
	Num4& operator=(Num4&& _Other) noexcept = delete;

protected:

private:
	float Time_;
	void Start() override;
	void Update() override;
};

