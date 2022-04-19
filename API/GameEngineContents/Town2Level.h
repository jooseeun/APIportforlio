#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class Town2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Town2Level();
	~Town2Level();

	// delete Function
	Town2Level(const Town2Level& _Other) = delete;
	Town2Level(Town2Level&& _Other) noexcept = delete;
	Town2Level& operator=(const Town2Level& _Other) = delete;
	Town2Level& operator=(Town2Level&& _Other) noexcept = delete;

	template<typename ItemActor>
	inline void GetItemPos(ItemActor* _Actor)
	{
		int Num = _Actor->GetInvenPos();
		ItemPos_[Num] = _Actor->GetItemName();

	}

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;
private:
	PlayerItem ItemPos_[13];
	BackGround* Back;


	int CurSelectPivot_;
	int NextSelectPivot_;
};

