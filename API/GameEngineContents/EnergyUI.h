#pragma once

// Ό³Έν :
class EnergyUI
{
public:
	// constrcuter destructer
	EnergyUI();
	~EnergyUI();

	// delete Function
	EnergyUI(const EnergyUI& _Other) = delete;
	EnergyUI(EnergyUI&& _Other) noexcept = delete;
	EnergyUI& operator=(const EnergyUI& _Other) = delete;
	EnergyUI& operator=(EnergyUI&& _Other) noexcept = delete;

protected:

private:

};

