#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class MineEntryLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MineEntryLevel();
	~MineEntryLevel();

	// delete Function
	MineEntryLevel(const MineEntryLevel& _Other) = delete;
	MineEntryLevel(MineEntryLevel&& _Other) noexcept = delete;
	MineEntryLevel& operator=(const MineEntryLevel& _Other) = delete;
	MineEntryLevel& operator=(MineEntryLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

