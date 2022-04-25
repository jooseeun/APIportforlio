#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// ���� :
class DropItem : public GameEngineActor
{
public:
	// constrcuter destructer
	DropItem();
	~DropItem();

	// delete Function
	DropItem(const DropItem& _Other) = delete;
	DropItem(DropItem&& _Other) noexcept = delete;
	DropItem& operator=(const DropItem& _Other) = delete;
	DropItem& operator=(DropItem&& _Other) noexcept = delete;
	inline void SetItemKind(PlayerItemKind _DropItemKind)
	{
		DropItemKind_ = _DropItemKind;
	}

	inline void SetItem(PlayerItem _DropItem)
	{
		DropItem_ = _DropItem;
	}
protected:

private:
	SeedType DropSeedType_;
	PlayerItemKind DropItemKind_;
	PlayerItem DropItem_;
	PlayerItem CurDropItem_;
	int IndexNum_;
	GameEngineRenderer* Object_;
	GameEngineCollision* ObjectCol_;

	void Start() override;
	void Update() override;
	void MoveToPlayer();
	std::string ItemToString(PlayerItem _Item);
};

