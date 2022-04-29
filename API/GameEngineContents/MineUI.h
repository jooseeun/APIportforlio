#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class MineUI : public GameEngineActor
{
public:
	// constrcuter destructer
	MineUI();
	~MineUI();

	// delete Function
	MineUI(const MineUI& _Other) = delete;
	MineUI(MineUI&& _Other) noexcept = delete;
	MineUI& operator=(const MineUI& _Other) = delete;
	MineUI& operator=(MineUI&& _Other) noexcept = delete;

	inline GameEngineRenderer* GetRenderer()
	{
		return MineRender;
	}

protected:

private:
	GameEngineRenderer* MineRender;

	void Start() override;
	void Update() override;

};

