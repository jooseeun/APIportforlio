#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>
// ???? :
struct ItemData
{
	ItemData()
		:NumRender(nullptr),
		Render(nullptr),
		ItemCount_(1),
		Click_(false),
		IsInven(true),
		IsSell_(false),
		SellValue_(0),
		ItemName_(PlayerItem::Max),
		ItemKind_(PlayerItemKind::NoItem),
		InvenFloor_(InvenFloor::Max),
		InvenPivot_(-1)
	{
	}
	GameEngineRenderer* Render;
	GameEngineRenderer* NumRender;
	PlayerItem ItemName_;
	PlayerItemKind ItemKind_;
	InvenFloor InvenFloor_;
	int InvenPivot_;
	int ItemCount_;
	size_t SellValue_;
	bool Click_;
	bool IsSell_;
	bool IsInven;
};

class Tool : public GameEngineActor
{
public:
	static Tool* ToolSet;
	// constrcuter destructer
	Tool();
	~Tool();

	// delete Function
	Tool(const Tool& _Other) = delete;
	Tool(Tool&& _Other) noexcept = delete;
	Tool& operator=(const Tool& _Other) = delete;
	Tool& operator=(Tool&& _Other) noexcept = delete;

	inline void GetCurMousePos()
	{
		POINT Pos_;
		GetCursorPos(&Pos_);
		ScreenToClient(GameEngineWindow::GethWnd(), &Pos_);
		MouseX_ = static_cast<float>(Pos_.x);
		MouseY_ = static_cast<float>(Pos_.y);
	}

	inline PlayerItem GetToolUIPivotItem(int _InvenPivot)
	{
		return ItemPos_[_InvenPivot];
	}
	
	inline void IsInvenOnOff(ItemData _Tool)
	{
		if (false == _Tool.IsInven)
		{
			_Tool.InvenPivot_ = 100;
		}
		else if (true == _Tool.IsInven)
		{
			//_Tool.Render->CreateRenderer();
		}
	}

	inline void ShopON()
	{
		IsShop_ = true;
	}
	inline void ShopOff()
	{
		IsShop_ = false;
	}
	inline bool IsShopCheck()
	{
		return IsShop_;
	}
	void ItemUse(PlayerItem _Item);
	void CreateItem(PlayerItem _ItemName, PlayerItemKind _ItemKind, std::string _RenderFileName, int _RenderIndex, size_t _SellValue);
	void SetClickItem(int _Pivot);

protected:

private:
	GameEngineSoundPlayer Sound_;
	std::vector<GameEngineCollision*> ShopColl_;
	bool IsShop_;
	void UpdateShopInvenPos();
	void ShopUpdate();
	std::vector<ItemData*> ItemList_;
	PlayerItem ItemPos_[24];
	int ItemCount_[24];



	bool IsClickON_;
	float FirstPivot_;
	float NumPivot_;
	float InventoryModeXPivot_;
	float InventoryModeYPivot_;
	float InvenFloorShopYPivot_;
	float InvenFloorYPivot_;
	float MouseX_;
	float MouseY_;

	void ItemCountRenderUpdate();
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void UpdateInvenPos();
	void GetToolUINum();

	void ItemCountRender();
	void CheckInventoryMode();
	void SetInventoryModePivot();
	bool IsInvenToryMode;
	

};

