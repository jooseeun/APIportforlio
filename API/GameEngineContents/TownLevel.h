#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class TownLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TownLevel();
	~TownLevel();

	// delete Function
	TownLevel(const TownLevel& _Other) = delete;
	TownLevel(TownLevel&& _Other) noexcept = delete;
	TownLevel& operator=(const TownLevel& _Other) = delete;
	TownLevel& operator=(TownLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

