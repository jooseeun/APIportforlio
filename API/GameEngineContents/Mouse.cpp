#include "Mouse.h"
#include "Player.h"
#include "ToolUI.h"
#include "Tool.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineCollision.h>


Mouse::Mouse() 
	:IsOpenShop_(false)
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
	MouseCol_->CameraEffectOff();
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


	if ("TitleLevel" == GetLevel()->GetNameCopy()&& true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		if (true == GetMouseCol()->CollisionCheck("StartCol", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
		}

		else if (true == GetMouseCol()->CollisionCheck("ExitCol", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngineWindow::GetInst().Off();
		}
	}
}

void Mouse::CheckPlayerIsLeftMouse()
{
	if ("TitleLevel" == GetLevel()->GetNameCopy())
	{
		return;
	}

	static float Time_ = 1.0f;
	if (0 <= Time_)
	{
		Time_ -= GameEngineTime::GetDeltaTime();
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		if (true == GetMouseCol()->NextPosCollisionCheck("SeedShopNPC",GetLevel()->GetCameraPos(), CollisionType::Rect, CollisionType::Rect))//카메라 이펙트 꺼져있는건 이렇게 충돌체크해야됨
		{
			if (GetLevel()->GetNameCopy() == "SeedShopLevel")
			{
				IsOpenShop_ = true; 
			}

			return;
		}

		if (true == GetMouseCol()->CollisionCheck("ShopExit", CollisionType::Rect, CollisionType::Rect))
		{
			if (GetLevel()->GetNameCopy() == "SeedShopLevel")
			{
				IsOpenShop_ = false;
			}

			return;
		}
	}

	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		if (false == ToolUI::ToolUISet->GetIsInventory())
		{
			if (true == GetMouseCol()->CollisionCheck("Num1Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(0);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num2Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(1);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num3Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(2);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num4Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(3);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num5Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(4);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num6Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(5);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num7Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(6);
			}

			else if (true == GetMouseCol()->CollisionCheck("Num8Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(7);
			}
			else if (true == GetMouseCol()->CollisionCheck("Num9Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(8);
			}
			else if (true == GetMouseCol()->CollisionCheck("Num10Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(9);
			}
			else if (true == GetMouseCol()->CollisionCheck("Num11Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(10);
			}
			else if (true == GetMouseCol()->CollisionCheck("Num12Col", CollisionType::Rect, CollisionType::Rect))
			{
				ToolUI::ToolUISet->SetSelectPivot(11);
			}
			else
			{
				if ("TitleLevel" != Player::MainPlayer->GetLevel()->GetNameCopy())
				{
					Player::MainPlayer->SetIsLeftMouseON();
				}
			}
		}

		if (true == ToolUI::ToolUISet->GetIsInventory() || true == Tool::ToolSet->IsShopCheck())
		{
			if (true == GetMouseCol()->CollisionCheck("Inven1Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(0);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven2Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(1);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven3Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(2);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven4Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(3);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven5Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(4);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven6Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(5);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven7Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(6);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven8Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(7);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven9Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(8);
			} 
			else if (true == GetMouseCol()->CollisionCheck("Inven10Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(9);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven11Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(10);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven12Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(11);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven13Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(12);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven14Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(13);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven15Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(14);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven16Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(15);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven17Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(16);
			}

			else if (true == GetMouseCol()->CollisionCheck("Inven18Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(17);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven19Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(18);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven20Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(19);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven21Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(20);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven22Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(21);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven23Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(22);
			}
			else if (true == GetMouseCol()->CollisionCheck("Inven24Col", CollisionType::Rect, CollisionType::Rect))
			{
				Tool::ToolSet->SetClickItem(23);
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
	
}
