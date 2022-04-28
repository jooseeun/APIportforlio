#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class Mine1Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine1Level();
	~Mine1Level();

	// delete Function
	Mine1Level(const Mine1Level& _Other) = delete;
	Mine1Level(Mine1Level&& _Other) noexcept = delete;
	Mine1Level& operator=(const Mine1Level& _Other) = delete;
	Mine1Level& operator=(Mine1Level&& _Other) noexcept = delete;

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

