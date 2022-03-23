#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class CoopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CoopLevel();
	~CoopLevel();

	// delete Function
	CoopLevel(const CoopLevel& _Other) = delete;
	CoopLevel(CoopLevel&& _Other) noexcept = delete;
	CoopLevel& operator=(const CoopLevel& _Other) = delete;
	CoopLevel& operator=(CoopLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

