#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Photato : public GameEngineActor
{
public:
	// constrcuter destructer
	Photato();
	~Photato();

	// delete Function
	Photato(const Photato& _Other) = delete;
	Photato(Photato&& _Other) noexcept = delete;
	Photato& operator=(const Photato& _Other) = delete;
	Photato& operator=(Photato&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

