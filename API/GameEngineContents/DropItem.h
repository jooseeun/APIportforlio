#pragma once
#include "PlayerEnum.h"
#include "Tool.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
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
	size_t SellValue_;
	float4 InitPos_;
	float4 Move_;
	bool IsStop_;


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
	void DropMove();
	std::string ItemToString(PlayerItem _Item);
};

