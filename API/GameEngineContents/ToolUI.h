#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class ToolUI : public GameEngineActor
{
public:
	static ToolUI* ToolUISet;
	// constrcuter destructer
	ToolUI();
	~ToolUI();

	// delete Function
	ToolUI(const ToolUI& _Other) = delete;
	ToolUI(ToolUI&& _Other) noexcept = delete;
	ToolUI& operator=(const ToolUI& _Other) = delete;
	ToolUI& operator=(ToolUI&& _Other) noexcept = delete;

	
	inline int getSelectPivot()
	{
		return SelectPivot;
	}

	
protected:

private:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	int SelectPivot;
	GameEngineRenderer* Select;
};

