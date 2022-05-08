#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class Chicken;
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
	GameEngineSoundPlayer Sound_;
	PlayerItem ItemPos_[13];
	BackGround* Back;
	Chicken* Chicken_[4];
	void CreateAnimal();
	int CurSelectPivot_;
	int NextSelectPivot_;
};

