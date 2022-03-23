#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class LobinHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LobinHouseLevel();
	~LobinHouseLevel();

	// delete Function
	LobinHouseLevel(const LobinHouseLevel& _Other) = delete;
	LobinHouseLevel(LobinHouseLevel&& _Other) noexcept = delete;
	LobinHouseLevel& operator=(const LobinHouseLevel& _Other) = delete;
	LobinHouseLevel& operator=(LobinHouseLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

