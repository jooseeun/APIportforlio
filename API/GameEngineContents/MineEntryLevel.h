#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
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
	template<typename ItemActor>
	inline void GetItemPos(ItemActor* _Actor)
	{
		int Num = _Actor->GetInvenPos();
		ItemPos_[Num] = _Actor->GetItemName();

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

