#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class FadeIn : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeIn();
	~FadeIn();

	// delete Function
	FadeIn(const FadeIn& _Other) = delete;
	FadeIn(FadeIn&& _Other) noexcept = delete;
	FadeIn& operator=(const FadeIn& _Other) = delete;
	FadeIn& operator=(FadeIn&& _Other) noexcept = delete;
	inline void StartfadeIn()
	{
		Alpha_ = 255;
		IsFadeIn = true;
	}

protected:

private:
	bool IsFadeIn;
	int Alpha_;
	void Start() override;
	void Update() override;
	GameEngineRenderer* Renderer_;
};

