#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class TitleBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBackGround();
	~TitleBackGround();

	// delete Function
	TitleBackGround(const TitleBackGround& _Other) = delete;
	TitleBackGround(TitleBackGround&& _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround& _Other) = delete;
	TitleBackGround& operator=(TitleBackGround&& _Other) noexcept = delete;

	inline bool IsLogo()
	{
		return StartLogo_;
	}
	inline bool IsBGM()
	{
		return IsBGM_;
	}
protected:
private:
	void Start() override;
	void Update() override;
	float Time_;
	bool Check_;
	bool StartLogo_;
	bool IsBGM_;
	float YPivot_;
	GameEngineRenderer* BackGround_;
	GameEngineRenderer* TitleFish_;
	GameEngineRenderer* Title1_;
	GameEngineRenderer* Title2_;
};

