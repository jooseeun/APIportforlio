#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include "SeedShopUI.h"
#include "Mouse.h"
#include "ShopUIMoney.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class SeedShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SeedShopLevel();
	~SeedShopLevel();

	// delete Function
	SeedShopLevel(const SeedShopLevel& _Other) = delete;
	SeedShopLevel(SeedShopLevel&& _Other) noexcept = delete;
	SeedShopLevel& operator=(const SeedShopLevel& _Other) = delete;
	SeedShopLevel& operator=(SeedShopLevel&& _Other) noexcept = delete;

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

	inline void CheckOpenShop_()
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
	ShopUIMoney* ShopMoney_;
	Mouse* MouseSet;
	SeedShopUI* ShopUI_;
	PlayerItem ItemPos_[13];
	BackGround* Back;
	bool IsOpenShop_;
	int CurSelectPivot_;
	int NextSelectPivot_;
};

