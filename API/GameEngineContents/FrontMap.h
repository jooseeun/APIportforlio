#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class FrontMap : public GameEngineActor
{
public:
	// constrcuter destructer
	FrontMap();
	~FrontMap();

	// delete Function
	FrontMap(const FrontMap& _Other) = delete;
	FrontMap(FrontMap&& _Other) noexcept = delete;
	FrontMap& operator=(const FrontMap& _Other) = delete;
	FrontMap& operator=(FrontMap&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	};

protected:
	void Start() override;
	void Render() override;

private:
	GameEngineRenderer* Image_;
};

