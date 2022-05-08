#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include "RobinShopUI.h"
#include "Mouse.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class RobinShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	RobinShopLevel();
	~RobinShopLevel();

	// delete Function
	RobinShopLevel(const RobinShopLevel& _Other) = delete;
	RobinShopLevel(RobinShopLevel&& _Other) noexcept = delete;
	RobinShopLevel& operator=(const RobinShopLevel& _Other) = delete;
	RobinShopLevel& operator=(RobinShopLevel&& _Other) noexcept = delete;

	inline void GetItemPos()
	{
		for (int _Num = 0; _Num < 13; _Num++)
		{
			ItemPos_[_Num] = Tool::ToolSet->GetToolUIPivotItem(_Num);
		}
	}

	inline void SetSelectPivot(int _SelectPivot)
	{
		CurSelectPivot_ = _SelectPivot;

	}
	inline void CheckOpenRobinShop_()
	{
		IsOpenShop_ = MouseSet->IsOpenShop();
	}
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineSoundPlayer sound;
	Mouse* MouseSet;
	RobinShopUI* ShopUI_;
	PlayerItem ItemPos_[13];
	BackGround* Back;
	bool IsOpenShop_;
	int CurSelectPivot_;
	int NextSelectPivot_;
};

