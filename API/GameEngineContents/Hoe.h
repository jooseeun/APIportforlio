#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// ���� :
class Hoe : public GameEngineActor
{
public:
	static Hoe* HoeSet;
	// constrcuter destructer
	Hoe();
	~Hoe();

	// delete Function
	Hoe(const Hoe& _Other) = delete;
	Hoe(Hoe&& _Other) noexcept = delete;
	Hoe& operator=(const Hoe& _Other) = delete;
	Hoe& operator=(Hoe&& _Other) noexcept = delete;
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

