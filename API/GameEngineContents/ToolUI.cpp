#include "ToolUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#define VK_SUB 0x07
ToolUI::ToolUI() 
{
}

ToolUI::~ToolUI() 
{
}

void ToolUI::Start()
{
	SetPosition({ 640,664 });
	GameEngineRenderer* ToolUI = CreateRenderer("ToolUI.bmp");
	ToolUI->CameraEffectOff();
	Select = CreateRenderer("MenuTile.bmp");
	Select->SetIndex(56);
	Select->CameraEffectOff();
	Select->SetPivot({ -335,0 });
	//Select->SetPivot({ -91,0 });
	//Select->SetPivot({ -30,0 });

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
}

void ToolUI::Update()
{
	float NumOne = -335.0;
	float Num = 61.0;
	if (true == GameEngineInput::GetInst()->IsDown("Num1"))
	{
		Select->SetPivot({NumOne, 0});
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num2"))
	{
		Select->SetPivot({ NumOne + Num * 1, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num3"))
	{
		Select->SetPivot({ NumOne + Num * 2, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num4"))
	{
		Select->SetPivot({ NumOne + Num * 3, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num5"))
	{
		Select->SetPivot({ NumOne + Num * 4, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num6"))
	{
		Select->SetPivot({ NumOne + Num * 5, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num7"))
	{
		Select->SetPivot({ NumOne + Num * 6, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num8"))
	{
		Select->SetPivot({ NumOne + Num * 7, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num9"))
	{
		Select->SetPivot({ NumOne + Num * 8, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num0"))
	{
		Select->SetPivot({ NumOne + Num * 9, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num-"))
	{
		Select->SetPivot({ NumOne + Num * 10, 0 });
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Num="))
	{
		Select->SetPivot({ NumOne + Num * 11, 0 });
	}


}