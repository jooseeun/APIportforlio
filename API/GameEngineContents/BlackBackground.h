#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class BlackBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	BlackBackground();
	~BlackBackground();

	// delete Function
	BlackBackground(const BlackBackground& _Other) = delete;
	BlackBackground(BlackBackground&& _Other) noexcept = delete;
	BlackBackground& operator=(const BlackBackground& _Other) = delete;
	BlackBackground& operator=(BlackBackground&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;

private:
};

