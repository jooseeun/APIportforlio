#include "Player.h"
#include "BackGround.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>

void Player::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(PlayerState::Move);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (CurItemKind_ == PlayerHave::WieldItem)
		{
			ChangeState(Wield);
		}
		else if (CurItemKind_ == PlayerHave::HitItem)
		{
			ChangeState(Hit);
		}
		else if (CurItemKind_ == PlayerHave::EatItem)
		{
			ChangeState(Eat);
		}
		else if (CurItemKind_ == PlayerHave::ElseItem)
		{
			ChangeState(Idle);
		}
		else if (CurItemKind_ == PlayerHave::NoItem)
		{
			ChangeState(Idle);
		}
	}

}

void Player::WieldUpdate()
{
	if (true == Arm->IsEndAnimation())
	{
		ChangeState(Idle);
	}
	
}
void Player::HitUpdate()
{
	if (true == Arm->IsEndAnimation())
	{
		ChangeState(Idle);
	}
}

void Player::EatUpdate()
{

}

void Player::MoveUpdate()
{

	float4 NextPos;
	float4 CheckPos;
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("RightWalk"))
	{
		Move = float4::RIGHT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 32.0f,62.0f };
		CurDir_ = PlayerDir::Right;
		ChangeAni("RightWalk");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("LeftWalk"))
	{
		Move = float4::LEFT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ -32.0f,62.0f };
		CurDir_ = PlayerDir::Left;
		ChangeAni("LeftWalk");
	}


	else if (true == GameEngineInput::GetInst()->IsPress("BackWalk"))
	{
		Move = float4::UP;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,62.0f };
		CurDir_ = PlayerDir::Back;
		ChangeAni("BackWalk");
	}

	else if (true == GameEngineInput::GetInst()->IsPress("FrontWalk"))
	{
		Move = float4::DOWN;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,64.0f };
		CurDir_ = PlayerDir::Front;
		ChangeAni("FrontWalk");
	}

	{

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(255, 0, 0) != Color)
		{
			SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);
		}
		
		if (RGB(0, 255, 255) == Color)
		{
			GameEngine::GetInst().ChangeLevel(PreLevel_);
		}
		else if (RGB(0, 0, 255) == Color)
		{
			GameEngine::GetInst().ChangeLevel(NextLevel_);
		}
		else if (RGB(255, 255, 0) == Color)
		{
			GameEngine::GetInst().ChangeLevel(EntryLevel_);
		}
		else if (RGB(25, 25, 25) == Color)
		{
			GameEngine::GetInst().ChangeLevel("ForestLevel");
		}

	} 

	if (false == IsMoveKey())
	{
		ChangeState(Idle);
	}
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	ChangeAni(GetDirString() + "Idle");
}

void Player::WieldStart()
{
	ChangeAni(GetDirString() + "Wield");
}

void Player::HitStart()
{
	ChangeAni(GetDirString() + "Hit");
}

void Player::EatStart()
{

}

void Player::MoveStart()
{
	
}

std::string Player::GetDirString()
{
	if (CurDir_ == PlayerDir::Front)
	{
		return "Front";
	}
	else if (CurDir_ == PlayerDir::Back)
	{
		return "Back";
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		return "Left";
	}
	else if (CurDir_ == PlayerDir::Right)
	{
		return "Right";
	}
	return "";
}