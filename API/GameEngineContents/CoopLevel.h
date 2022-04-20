#pragma once
#include "Player.h"
#include "ToolUI.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
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

