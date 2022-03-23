#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class PlayerCreateLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayerCreateLevel();
	~PlayerCreateLevel();

	// delete Function
	PlayerCreateLevel(const PlayerCreateLevel& _Other) = delete;
	PlayerCreateLevel(PlayerCreateLevel&& _Other) noexcept = delete;
	PlayerCreateLevel& operator=(const PlayerCreateLevel& _Other) = delete;
	PlayerCreateLevel& operator=(PlayerCreateLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

