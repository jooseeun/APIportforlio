#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
// ���� :
class NoMoney : public GameEngineActor
{
public:
	// constrcuter destructer
	NoMoney();
	~NoMoney();

	// delete Function
	NoMoney(const NoMoney& _Other) = delete;
	NoMoney(NoMoney&& _Other) noexcept = delete;
	NoMoney& operator=(const NoMoney& _Other) = delete;
	NoMoney& operator=(NoMoney&& _Other) noexcept = delete;

protected:

private:
	GameEngineSoundPlayer Sound_;
	void Start() override;
	void Update() override;
	float Time;
};

