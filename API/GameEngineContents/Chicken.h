#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Time.h"
// ???? :

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
class Chicken : public GameEngineActor
{
public:
	// constrcuter destructer
	Chicken();
	~Chicken();

	// delete Function
	Chicken(const Chicken& _Other) = delete;
	Chicken(Chicken&& _Other) noexcept = delete;
	Chicken& operator=(const Chicken& _Other) = delete;
	Chicken& operator=(Chicken&& _Other) noexcept = delete;

	inline void SetCurDir(AnimalDir _CurDir)
	{
		CurDir_ = _CurDir;
	}
	inline void SetFirstDay()
	{
		FirstDay_ = Time::TimeSet->GetGameDay_();
	}
protected:

private:
	GameEngineSoundPlayer Sound_;
	bool IsBaby_;
	int FirstDay_;
	int FirstHour_;
	int CurHour_;
	bool IsEgg_;

	void CreateEgg();
	GameEngineRenderer* ChickenRender_;
	GameEngineCollision* ChickenCol_;
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

