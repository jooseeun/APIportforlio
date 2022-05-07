#pragma once
#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class GameEngineRenderer;
class PlayHelpBar :public GameEngineActor
{
public:
	// constrcuter destructer
	PlayHelpBar();
	~PlayHelpBar();

	// delete Function
	PlayHelpBar(const PlayHelpBar& _Other) = delete;
	PlayHelpBar(PlayHelpBar&& _Other) noexcept = delete;
	PlayHelpBar& operator=(const PlayHelpBar& _Other) = delete;
	PlayHelpBar& operator=(PlayHelpBar&& _Other) noexcept = delete;

protected:

private:
	GameEngineRenderer* Render_;
	float PosX_;
	float PosY_;
	bool Up_;
	void Start() override;
	void Update() override;
};

