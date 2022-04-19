#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
// Ό³Έν :
class Mouse :public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;
	inline void GetCurPos()
	{
		POINT Pos_;
		GetCursorPos(&Pos_);
		ScreenToClient(GameEngineWindow::GethWnd(), &Pos_);
		CurPos_.x = static_cast<float>(Pos_.x);
		CurPos_.y = static_cast<float>(Pos_.y);
	}
protected:

private:
	float4 CurPos_;
	void Start() override;
	void Update() override;
};

