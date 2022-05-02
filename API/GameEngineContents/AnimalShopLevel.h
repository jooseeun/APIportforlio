#pragma once
#include "BackGround.h"
#include "PlayerEnum.h"
#include "Tool.h"
#include "AnimalShopUI.h"
#include "Mouse.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class AnimalShopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	AnimalShopLevel();
	~AnimalShopLevel();

	// delete Function
	AnimalShopLevel(const AnimalShopLevel& _Other) = delete;
	AnimalShopLevel(AnimalShopLevel&& _Other) noexcept = delete;
	AnimalShopLevel& operator=(const AnimalShopLevel& _Other) = delete;
	AnimalShopLevel& operator=(AnimalShopLevel&& _Other) noexcept = delete;

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
	inline void CheckOpenAnimalShop_()
	{
		IsOpenShop_ = MouseSet->IsOpenShop();
	}
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	Mouse* MouseSet;
	AnimalShopUI* ShopUI_;
	PlayerItem ItemPos_[13];
	BackGround* Back;
	bool IsOpenShop_;
	int CurSelectPivot_;
	int NextSelectPivot_;
};

