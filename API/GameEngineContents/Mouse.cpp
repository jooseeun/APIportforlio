#include "Mouse.h"
#include "Player.h"
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
	//ShowCursor(false);
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
}

void Mouse::CheckPlayerIsLeftMouse()
{
	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (true == GetMouseCol()->CollisionCheck("StartCol", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
		}

		else if (true == GetMouseCol()->CollisionCheck("ExitCol", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
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

