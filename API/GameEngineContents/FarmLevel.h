#pragma once
#include "Ax.h"
#include "Hoe.h"
#include "Pick.h"
#include "Sickle.h"
#include "Player.h"
#include "ToolUI.h"
#include "WateringCan.h"
#include "ContentsEnums.h"
#include "PhotatoSeed.h"
#include "BackGround.h"
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
	Ax* AxSet;
	Hoe* HoeSet;
	Pick* PickSet;
	Sickle* SickleSet;
	WateringCan* WateringCanSet;
	ToolUI* ToolUISet;
	PhotatoSeed* PhotatoSeedSet;

	PlayerItem ItemPos_[13];


	int CurSelectPivot_;
	int NextSelectPivot_;

};

