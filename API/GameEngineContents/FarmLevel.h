#pragma once
#include "Ax.h"
#include "Hoe.h"
#include "Pick.h"
#include "Sickle.h"
#include "Player.h"
#include "ToolUI.h"
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
	ToolUI* ToolUISet;

	PlayerItem ItemPos_[13];


	int CurSelectPivot_;
	int NextSelectPivot_;

};

