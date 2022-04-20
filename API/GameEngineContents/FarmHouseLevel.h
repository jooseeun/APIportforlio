#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
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


	inline void GetItemPos()
	{
		for (int _Num = 0; _Num < 13; _Num++)
		{
			ItemPos_[_Num] = Tool::ToolSet->GetToolUIPivotItem(_Num);
		}
	}

	/*template<typename ItemActor>
	inline void ChangeItemPos(ItemActor* _Actor1, ItemActor* _Actor2)
	{
		int Num = _Actor1->GetInvenPos();
		_Actor1->SetInvenPos(_Actor2->GetInvenPos());
		_Actor2->SetInvenPos(Num);
		ItemPos_[Num] = _Actor->GetItemName();

	}*/

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

