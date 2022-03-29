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
	//defalut 값
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

	//{ // 캐릭터 아래로 걷는 모션
	//	GameEngineRenderer* BodyDown = CreateRenderer();
	//	BodyDown->CreateAnimation("Body.bmp", "PlayerWalkDownLag", 1, 2, 0.15f, true);
	//	BodyDown->ChangeAnimation("PlayerWalkDownLag");
	//	GameEngineRenderer* ArmDown = CreateRenderer();
	//	ArmDown->CreateAnimation("Body.bmp", "PlayerWalkDownArm", 7, 8, 0.15f, true);
	//	ArmDown->ChangeAnimation("PlayerWalkDownArm");
	//	GameEngineRenderer* Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,9 });
	//	Hair->SetIndex(101);
	//	GameEngineRenderer* PantsDown = CreateRenderer();
	//	PantsDown->CreateAnimation("Pants.bmp", "PlayerWalkDownPants", 1, 2, 0.15f, true);
	//	PantsDown->ChangeAnimation("PlayerWalkDownPants");
	//	GameEngineRenderer* Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
	//	Shirts->SetIndex(387);
	//}
	// 
	//{ // 캐릭터 오른쪽으로 걷는 모션
	//	GameEngineRenderer* BodyRight = CreateRenderer();
	//	BodyRight->CreateAnimation("Body.bmp", "PlayerWalkRightLag", 19, 20, 0.15f, true);
	//	BodyRight->ChangeAnimation("PlayerWalkRightLag");
	//	GameEngineRenderer* ShirtsRight = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
	//	ShirtsRight->SetIndex(419);
	//	GameEngineRenderer* ArmRight = CreateRenderer();
	//	ArmRight->CreateAnimation("Body.bmp", "PlayerWalkRightArm", 25, 26, 0.15f, true);
	//	ArmRight->ChangeAnimation("PlayerWalkRightArm");
	//	GameEngineRenderer* HairRight = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,9 });
	//	HairRight->SetIndex(109);
	//	GameEngineRenderer* PantsDown = CreateRenderer();
	//	PantsDown->CreateAnimation("Pants.bmp", "PlayerWalkDownPants", 121, 122, 0.15f, true);
	//	PantsDown->ChangeAnimation("PlayerWalkDownPants");
	//}
	
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

		{ // 캐릭터 아래로 걷는 모션
			GameEngineRenderer* BodyDown = CreateRenderer();
			BodyDown->CreateAnimation("Body.bmp", "PlayerWalkDownLag", 1, 2, 0.3f, true);
			BodyDown->ChangeAnimation("PlayerWalkDownLag");
			GameEngineRenderer* ArmDown = CreateRenderer();
			ArmDown->CreateAnimation("Body.bmp", "PlayerWalkDownArm", 7, 8, 0.3f, true);
			ArmDown->ChangeAnimation("PlayerWalkDownArm");
			GameEngineRenderer* Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,9 });
			Hair->SetIndex(101);
			GameEngineRenderer* Pants = CreateRendererToScale("Pants.bmp", { 64, 128 });
			Pants->SetIndex(0);
			GameEngineRenderer* Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
			Shirts->SetIndex(387);
		}
	}



}
void Player::Render()
{

}