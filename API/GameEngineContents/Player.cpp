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
	case Wield:
		WieldUpdate();
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
	int ShirtsNum = 259;
	Body = CreateRendererToScale("Body.bmp", { 64, 128 }, 10);
	Pants = CreateRendererToScale("Body.bmp", { 64, 128 }, 11);
	Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, 12, RenderPivot::CENTER, { 0,16 });
	Arm = CreateRendererToScale("Body.bmp", { 64, 128 }, 13, RenderPivot::CENTER, { 0,2 });
	Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, 14, RenderPivot::CENTER, { 0,4 });

	{// 캐릭터 front idle 상태
		Body->CreateAnimation("Body.bmp", "FrontIdle", 0, 0, 0.15f, false); // 24 한줄에
		Arm->CreateAnimation("Body.bmp", "FrontIdle", 6, 6, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "FrontIdle", 18, 18, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "FrontIdle", 101, 101, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "FrontIdle", ShirtsNum, ShirtsNum, 0.15f, false);
	}
	{// 캐릭터 right idle 상태
		Body->CreateAnimation("Body.bmp", "RightIdle", 24, 24, 0.15f, false);//+24
		Arm->CreateAnimation("Body.bmp", "RightIdle", 30, 30, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "RightIdle", 42, 42, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "RightIdle", 109, 109, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "RightIdle", ShirtsNum+16, ShirtsNum+16, 0.15f, false);
	}	
	{// 캐릭터 Left idle 상태
		Body->CreateAnimation("Body2.bmp", "LeftIdle", 47, 47, 0.15f, false);
		Arm->CreateAnimation("Body2.bmp", "LeftIdle", 41, 41, 0.15f, false);
		Pants->CreateAnimation("Body2.bmp", "LeftIdle", 29, 29, 0.15f, false);
		Hair->CreateAnimation("Hair2.bmp", "LeftIdle", 106, 106, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "LeftIdle", ShirtsNum+32, ShirtsNum+32, 0.15f, false);
	}
	{// 캐릭터 Back idle 상태
		Body->CreateAnimation("Body.bmp", "BackIdle", 48, 48, 0.15f, false); // 24 한줄에
		Arm->CreateAnimation("Body.bmp", "BackIdle", 54, 54, 0.15f, false);
		Pants->CreateAnimation("Body.bmp", "BackIdle", 66, 66, 0.15f, false);
		Hair->CreateAnimation("Hair.bmp", "BackIdle", 117, 117, 0.15f, false);
		Shirts->CreateAnimation("Shirts.bmp", "BackIdle", ShirtsNum+48, ShirtsNum+48, 0.15f, false);
	}
	{ // 캐릭터 아래로 걷는 모션
		Body->CreateAnimation("Body.bmp", "WalkDown", 1, 2, 0.3f, true);
		Arm->CreateAnimation("Body.bmp", "WalkDown", 7, 8, 0.3f, true);
		Pants->CreateAnimation("Body.bmp", "WalkDown", 19, 20, 0.3f, true);
		Hair->CreateAnimation("Hair.bmp", "WalkDown", 101, 101, 0.3f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkDown", ShirtsNum, ShirtsNum, 0.15f, true);
	}
	{ // 캐릭터 오른쪽으로 걷는 모션
		Body->CreateAnimation("Body.bmp", "WalkRight", 25, 26, 0.4f, true);
		Arm->CreateAnimation("Body.bmp", "WalkRight", 31, 32, 0.4f, true);
		Pants->CreateAnimation("Body.bmp", "WalkRight", 43, 44, 0.4f, true);
		Hair->CreateAnimation("Hair.bmp", "WalkRight", 109, 109, 0.4f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkRight", ShirtsNum + 16, ShirtsNum + 16, 0.6f, true);
	}
	{ // 캐릭터 왼쪽으로 걷는 모션
		Body->CreateAnimation("Body2.bmp", "WalkLeft", 45, 46, 0.4f, true);
		Arm->CreateAnimation("Body2.bmp", "WalkLeft", 40, 41, 0.4f, true);
		Pants->CreateAnimation("Body2.bmp", "WalkLeft", 27, 28, 0.4f, true);
		Hair->CreateAnimation("Hair2.bmp", "WalkLeft", 106, 106, 0.4f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkLeft", ShirtsNum + 32, ShirtsNum + 32, 0.6f, true);
	}
	{ // 캐릭터 위로 걷는 모션
		Body->CreateAnimation("Body.bmp", "WalkUp", 49, 50, 0.3f, true);
		Arm->CreateAnimation("Body.bmp", "WalkUp", 55, 56, 0.3f, true);
		Pants->CreateAnimation("Body.bmp", "WalkUp", 67, 68, 0.3f, true);
		Hair->CreateAnimation("Hair.bmp", "WalkUp", 117, 117, 0.3f, true);
		Shirts->CreateAnimation("Shirts.bmp", "WalkUp", ShirtsNum + 48, ShirtsNum + 48, 0.15f, true);
	}

	
	ChangeAni("FrontIdle");

	if (false == GameEngineInput::GetInst()->IsKey("WalkLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("WalkLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("WalkRight", 'D');
		GameEngineInput::GetInst()->CreateKey("WalkUp", 'W');
		GameEngineInput::GetInst()->CreateKey("WalkDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Wield", VK_LBUTTON);
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
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}
}
void Player::SetSideLevel(std::string _Pre, std::string _Next, std::string _Entry)
{
	NextLevel_ = _Next;
	PreLevel_ = _Pre;
	EntryLevel_ = _Entry;

}