#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Money : public GameEngineActor
{
public:
	static Money* MoneySet;
	// constrcuter destructer
	Money();
	~Money();

	// delete Function
	Money(const Money& _Other) = delete;
	Money(Money&& _Other) noexcept = delete;
	Money& operator=(const Money& _Other) = delete;
	Money& operator=(Money&& _Other) noexcept = delete;
	inline void SetMoney(size_t _PlayerMoney)
	{
		PlayerMoney_ = _PlayerMoney;
	}
	inline size_t GetMoney()
	{
		return PlayerMoney_;
	}
protected:

private:
	int Index_;
	size_t PlayerMoney_;
	void MoneyStringUpdate();
	void MoneySeatUpdate();
	GameEngineRenderer* MoneyList_[8];
	size_t MoneyIndex_[8];
	void Start() override;
	void Update() override;
};

