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
class Town2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Town2Level();
	~Town2Level();

	// delete Function
	Town2Level(const Town2Level& _Other) = delete;
	Town2Level(Town2Level&& _Other) noexcept = delete;
	Town2Level& operator=(const Town2Level& _Other) = delete;
	Town2Level& operator=(Town2Level&& _Other) noexcept = delete;

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

