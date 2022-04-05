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


Player::Player()
	:Speed_(205.0f),
	 ColMap_(" ")
{
}

Player::~Player() 
{
}

void Player::SetMapScale(float _X, float _Y)
{
	MapScaleX_ = _X;
	MapScaleY_ = _Y;
}
void Player::SetColMapName(const std::string& _Name)
{
	ColMap_ = _Name;
}

void Player::ChangeState(PlayerState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case Idle:
			IdleStart();
			break;
		case Attack:
			AttackStart();
			break;
		case Move:
			MoveStart();
			break;
		default:
			break;
		}
	}

	CurState_ = _State;
}

void Player::StateUpdate()
{
	switch (CurState_)
	{
	case Idle:
		IdleUpdate();
		break;
	case Attack:
		AttackUpdate();
		break;
	case Move:
		MoveUpdate();
		break;
	default:
		break;
	}
}

void Player::Start()
{
	//defalut 값
	GameEngineRenderer* Body = CreateRendererToScale("Body.bmp", { 64, 128 });
	Body->SetIndex(0);
	GameEngineRenderer* Arm = CreateRendererToScale("Body.bmp", { 64, 128 });
	Arm->SetIndex(6);
	GameEngineRenderer* Hair = CreateRendererToScale("Hair.bmp", { 64, 128 },3, RenderPivot::CENTER, { 0,4 });
	Hair->SetIndex(101);
	GameEngineRenderer* Pants = CreateRendererToScale("Pants.bmp", { 64, 128 });
	Pants->SetIndex(0);
	GameEngineRenderer* Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 },5, RenderPivot::CENTER, { 0,16 });
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
	StateUpdate();
	CameraCheck();
	// 카메라 이동

}

void Player::Render()
{

}

void Player::CameraCheck()
{
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	float CameraRectX = 1280;
	float CameraRectY = 720;

	if (0 >= GetLevel()->GetCameraPos().x)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	if (0 >= GetLevel()->GetCameraPos().y)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	if (MapScaleX_ <= GetLevel()->GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = GetLevel()->GetCameraPos().x - (GetLevel()->GetCameraPos().x + CameraRectX - MapScaleX_);
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	if (MapScaleY_ <= (GetLevel()->GetCameraPos().y + CameraRectY))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = GetLevel()->GetCameraPos().y - (GetLevel()->GetCameraPos().y + CameraRectY - MapScaleY_);
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}

bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsDown("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsDown("MoveRight") &&
		false == GameEngineInput::GetInst()->IsDown("MoveUp") &&
		false == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		return false;
	}
	ChangeState(Move);
	return true;
}