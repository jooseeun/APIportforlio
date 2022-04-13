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
// ���� :

class ForestLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	ForestLevel();
	~ForestLevel();

	// delete Function
	ForestLevel(const ForestLevel& _Other) = delete;
	ForestLevel(ForestLevel&& _Other) noexcept = delete;
	ForestLevel& operator=(const ForestLevel& _Other) = delete;
	ForestLevel& operator=(ForestLevel&& _Other) noexcept = delete;

	template<typename ItemActor>
	inline void GetItemPos(ItemActor* _Actor)
	{
		int Num = _Actor->GetInvenPos();
		ItemPos_[Num] = _Actor->GetItemName();

	}

protected:
	void Loading() override;
	void Update() override;
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

