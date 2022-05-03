#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class GameEngineRenderer;
class GameEngineCollision;
class Cow : public GameEngineActor
{
public:
	// constrcuter destructer
	Cow();
	~Cow();

	// delete Function
	Cow(const Cow& _Other) = delete;
	Cow(Cow&& _Other) noexcept = delete;
	Cow& operator=(const Cow& _Other) = delete;
	Cow& operator=(Cow&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* CowRender_;
	GameEngineCollision* CowCol_;
	void Start() override;
	void Update() override;
};

