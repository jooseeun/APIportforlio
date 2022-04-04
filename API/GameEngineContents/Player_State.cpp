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
}

void Player::AttackUpdate()
{

}

void Player::MoveUpdate()
{

	MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmHouse.bmp");
	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	float4 NextPos;
	float4 CheckPos;
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Move = float4::RIGHT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 32.0f,0.0f };
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		Move = float4::LEFT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ -32.0f,0.0f };
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		Move = float4::UP;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,-64.0f };
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Move = float4::DOWN;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,64.0f };

	}

	{

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(255, 0, 0) != Color)
		{
			SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);
		}
		if (RGB(0, 0, 255) == Color)
		{
			GameEngine::GetInst().ChangeLevel("FarmLevel");
		}

	} // 맵충돌


}


//////////////////////////////////////// State

void Player::IdleStart()
{
	// 애니메이션이 바뀐다.

	// AnimationName = "Idle_"
}

void Player::AttackStart()
{

}

void Player::MoveStart()
{

}

