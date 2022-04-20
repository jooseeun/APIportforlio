#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class Time :public GameEngineActor
{
public:
	static Time* TimeSet;
	// constrcuter destructer
	Time();
	~Time();

	// delete Function
	Time(const Time& _Other) = delete;
	Time(Time&& _Other) noexcept = delete;
	Time& operator=(const Time& _Other) = delete;
	Time& operator=(Time&& _Other) noexcept = delete;

	inline int GetGameMinute_()
	{
		return GameMinute_;
	}
	inline int GetGameHour_()
	{
		return GameHour_;
	}
	inline int GetGameDay_()
	{
		return GameDay_;
	}

protected:

private:
	float Time_;
	float CurTime_;
	int GameHour_;
	int GameMinute_;
	int GameDay_;

	void UpdateGameTime();
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
};

