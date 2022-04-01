#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineImage;
class GameEngineCollision;
class Player:public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineImage* MapColImage_;
protected:

private:
	float Speed_;

	void Update() override;
	void Start() override;
	void Render() override;

};

