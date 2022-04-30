#pragma once

#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
// ���� :
class HealthUI :public GameEngineActor
{
public:
	static HealthUI* HealthUISet;
	// constrcuter destructer
	HealthUI();
	~HealthUI();

	// delete Function
	HealthUI(const HealthUI& _Other) = delete;
	HealthUI(HealthUI&& _Other) noexcept = delete;
	HealthUI& operator=(const HealthUI& _Other) = delete;
	HealthUI& operator=(HealthUI&& _Other) noexcept = delete;

	inline void MinusPlayerHP()
	{
		PlayerHp_ -= 5.0f*GameEngineTime::GetDeltaTime();
	}
protected:

private:
	void UpdateEnergyValue();
	float PlayerHp_;
	GameEngineRenderer* HealthBar_;
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

