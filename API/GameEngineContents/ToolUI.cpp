#include "ToolUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

ToolUI* ToolUI::ToolUISet = nullptr;

ToolUI::ToolUI()
	:SelectPivot_(0),
	IsClickItem_(false)
{
}

ToolUI::~ToolUI() 
{

}

void ToolUI::Start()
{
	SetPosition({ 640,664 });
	ToolUI_ = CreateRenderer("ToolUI.bmp");
	ToolUI_->CameraEffectOff();
	Select_ = CreateRenderer("MenuTile.bmp");
	Select_->SetIndex(56);
	Select_->CameraEffectOff();
	Select_->SetPivot({ -352,0 });

	Inventory_ = CreateRenderer("Inventory.bmp");
	Inventory_->SetPivot({ 0,-304 });
	Inventory_->CameraEffectOff();
	FirstPivot_ = -352.0;
	NumPivot_ = 64.0;
	Ypivot_ = 0;

	InvenFirstXPivot_ = -336.0f;
	InvenFirstYPivot_ = -484.0f;
	InvenNumPivot_ = 61.0f;
	InvenFloorPivot_ = 78.0f;

	if (false == GameEngineInput::GetInst()->IsKey("Num1"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1", '1');
		GameEngineInput::GetInst()->CreateKey("Num2", '2');
		GameEngineInput::GetInst()->CreateKey("Num3", '3');
		GameEngineInput::GetInst()->CreateKey("Num4", '4');
		GameEngineInput::GetInst()->CreateKey("Num5", '5');
		GameEngineInput::GetInst()->CreateKey("Num6", '6');
		GameEngineInput::GetInst()->CreateKey("Num7", '7');
		GameEngineInput::GetInst()->CreateKey("Num8", '8');
		GameEngineInput::GetInst()->CreateKey("Num9", '9');
		GameEngineInput::GetInst()->CreateKey("Num0", '0');
		GameEngineInput::GetInst()->CreateKey("Num-", VK_OEM_MINUS);
		GameEngineInput::GetInst()->CreateKey("Num=", VK_OEM_PLUS);

	}

	if (false == GameEngineInput::GetInst()->IsKey("InvenSwitch"))
	{
		GameEngineInput::GetInst()->CreateKey("InvenSwitch", 'E');
	}

	{
		ToolUIPivotColl_.push_back(CreateCollision("Num1Col", { 64,64 }, { FirstPivot_, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num2Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 1, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num3Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 2, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num4Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 3, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num5Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 4, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num6Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 5, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num7Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 6, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num8Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 7, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num9Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 8, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num10Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 9, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num11Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 10, Ypivot_ }));
		ToolUIPivotColl_.push_back(CreateCollision("Num12Col", { 64,64 }, { FirstPivot_ + NumPivot_ * 11, Ypivot_ }));
	}
	{
		InventoryPivotColl_.push_back(CreateCollision("Inven1Col", { 64,64 },{ InvenFirstXPivot_ ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven2Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 1 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven3Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 2 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven4Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 3 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven5Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 4 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven6Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 5 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven7Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 6 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven8Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 7 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven9Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 8 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven10Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 9 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven11Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 10 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven12Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 11 ,InvenFirstYPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven13Col", { 64,64 }, { InvenFirstXPivot_ ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven14Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 1 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven15Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 2 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven16Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 3 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven17Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 4 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven18Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 5 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven19Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 6 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven20Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 7 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven21Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 8 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven22Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 9 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven23Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 10 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		InventoryPivotColl_.push_back(CreateCollision("Inven24Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 11 ,InvenFirstYPivot_ + InvenFloorPivot_}));
		

	}

	ColListCameraEffectOff();
}

void ToolUI::ColListCameraEffectOff()
{
	{
		std::list<GameEngineCollision*>::iterator StartIter = ToolUIPivotColl_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = ToolUIPivotColl_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			(*StartIter)->CameraEffectOff();
		}
	}

	{
		std::list<GameEngineCollision*>::iterator StartIter = InventoryPivotColl_.begin();
		std::list<GameEngineCollision*>::iterator EndIter = InventoryPivotColl_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			(*StartIter)->CameraEffectOff();
		}
	}
}
void ToolUI::Update()
{
	CheckToolUIKey();
	SelectSetPivot();
	InvenONOFF();

}

void ToolUI::InvenONOFF()
{
	std::list<GameEngineCollision*>::iterator ToolUIStartIter = ToolUIPivotColl_.begin();
	std::list<GameEngineCollision*>::iterator ToolUIEndIter = ToolUIPivotColl_.end();
	std::list<GameEngineCollision*>::iterator InventoryStartIter = InventoryPivotColl_.begin();
	std::list<GameEngineCollision*>::iterator InventoryEndIter = InventoryPivotColl_.end();

	if (true == GameEngineInput::GetInst()->IsDown("InvenSwitch"))
	{
		InventorySwitch();
	}

	if (false == GetIsInventory())
	{
		Inventory_->Off();
		ToolUI_->On();
		Select_->On();
		for (; InventoryStartIter != InventoryEndIter; ++InventoryStartIter)
		{
			(*InventoryStartIter)->Off();
		}
		for (; ToolUIStartIter != ToolUIEndIter; ++ToolUIStartIter)
		{
			(*ToolUIStartIter)->On();
		}
	}

	else if (true == GetIsInventory())
	{
		Inventory_->On();
		ToolUI_->Off();
		Select_->Off();
		
		for (; ToolUIStartIter != ToolUIEndIter; ++ToolUIStartIter)
		{
			(*ToolUIStartIter)->Off();
		}
		for (; InventoryStartIter != InventoryEndIter; ++InventoryStartIter)
		{
			(*InventoryStartIter)->On();
		}
	}
}




void ToolUI::SelectSetPivot() 
{
	if (SelectPivot_ == 0)
	{
		Select_->SetPivot({ FirstPivot_, 0 });
	}
	else if (SelectPivot_ == 1)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 1, 0 });
	}
	else if (SelectPivot_ == 2)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 2, 0 });
	}
	else if (SelectPivot_ == 3)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 3, 0 });
	}
	else if (SelectPivot_ == 4)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 4, 0 });
	}
	else if (SelectPivot_ == 5)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 5, 0 });
	}
	else if (SelectPivot_ == 6)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 6, 0 });
	}
	else if (SelectPivot_ == 7)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 7, 0 });
	}
	else if (SelectPivot_ == 8)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 8, 0 });
	}
	else if (SelectPivot_ == 9)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 9, 0 });
	}
	else if (SelectPivot_ == 10)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 10 , 0 });
	}
	else if (SelectPivot_ == 11)
	{
		Select_->SetPivot({ FirstPivot_ + NumPivot_ * 11, 0 });
	}
}

void ToolUI::CheckToolUIKey()
{
	{
		if (true == GameEngineInput::GetInst()->IsDown("Num1"))
		{
			SelectPivot_ = 0;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num2"))
		{
			SelectPivot_ = 1;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num3"))
		{
			SelectPivot_ = 2;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num4"))
		{
			SelectPivot_ = 3;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num5"))
		{
			SelectPivot_ = 4;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num6"))
		{
			SelectPivot_ = 5;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num7"))
		{
			SelectPivot_ = 6;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num8"))
		{
			SelectPivot_ = 7;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num9"))
		{
			SelectPivot_ = 8;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num0"))
		{
			SelectPivot_ = 9;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num-"))
		{
			SelectPivot_ = 10;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num="))
		{
			SelectPivot_ = 11;
		}
	}
}


void ToolUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ToolUISet = this;
}