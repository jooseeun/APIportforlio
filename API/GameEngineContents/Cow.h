#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Time.h"
// Ό³Έν :

enum class AnimalState
{
	Idle,
	Walk,
	Max
};
enum class AnimalDir
{
	Front,
	Right,
	Back,
	Left,
	Max
};
class GameEngineRenderer;
class GameEngineCollision;
class Cow : public GameEngineActor
{
public:
	// constrcuter destructer
	Cow();
	~Cow();

	// delete Function
	Cow(const Cow& _Other) = delete;
	Cow(Cow&& _Other) noexcept = delete;
	Cow& operator=(const Cow& _Other) = delete;
	Cow& operator=(Cow&& _Other) noexcept = delete;
	inline bool IsBabyReturn()
	{
		return IsBaby_;
	}
	inline void SetCurDir(AnimalDir _CurDir)
	{
		CurDir_ = _CurDir;
	}
	inline void SetFirstDay()
	{
		FirstDay_ = Time::TimeSet->GetGameDay_();
	}
	void CreateMilk();
protected:

private:
	bool IsBaby_;
	int FirstDay_;
	int FirstHour_;
	int CurHour_;
	bool IsMilk_;

	GameEngineRenderer* CowRender_;
	GameEngineCollision* CowCol_;
	void Start() override;
	void Update() override;

	float4 CurPos_;
	float4 NextPos_;
	float Time;
	AnimalState CurState_;
	AnimalDir CurDir_;
	std::string GetDirString();
	void ChangeAni();
public:
	void ChangeState(AnimalState _State);
	void StateUpdate();
private:

	void IdleUpdate();
	void WalkUpdate();

	void IdleStart();
	void WalkStart();
};

