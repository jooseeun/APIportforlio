#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class BusStopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BusStopLevel();
	~BusStopLevel();

	// delete Function
	BusStopLevel(const BusStopLevel& _Other) = delete;
	BusStopLevel(BusStopLevel&& _Other) noexcept = delete;
	BusStopLevel& operator=(const BusStopLevel& _Other) = delete;
	BusStopLevel& operator=(BusStopLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

