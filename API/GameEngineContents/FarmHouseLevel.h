#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class FarmHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	FarmHouseLevel();
	~FarmHouseLevel();

	// delete Function
	FarmHouseLevel(const FarmHouseLevel& _Other) = delete;
	FarmHouseLevel(FarmHouseLevel&& _Other) noexcept = delete;
	FarmHouseLevel& operator=(const FarmHouseLevel& _Other) = delete;
	FarmHouseLevel& operator=(FarmHouseLevel&& _Other) noexcept = delete;
	GameEngineSoundPlayer BgmPlayer;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:

};

