#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class Cow;
class BarnLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BarnLevel();
	~BarnLevel();

	// delete Function
	BarnLevel(const BarnLevel& _Other) = delete;
	BarnLevel(BarnLevel&& _Other) noexcept = delete;
	BarnLevel& operator=(const BarnLevel& _Other) = delete;
	BarnLevel& operator=(BarnLevel&& _Other) noexcept = delete;

	inline void GetItemPos()
	{
		for (int _Num = 0; _Num < 13; _Num++)
		{
			ItemPos_[_Num] = Tool::ToolSet->GetToolUIPivotItem(_Num);
		}
	}

	inline void SetSelectPivot(int _SelectPivot)
	{
		CurSelectPivot_ = _SelectPivot;

	}

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

	void CreateAnimal();

private:
	GameEngineSoundPlayer sound;
	PlayerItem ItemPos_[13];
	BackGround* Back;

	Cow* Cow_[4];
	int CurSelectPivot_;
	int NextSelectPivot_;
};

