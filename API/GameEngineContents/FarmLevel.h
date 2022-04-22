#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :

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
	GameEngineSoundPlayer BgmPlayer;

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

