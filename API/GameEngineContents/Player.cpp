#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>

Player::Player() 
	:Speed_(90.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		// 이때 대문자여야 합니다.
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Fire", VK_SPACE);
		// VK_LBUTTON;
	}

}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		// 1.0F * 0.001101F
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}


	// 내가 키를 눌렀다면 움직여라.
	//if (0 != GetAsyncKeyState('A'))
	//{
	//	int a = 0;
	//}

}
void Player::Render()
{
	DebugRectRender();
}