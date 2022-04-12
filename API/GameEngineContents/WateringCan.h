#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class WateringCan : public GameEngineActor

{
public:
	// constrcuter destructer
	WateringCan();
	~WateringCan();

	// delete Function
	WateringCan(const WateringCan& _Other) = delete;
	WateringCan(WateringCan&& _Other) noexcept = delete;
	WateringCan& operator=(const WateringCan& _Other) = delete;
	WateringCan& operator=(WateringCan&& _Other) noexcept = delete;

	inline void SetInvenPos(int _InvenPos)
	{
		InvenPos_ = _InvenPos;
	}
	inline int GetInvenPos()
	{
		return InvenPos_;
	}
	inline PlayerItem GetItemName()
	{
		return ItemName_;
	}
protected:

private:
	int InvenPos_;
	void Start() override;
	void Update() override;
	PlayerHave ItemKind_;
	PlayerItem ItemName_;
};

