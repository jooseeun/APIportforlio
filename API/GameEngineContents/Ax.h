#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Ax : public GameEngineActor
{
public:
	static Ax* AxSet;
	// constrcuter destructer
	Ax();
	~Ax();

	// delete Function
	Ax(const Ax& _Other) = delete;
	Ax(Ax&& _Other) noexcept = delete;
	Ax& operator=(const Ax& _Other) = delete;
	Ax& operator=(Ax&& _Other) noexcept = delete;
	
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

