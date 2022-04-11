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
		ChangeState(PlayerState::Walk);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		if (CurItemKind_ == PlayerHave::WieldItem)
		{
			ChangeState(PlayerState::Wield);
		}
		else if (CurItemKind_ == PlayerHave::HitItem)
		{
			ChangeState(PlayerState::Hit);
		}
		else if (CurItemKind_ == PlayerHave::EatItem)
		{
			ChangeState(PlayerState::Eat);
		}
		else if (CurItemKind_ == PlayerHave::ElseItem)
		{
			ChangeState(PlayerState::Idle);
		}
		else if (CurItemKind_ == PlayerHave::NoItem)
		{
			ChangeState(PlayerState::Idle);
		}
	}

}

void Player::WieldUpdate()
{
	if (true == Arm->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
	
}
void Player::HitUpdate()
{
	if (true == Arm->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::EatUpdate()
{

}

void Player::WalkUpdate()
{
	DirKeyCheck();

	float4 NextPos;
	float4 CheckPos = ArrCheckDir[static_cast<int>(CurDir_)];
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("RightWalk"))
	{
		Move += float4::RIGHT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("LeftWalk"))
	{
		Move += float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("BackWalk"))
	{
		Move += float4::UP;
	}

	else if (true == GameEngineInput::GetInst()->IsPress("FrontWalk"))
	{
		Move += float4::DOWN;
	}

	Move.Normal2D();
	NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos += NextPos;

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
		ChangeState(PlayerState::Idle);
	}
}


//////////////////////////////////////// State

void Player::IdleStart()
{
}

void Player::WieldStart()
{
}

void Player::HitStart()
{
}

void Player::EatStart()
{

}

void Player::WalkStart()
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