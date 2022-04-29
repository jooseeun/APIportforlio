#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Bug : public GameEngineActor
{
public:
	// constrcuter destructer
	Bug();
	~Bug();

	// delete Function
	Bug(const Bug& _Other) = delete;
	Bug(Bug&& _Other) noexcept = delete;
	Bug& operator=(const Bug& _Other) = delete;
	Bug& operator=(Bug&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

