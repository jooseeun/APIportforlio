#pragma once
#include "Ax.h"
#include "Hoe.h"
#include "Pick.h"
#include "Sickle.h"
#include "Player.h"
#include "ToolUI.h"
#include "WateringCan.h"
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
	template<typename ItemActor>
	inline void GetItemPos(ItemActor* _Actor)
	{
		int Num = _Actor->GetInvenPos();
		ItemPos_[Num] = _Actor->GetItemName();

	}

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:
	Player* PlayerSet;
	Ax* AxSet;
	Hoe* HoeSet;
	Pick* PickSet;
	Sickle* SickleSet;
	WateringCan* WateringCanSet;
	ToolUI* ToolUISet;

	PlayerItem ItemPos_[13];


	int CurSelectPivot_;
	int NextSelectPivot_;
};

