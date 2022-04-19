#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>


Mouse::Mouse() 
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	ShowCursor(false);
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	GameEngineRenderer* Renderer = CreateRenderer("Mouse.bmp");
	Renderer->CameraEffectOff();
	MouseCol_ = CreateCollision("MouseCol", { 16,20 }, { -8,-10 });

	if (false == GameEngineInput::GetInst()->IsKey("LeftMouse"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);
	}
}

void Mouse::Update()
{
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	CheckPlayerIsLeftMouse();

	if ("TitleLevel" == GetLevel()->GetNameCopy()&& true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (true == GetMouseCol()->CollisionCheck("StartCol", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
		}

		else if (true == GetMouseCol()->CollisionCheck("ExitCol", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
		}
	}
}

void Mouse::CheckPlayerIsLeftMouse()
{
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{

		if (true == GetMouseCol()->CollisionCheck("Num1Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(1);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num2Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(2);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num3Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(3);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num4Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(4);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num5Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(5);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num6Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(6);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num7Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(7);
		}

		else if (true == GetMouseCol()->CollisionCheck("Num8Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(8);
		}
		else if (true == GetMouseCol()->CollisionCheck("Num9Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(9);
		}
		else if (true == GetMouseCol()->CollisionCheck("Num10Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(10);
		}
		else if (true == GetMouseCol()->CollisionCheck("Num11Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(11);
		}
		else if (true == GetMouseCol()->CollisionCheck("Num12Col", CollisionType::Rect, CollisionType::Rect))
		{
			ToolUI::ToolUISet->SetSelectPivot(12);
		}

		else
		{
			if ("TitleLevel" != Player::MainPlayer->GetLevel()->GetNameCopy())
			{
				Player::MainPlayer->SetIsLeftMouseON();
			}
		}
	}
	
}

