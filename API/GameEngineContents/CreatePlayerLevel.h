#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class CreatePlayerLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CreatePlayerLevel();
	~CreatePlayerLevel();

	// delete Function
	CreatePlayerLevel(const CreatePlayerLevel& _Other) = delete;
	CreatePlayerLevel(CreatePlayerLevel&& _Other) noexcept = delete;
	CreatePlayerLevel& operator=(const CreatePlayerLevel& _Other) = delete;
	CreatePlayerLevel& operator=(CreatePlayerLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

