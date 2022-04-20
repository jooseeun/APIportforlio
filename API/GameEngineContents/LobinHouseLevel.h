#pragma once
#include "Player.h"
#include "ToolUI.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class LobinHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	LobinHouseLevel();
	~LobinHouseLevel();

	// delete Function
	LobinHouseLevel(const LobinHouseLevel& _Other) = delete;
	LobinHouseLevel(LobinHouseLevel&& _Other) noexcept = delete;
	LobinHouseLevel& operator=(const LobinHouseLevel& _Other) = delete;
	LobinHouseLevel& operator=(LobinHouseLevel&& _Other) noexcept = delete;

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

