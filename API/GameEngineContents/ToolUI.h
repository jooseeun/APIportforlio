#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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
	void SelectSetPivot();
	void CheckToolUIKey();
	void InvenONOFF();

	float NumOne = -352.0;
	float Num = 64.0;

	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	int SelectPivot_;
	bool IsInventory_;
	GameEngineRenderer* Select_;
	GameEngineRenderer* Inventory_;
	GameEngineRenderer* ToolUI_;
};

