#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class TopUI : public GameEngineActor
{
public:
	static TopUI* TopUISet;
	// constrcuter destructer
	TopUI();
	~TopUI();

	// delete Function
	TopUI(const TopUI& _Other) = delete;
	TopUI(TopUI&& _Other) noexcept = delete;
	TopUI& operator=(const TopUI& _Other) = delete;
	TopUI& operator=(TopUI&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* DateRender_;
	GameEngineRenderer* HourRender_;
	GameEngineRenderer* MinuteRender_;
	GameEngineRenderer* AMPMRender_;
	int Date_;
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

