#pragma once
#include "Player.h"
#include "ToolUI.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class Mine2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine2Level();
	~Mine2Level();

	// delete Function
	Mine2Level(const Mine2Level& _Other) = delete;
	Mine2Level(Mine2Level&& _Other) noexcept = delete;
	Mine2Level& operator=(const Mine2Level& _Other) = delete;
	Mine2Level& operator=(Mine2Level&& _Other) noexcept = delete;

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

