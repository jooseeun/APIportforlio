#pragma once

#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// ���� :
class TitleLogo;
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;
	GameEngineSoundPlayer BgmPlayer;
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	bool IsCreate_;
	TitleLogo* Logo;
	int count;
	bool IsBGM_;
};

