#pragma once
#include "PlayerEnum.h"
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
	inline void SetCropsType(SeedType _SeedType)
	{
		DropSeedType_ = _SeedType;
	}

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
	int IndexNum_;


	GameEngineRenderer* Crops_;
	GameEngineCollision* CropsCol_;

	void Start() override;
	void Update() override;
	void MoveToPlayer();
};

