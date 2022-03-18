#pragma once
#include <GameEngine/GameEngine.h>

// Ό³Έν :
class StardewVallyGame : public GameEngine
{
public:
	// constrcuter destructer
	StardewVallyGame();
	~StardewVallyGame();

	// delete Function
	StardewVallyGame(const StardewVallyGame& _Other) = delete;
	StardewVallyGame(StardewVallyGame&& _Other) noexcept = delete;
	StardewVallyGame& operator=(const StardewVallyGame& _Other) = delete;
	StardewVallyGame& operator=(StardewVallyGame&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;
protected:

private:

};

