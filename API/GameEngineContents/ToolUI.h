#pragma once

#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class ToolUI : public GameEngineActor
{
public:
	static ToolUI* ToolUISet;
	// constrcuter destructer
	ToolUI();
	~ToolUI();

	// delete Function
	ToolUI(const ToolUI& _Other) = delete;
	ToolUI(ToolUI&& _Other) noexcept = delete;
	ToolUI& operator=(const ToolUI& _Other) = delete;
	ToolUI& operator=(ToolUI&& _Other) noexcept = delete;

	
	inline int getSelectPivot()
	{
		return SelectPivot_;
	}
	inline void SetSelectPivot(int _SelectPivot)
	{
		SelectPivot_ = _SelectPivot;
	}

	inline void InventorySwitch()
	{
		IsInventory_ = !IsInventory_;
	}
	inline bool GetIsInventory()
	{
		return IsInventory_;
	}

protected:

private:

	int ClickPivot_;
	bool IsClickItem_;

	void SelectSetPivot();
	void CheckToolUIKey();
	void InvenONOFF();

	float FirstPivot_;
	float NumPivot_;
	float Ypivot_;

	float InvenFirstXPivot_;
	float InvenFirstYPivot_;
	float InvenNumPivot_;
	float InvenFloorPivot_;

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	int SelectPivot_;
	bool IsInventory_;
	GameEngineRenderer* Select_;
	GameEngineRenderer* Inventory_;
	GameEngineRenderer* ToolUI_;

	std::list<GameEngineCollision*> ToolUIPivotColl_;
	std::list<GameEngineCollision*> InventoryPivotColl_;

	void ColListCameraEffectOff();

};

