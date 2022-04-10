#pragma once
#include <GameEngine/GameEngineLevel.h>
// ���� :
class FarmLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FarmLevel();
	~FarmLevel();

	// delete Function
	FarmLevel(const FarmLevel& _Other) = delete;
	FarmLevel(FarmLevel&& _Other) noexcept = delete;
	FarmLevel& operator=(const FarmLevel& _Other) = delete;
	FarmLevel& operator=(FarmLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:

};

