#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

// ���� :
struct ItemData
{
	GameEngineRenderer* Render;
	GameEngineRenderer* NumRender;
	PlayerItem ItemName_;
	PlayerItemKind ItemKind_;
	InvenFloor InvenFloor_;
	int InvenPivot_;
	int ItemCount_ = 1;
	bool Click_ = false;
	bool IsInven= true;
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

	void ItemUse(PlayerItem _Item);
	void CreateItem(ItemData* _Item, std::string _RenderFileName, int _RenderIndex);
	void SetClickItem(int _Pivot);

protected:

private:

	std::list<ItemData*> ItemList_;
	PlayerItem ItemPos_[24];
	int ItemCount_[24];



	bool IsClickON_;
	float FirstPivot_;
	float NumPivot_;
	float InventoryModeXPivot_;
	float InventoryModeYPivot_;
	float InvenFloorYPivot_;
	float MouseX_;
	float MouseY_;

	void ItemCountRenderUpdate();
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void UpdateInvenPos();
	void GetToolUINum();


	void CheckInventoryMode();
	void SetInventoryModePivot();
	bool IsInvenToryMode;
	

};

