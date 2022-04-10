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
#include <GameEngine/GameEngineCollision.h>

Player::Player()
	:Speed_(205.0f),
	 ColMap_(" ")
{
	
}

Player::~Player() 
{
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
void Player::ChangeAni(std::string _Name)
{
	Body->ChangeAnimation(_Name);
	Arm->ChangeAnimation(_Name);
	Pants->ChangeAnimation(_Name);
	Shirts->ChangeAnimation(_Name);
	Hair->ChangeAnimation(_Name);

}
void Player::Start()
{
	Body = CreateRendererToScale("Body.bmp", { 64, 128 }, 10);
	Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, 11, RenderPivot::CENTER, { 0,4 });
	Pants = CreateRendererToScale("Body.bmp", { 64, 128 }, 12);
	Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, 14, RenderPivot::CENTER, { 0,16 });
	Arm = CreateRendererToScale("Body.bmp", { 64, 128 }, 13, RenderPivot::CENTER, { 0,2 });

	//PlayerCollision = CreateCollision("PlayerCol", {64, 128});
	//defalut ��
	{
		Body->CreateAnimation("Body.bmp", "FrontIdle", 0, 0, 0.15f, false); // 24 ���ٿ�
		Arm->CreateAnimation("Body.bmp", "FrontIdle", 6, 6, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "FrontIdle", 18, 18, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "FrontIdle", 101, 101, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "FrontIdle", 387, 387, 0.15f, false);
	}
	{
		Body->CreateAnimation("Body.bmp", "BackIdle", 48, 48, 0.15f, false); // 24 ���ٿ�
		Arm->CreateAnimation("Body.bmp", "BackIdle", 54, 54, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "BackIdle", 66, 66, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "BackIdle", 117, 117, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "BackIdle", 483, 483, 0.15f, false);
	}
	
	{
		Body->CreateAnimation("Body.bmp", "LeftIdle", 0, 0, 0.15f, false);
		Arm->CreateAnimation("Body.bmp", "LeftIdle", 6, 6, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "LeftIdle", 14, 14, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "LeftIdle", 101, 101, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "LeftIdle", 387, 387, 0.15f, false);
	}
	{
		Body->CreateAnimation("Body.bmp", "RightIdle", 24, 24, 0.15f, false);//+24
		Arm->CreateAnimation("Body.bmp", "RightIdle", 30, 30, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "RightIdle", 42, 42, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "RightIdle", 109, 109, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "RightIdle", 419, 419, 0.15f, false);
	}
	{ // ĳ���� �Ʒ��� �ȴ� ���
		Body->CreateAnimation("Body.bmp", "WalkDown", 1, 2, 0.15f, true);
		Arm->CreateAnimation("Body.bmp", "WalkDown", 7, 8, 0.15f, true);
		Pants->CreateAnimation("Body.bmp", "WalkDown", 19, 20, 0.15f, true);
		Hair->CreateAnimation("Hair.bmp", "WalkDown", 101, 101, 0.15f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkDown", 387, 387, 0.15f, true);
		//GameEngineRenderer* HairDown = CreateRendererToScale("Hair.bmp", { 64, 128 }, 3,RenderPivot::CENTER, { 0,9 });
		//HairDown->SetIndex(101);
		//Shirts->SetIndex(387);
		
	}
	{ // ĳ���� ���� �ȴ� ���
		Body->CreateAnimation("Body.bmp", "WalkUp", 49, 50, 0.15f, true);
		Arm->CreateAnimation("Body.bmp", "WalkUp", 55, 56, 0.15f, true);
		Pants->CreateAnimation("Body.bmp", "WalkUp", 67, 68, 0.15f, true);
		Hair->CreateAnimation("Hair.bmp", "WalkUp", 117, 117, 0.15f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkUp", 483, 483, 0.15f, true);
	}
	{ // ĳ���� ���������� �ȴ� ���
		Body->CreateAnimation("Body.bmp", "WalkRight", 25, 26, 0.6f, true);
		Arm->CreateAnimation("Body.bmp", "WalkRight", 31, 32, 0.6f, true);
		Pants->CreateAnimation("Body.bmp", "WalkRight", 43, 44, 0.6f, true);
		Hair->CreateAnimation("Hair.bmp", "WalkRight", 109, 109, 0.6f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkRight", 419, 419, 0.6f, true);
	}
	{ // ĳ���� �������� �ȴ� ���
		Body->CreateAnimation("Body2.bmp", "WalkLeft", 33, 34, 0.6f, true);
		Pants->CreateAnimation("Body.bmp", "WalkLeft", 121, 122, 0.6f, true);
		Arm->CreateAnimation("Body2.bmp", "WalkLeft", 27, 29, 0.6f, true);
		Hair->CreateAnimation("Hair2.bmp", "WalkLeft", 109, 109, 0.6f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkLeft", 451, 451, 0.6f, true);
	}


	ChangeAni("FrontIdle");

	if (false == GameEngineInput::GetInst()->IsKey("WalkLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("WalkLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("WalkRight", 'D');
		GameEngineInput::GetInst()->CreateKey("WalkUp", 'W');
		GameEngineInput::GetInst()->CreateKey("WalkDown", 'S');

	}

}

void Player::Update()
{
	StateUpdate();
	CameraCheck();
	// ī�޶� �̵�

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
	if (false == GameEngineInput::GetInst()->IsDown("WalkLeft") &&
		false == GameEngineInput::GetInst()->IsDown("WalkRight") &&
		false == GameEngineInput::GetInst()->IsDown("WalkUp") &&
		false == GameEngineInput::GetInst()->IsDown("WalkDown"))
	{
		if (CurState_ == Idle)
		{
			return false;

		}
		
	}
	if (true == GameEngineInput::GetInst()->IsFree("WalkLeft") &&
		true == GameEngineInput::GetInst()->IsFree("WalkRight") &&
		true == GameEngineInput::GetInst()->IsFree("WalkUp") &&
		true == GameEngineInput::GetInst()->IsFree("WalkDown"))
	{
		return false;
	}
	ChangeState(Move);
	return true;
}

void Player::SetMapScale(float _X, float _Y)
{
	MapScaleX_ = _X;
	MapScaleY_ = _Y;
}

void Player::SetColMapName(const std::string& _Name)
{
	ColMap_ = _Name;
	MapColImage_ = GameEngineImageManager::GetInst()->Find(ColMap_);
	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}
}
void Player::SetSideLevel(std::string _Pre, std::string _Next, std::string _Entry)
{
	NextLevel_ = _Next;
	PreLevel_ = _Pre;
	EntryLevel_ = _Entry;

}