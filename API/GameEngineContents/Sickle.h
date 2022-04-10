#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Sickle : public GameEngineActor

{
public:
	// constrcuter destructer
	Sickle();
	~Sickle();

	// delete Function
	Sickle(const Sickle& _Other) = delete;
	Sickle(Sickle&& _Other) noexcept = delete;
	Sickle& operator=(const Sickle& _Other) = delete;
	Sickle& operator=(Sickle&& _Other) noexcept = delete;

	inline void SetInvenPos(int _InvenPos)
	{
		InvenPos_ = _InvenPos;
	}
	inline int getInvenPos()
	{
		return InvenPos_;
	}
protected:

private:
	int InvenPos_;
	void Start() override;
	void Update() override;
	PlayerHave ItemKind_;
};

