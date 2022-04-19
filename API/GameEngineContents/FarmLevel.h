#pragma once

#include "BackGround.h"
#include "PlayerEnum.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
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
	GameEngineSoundPlayer BgmPlayer;

	template<typename ItemActor>
	inline void GetItemPos(ItemActor* _Actor)
	{
		int Num=_Actor->GetInvenPos();
		ItemPos_[Num] = _Actor->GetItemName();

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

	BackGround* Back;
	PlayerItem ItemPos_[13];

	int CurSelectPivot_;
	int NextSelectPivot_;

};

