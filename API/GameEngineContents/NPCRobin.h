#pragma once

#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class NPCRobin : public GameEngineActor
{
public:
	// constrcuter destructer
	NPCRobin();
	~NPCRobin();

	// delete Function
	NPCRobin(const NPCRobin& _Other) = delete;
	NPCRobin(NPCRobin&& _Other) noexcept = delete;
	NPCRobin& operator=(const NPCRobin& _Other) = delete;
	NPCRobin& operator=(NPCRobin&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;
};

