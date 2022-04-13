#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Pick : public GameEngineActor
{
public:
	// constrcuter destructer
	Pick();
	~Pick();

	// delete Function
	Pick(const Pick& _Other) = delete;
	Pick(Pick&& _Other) noexcept = delete;
	Pick& operator=(const Pick& _Other) = delete;
	Pick& operator=(Pick&& _Other) noexcept = delete;

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
	PlayerItemKind ItemKind_;
	PlayerItem ItemName_;
};

