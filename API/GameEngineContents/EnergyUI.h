#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class EnergyUI :public GameEngineActor
{
public:
	static EnergyUI* EnergyUISet;

	// constrcuter destructer
	EnergyUI();
	~EnergyUI();

	// delete Function
	EnergyUI(const EnergyUI& _Other) = delete;
	EnergyUI(EnergyUI&& _Other) noexcept = delete;
	EnergyUI& operator=(const EnergyUI& _Other) = delete;
	EnergyUI& operator=(EnergyUI&& _Other) noexcept = delete;
	inline void UseEnergy()
	{
		EnergyValue_ -= 1.0f;
	}
protected:

private:
	GameEngineSoundPlayer Sound_;
	void UpdateEnergyValue();
	float EnergyValue_;
	GameEngineRenderer* EnergyUIBar;
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

