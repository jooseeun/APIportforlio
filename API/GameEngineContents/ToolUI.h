#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class ToolUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ToolUI();
	~ToolUI();

	// delete Function
	ToolUI(const ToolUI& _Other) = delete;
	ToolUI(ToolUI&& _Other) noexcept = delete;
	ToolUI& operator=(const ToolUI& _Other) = delete;
	ToolUI& operator=(ToolUI&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
	GameEngineRenderer* Select;
};

