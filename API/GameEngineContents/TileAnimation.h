#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class TileAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	TileAnimation();
	~TileAnimation();

	// delete Function
	TileAnimation(const TileAnimation& _Other) = delete;
	TileAnimation(TileAnimation&& _Other) noexcept = delete;
	TileAnimation& operator=(const TileAnimation& _Other) = delete;
	TileAnimation& operator=(TileAnimation&& _Other) noexcept = delete;
	inline void SetAniString(std::string _TileString)
	{
		TileString_ = _TileString;

	};
protected:

private:
	void Start() override;
	void Update() override;
private:
	bool IsUpdate_;
	GameEngineRenderer* TileAni_;
	std::string TileString_;
};

