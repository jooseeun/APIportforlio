#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class GameEngineRenderer;
class GameEngineCollision;
class Chicken : public GameEngineActor
{
public:
	// constrcuter destructer
	Chicken();
	~Chicken();

	// delete Function
	Chicken(const Chicken& _Other) = delete;
	Chicken(Chicken&& _Other) noexcept = delete;
	Chicken& operator=(const Chicken& _Other) = delete;
	Chicken& operator=(Chicken&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* ChickenRender_;
	GameEngineCollision* ChickenCol_;
	void Start() override;
	void Update() override;
};

