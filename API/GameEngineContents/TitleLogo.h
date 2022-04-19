#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineCollision;
class TitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;


protected:
	GameEngineCollision* StartCol_;
	GameEngineCollision* ExitCol_;

	void Start();
	void Update() override;

private:
	bool hide_;
	bool show_;

};

