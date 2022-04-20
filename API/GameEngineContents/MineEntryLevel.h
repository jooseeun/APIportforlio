#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
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

private:
	PlayerItem ItemPos_[13];
	BackGround* Back;

	int CurSelectPivot_;
	int NextSelectPivot_;
};

