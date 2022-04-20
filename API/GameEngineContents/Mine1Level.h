#pragma once

#include "Player.h"
#include "ToolUI.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class Mine1Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine1Level();
	~Mine1Level();

	// delete Function
	Mine1Level(const Mine1Level& _Other) = delete;
	Mine1Level(Mine1Level&& _Other) noexcept = delete;
	Mine1Level& operator=(const Mine1Level& _Other) = delete;
	Mine1Level& operator=(Mine1Level&& _Other) noexcept = delete;

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
	ToolUI* ToolUISet;

	PlayerItem ItemPos_[13];


	int CurSelectPivot_;
	int NextSelectPivot_;
};

