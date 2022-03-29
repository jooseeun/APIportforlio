#include "Player.h"
#include "BackGround.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>


Player::Player()
	:Speed_(125.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{	

	SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* Body = CreateRendererToScale("Body.bmp", { 64, 128 });
	Body->SetIndex(0);
	GameEngineRenderer* Arm = CreateRendererToScale("Body.bmp", { 64, 128 });
	Arm->SetIndex(6);
	GameEngineRenderer* Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,4 });
	Hair->SetIndex(101);
	GameEngineRenderer* Pants = CreateRendererToScale("Pants.bmp", { 64, 128 });
	Pants->SetIndex(0);
	GameEngineRenderer* Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
	Shirts->SetIndex(387);

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');

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



}
void Player::Render()
{

}