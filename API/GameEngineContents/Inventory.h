#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Inventory :public GameEngineActor
{
public:
	static Inventory* InventorySet;
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;
	inline void InventorySwitch()
	{
		IsInventory_ = !IsInventory_;
	}
	inline bool GetIsInventory()
	{
		return IsInventory_;
	}
protected:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	bool IsInventory_;

};

