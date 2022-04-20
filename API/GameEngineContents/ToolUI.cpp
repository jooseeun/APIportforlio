#include "ToolUI.h"
#include "Ax.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>

ToolUI* ToolUI::ToolUISet = nullptr;

ToolUI::ToolUI()
	:SelectPivot_(1)
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

	GameEngineCollision* Num1Col = CreateCollision("Num1Col", { 64,64 }, { NumOne, 0 });
	GameEngineCollision* Num2Col = CreateCollision("Num2Col", { 64,64 }, { NumOne + Num * 1, 0 });
	GameEngineCollision* Num3Col = CreateCollision("Num3Col", { 64,64 }, { NumOne + Num * 2, 0 });
	GameEngineCollision* Num4Col = CreateCollision("Num4Col", { 64,64 }, { NumOne + Num * 3, 0 });
	GameEngineCollision* Num5Col = CreateCollision("Num5Col", { 64,64 }, { NumOne + Num * 4, 0 });
	GameEngineCollision* Num6Col = CreateCollision("Num6Col", { 64,64 }, { NumOne + Num * 5, 0 });
	GameEngineCollision* Num7Col = CreateCollision("Num7Col", { 64,64 }, { NumOne + Num * 6, 0 });
	GameEngineCollision* Num8Col = CreateCollision("Num8Col", { 64,64 }, { NumOne + Num * 7, 0 });
	GameEngineCollision* Num9Col = CreateCollision("Num9Col", { 64,64 }, { NumOne + Num * 8, 0 });
	GameEngineCollision* Num10Col = CreateCollision("Num10Col", { 64,64 }, { NumOne + Num * 9, 0 });
	GameEngineCollision* Num11Col = CreateCollision("Num11Col", { 64,64 }, { NumOne + Num * 10, 0 });
	GameEngineCollision* Num12Col = CreateCollision("Num12Col", { 64,64 }, { NumOne + Num * 11, 0 });


}
void ToolUI::Update()
{
	CheckToolUIKey();
	SelectSetPivot();
	InvenONOFF();

}

void ToolUI::InvenONOFF()
{
	if (true == GameEngineInput::GetInst()->IsDown("InvenSwitch"))
	{
		InventorySwitch();
	}

	if (false == GetIsInventory())
	{
		Inventory_->Off();
		ToolUI_->On();
	}

	else if (true == GetIsInventory())
	{
		Inventory_->On();
		ToolUI_->Off();
	}
}


void ToolUI::SelectSetPivot() 
{
	if (SelectPivot_ == 1)
	{
		Select_->SetPivot({ NumOne, 0 });
	}
	else if (SelectPivot_ == 2)
	{
		Select_->SetPivot({ NumOne + Num * 1, 0 });
	}
	else if (SelectPivot_ == 3)
	{
		Select_->SetPivot({ NumOne + Num * 2, 0 });
	}
	else if (SelectPivot_ == 4)
	{
		Select_->SetPivot({ NumOne + Num * 3, 0 });
	}
	else if (SelectPivot_ == 5)
	{
		Select_->SetPivot({ NumOne + Num * 4, 0 });
	}
	else if (SelectPivot_ == 6)
	{
		Select_->SetPivot({ NumOne + Num * 5, 0 });
	}
	else if (SelectPivot_ == 7)
	{
		Select_->SetPivot({ NumOne + Num * 6, 0 });
	}
	else if (SelectPivot_ == 8)
	{
		Select_->SetPivot({ NumOne + Num * 7, 0 });
	}
	else if (SelectPivot_ == 9)
	{
		Select_->SetPivot({ NumOne + Num * 8, 0 });
	}
	else if (SelectPivot_ == 10)
	{
		Select_->SetPivot({ NumOne + Num * 9, 0 });
	}
	else if (SelectPivot_ == 11)
	{
		Select_->SetPivot({ NumOne + Num * 10 , 0 });
	}
	else if (SelectPivot_ == 12)
	{
		Select_->SetPivot({ NumOne + Num * 11, 0 });
	}
}
void ToolUI::CheckToolUIKey()
{
	{
		if (true == GameEngineInput::GetInst()->IsDown("Num1"))
		{
			SelectPivot_ = 1;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num2"))
		{
			SelectPivot_ = 2;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num3"))
		{
			SelectPivot_ = 3;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num4"))
		{
			SelectPivot_ = 4;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num5"))
		{
			SelectPivot_ = 5;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num6"))
		{
			SelectPivot_ = 6;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num7"))
		{
			SelectPivot_ = 7;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num8"))
		{
			SelectPivot_ = 8;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num9"))
		{
			SelectPivot_ = 9;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num0"))
		{
			SelectPivot_ = 10;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num-"))
		{
			SelectPivot_ = 11;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Num="))
		{
			SelectPivot_ = 12;
		}
	}
}


void ToolUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ToolUISet = this;
}