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
	IsMoveKey();
	Is
}

void Player::WieldUpdate()
{

}

void Player::MoveUpdate()
{

	float4 NextPos;
	float4 CheckPos;
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("WalkRight"))
	{
		Move = float4::RIGHT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 32.0f,62.0f };
		CurDir_ = Right;
		ChangeAni("WalkRight");
	}
	if (true == GameEngineInput::GetInst()->IsPress("WalkLeft"))
	{
		Move = float4::LEFT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ -32.0f,62.0f };
		CurDir_ = Left;
		ChangeAni("WalkLeft");
	}


	if (true == GameEngineInput::GetInst()->IsPress("WalkUp"))
	{
		Move = float4::UP;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,62.0f };
		CurDir_ = Back;
		ChangeAni("WalkUp");
	}

	if (true == GameEngineInput::GetInst()->IsPress("WalkDown"))
	{
		Move = float4::DOWN;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,64.0f };
		CurDir_ = Front;
		ChangeAni("WalkDown");
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
	if (CurDir_ == Front)
	{
		ChangeAni("FrontIdle");
	}
	else if (CurDir_ == Back)
	{

		ChangeAni("BackIdle");
	}
	else if (CurDir_ == Left)
	{

		ChangeAni("LeftIdle");
	}
	else if (CurDir_ == Right)
	{

		ChangeAni("RightIdle");
	}
}

void Player::WieldStart()
{

}

void Player::MoveStart()
{
	
}

