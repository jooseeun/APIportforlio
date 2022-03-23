#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class MarnieHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MarnieHouseLevel();
	~MarnieHouseLevel();

	// delete Function
	MarnieHouseLevel(const MarnieHouseLevel& _Other) = delete;
	MarnieHouseLevel(MarnieHouseLevel&& _Other) noexcept = delete;
	MarnieHouseLevel& operator=(const MarnieHouseLevel& _Other) = delete;
	MarnieHouseLevel& operator=(MarnieHouseLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

