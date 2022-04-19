#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class PhotatoSeed : public GameEngineActor
{
public:
	static PhotatoSeed* PhotatoSeedSet;
	// constrcuter destructer
	PhotatoSeed();
	~PhotatoSeed();

	// delete Function
	PhotatoSeed(const PhotatoSeed& _Other) = delete;
	PhotatoSeed(PhotatoSeed&& _Other) noexcept = delete;
	PhotatoSeed& operator=(const PhotatoSeed& _Other) = delete;
	PhotatoSeed& operator=(PhotatoSeed&& _Other) noexcept = delete;
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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	PlayerItemKind ItemKind_;
	PlayerItem ItemName_;
};

