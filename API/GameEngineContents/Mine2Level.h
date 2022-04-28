#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class Mine2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine2Level();
	~Mine2Level();

	// delete Function
	Mine2Level(const Mine2Level& _Other) = delete;
	Mine2Level(Mine2Level&& _Other) noexcept = delete;
	Mine2Level& operator=(const Mine2Level& _Other) = delete;
	Mine2Level& operator=(Mine2Level&& _Other) noexcept = delete;

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

