#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class narrationLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	narrationLevel();
	~narrationLevel();

	// delete Function
	narrationLevel(const narrationLevel& _Other) = delete;
	narrationLevel(narrationLevel&& _Other) noexcept = delete;
	narrationLevel& operator=(const narrationLevel& _Other) = delete;
	narrationLevel& operator=(narrationLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

