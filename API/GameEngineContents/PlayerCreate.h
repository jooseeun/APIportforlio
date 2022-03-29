#pragma once

#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PlayerCreate : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerCreate();
	~PlayerCreate();

	// delete Function
	PlayerCreate(const PlayerCreate& _Other) = delete;
	PlayerCreate(PlayerCreate&& _Other) noexcept = delete;
	PlayerCreate& operator=(const PlayerCreate& _Other) = delete;
	PlayerCreate& operator=(PlayerCreate&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Render() override;

private:

};

