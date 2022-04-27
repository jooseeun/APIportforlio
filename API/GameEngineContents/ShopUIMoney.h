#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class ShopUIMoney : public GameEngineActor
{
public:
	// constrcuter destructer
	ShopUIMoney();
	~ShopUIMoney();

	// delete Function
	ShopUIMoney(const ShopUIMoney& _Other) = delete;
	ShopUIMoney(ShopUIMoney&& _Other) noexcept = delete;
	ShopUIMoney& operator=(const ShopUIMoney& _Other) = delete;
	ShopUIMoney& operator=(ShopUIMoney&& _Other) noexcept = delete;

	inline size_t GetShopUIMoney()
	{
		return PlayerShopUIMoney_;
	}

protected:

private:
	int Index_;
	size_t PlayerShopUIMoney_;
	void ShopUIMoneyStringUpdate();
	void ShopUIMoneySeatUpdate();
	GameEngineRenderer* ShopUIMoneyList_[8];
	size_t ShopUIMoneyIndex_[8];
	void Start() override;
	void Update() override;
};

