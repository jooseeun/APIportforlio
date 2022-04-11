#include "Player.h"
#include "BackGround.h"

#include "ContentsEnums.h"
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
	 ColMap_(" "),
	CurDir_(PlayerDir::Front),
	PrevDir_(PlayerDir::Front),
	CurItemKind_(PlayerHave::WieldItem),
	CurState_(PlayerState::Idle),
	CurItem_(PlayerItem::AxItem)
{
	ArrAnimationName[static_cast<int>(PlayerState::Idle)] = "Idle";
	ArrAnimationName[static_cast<int>(PlayerState::Walk)] = "Walk";
	ArrAnimationName[static_cast<int>(PlayerState::Wield)] = "Wield";

	ArrCheckDir[static_cast<int>(PlayerDir::Left)] = float4{ -32.0f,62.0f };
	ArrCheckDir[static_cast<int>(PlayerDir::Right)] = float4{ 32.0f,62.0f };
	ArrCheckDir[static_cast<int>(PlayerDir::Back)] = float4{ 0.0f,62.0f };
	ArrCheckDir[static_cast<int>(PlayerDir::Front)] = float4{ 0.0f,64.0f };
}

Player::~Player() 
{
}

void Player::DirAnimationChange() 
{
	ChangeAni(GetDirString() + ArrAnimationName[static_cast<int>(CurState_)]);
}

void Player::ChangeState(PlayerState _State)
{
	DirKeyCheck();

	if (CurState_ != _State)
	{
		ChangeAni(GetDirString() + ArrAnimationName[static_cast<int>(_State)]);

		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Wield:
			WieldStart();
			break;
		case PlayerState::Hit:
			HitStart();
			break;
		case PlayerState::Walk:
			WalkStart();
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
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Wield:
		WieldUpdate();
		break;
	case PlayerState::Hit:
		HitUpdate();
		break;
	case PlayerState::Walk:
		WalkUpdate();
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

	int ShirtsNum = 0;
	Body = CreateRendererToScale("Body.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Pants = CreateRendererToScale("Body.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,16 });
	Arm = CreateRendererToScale("Body.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,2 });
	Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,4 });
	//Tool = CreateRendererToScale("Tools.bmp", { 56, 112 }, 15);

	////////////idle
	{ 
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
			Shirts->CreateAnimation("Shirts.bmp", "RightIdle", ShirtsNum + 16, ShirtsNum + 16, 0.15f, false);
		}
		{// 캐릭터 Left idle 상태
			Body->CreateAnimation("Body2.bmp", "LeftIdle", 47, 47, 0.15f, false);
			Arm->CreateAnimation("Body2.bmp", "LeftIdle", 41, 41, 0.15f, false);
			Pants->CreateAnimation("Body2.bmp", "LeftIdle", 29, 29, 0.15f, false);
			Hair->CreateAnimation("Hair2.bmp", "LeftIdle", 106, 106, 0.15f, false);
			Shirts->CreateAnimation("Shirts.bmp", "LeftIdle", ShirtsNum + 32, ShirtsNum + 32, 0.15f, false);
		}
		{// 캐릭터 Back idle 상태
			Body->CreateAnimation("Body.bmp", "BackIdle", 48, 48, 0.15f, false); // 24 한줄에
			Arm->CreateAnimation("Body.bmp", "BackIdle", 54, 54, 0.15f, false);
			Pants->CreateAnimation("Body.bmp", "BackIdle", 66, 66, 0.15f, false);
			Hair->CreateAnimation("Hair.bmp", "BackIdle", 117, 117, 0.15f, false);
			Shirts->CreateAnimation("Shirts.bmp", "BackIdle", ShirtsNum + 48, ShirtsNum + 48, 0.15f, false);
		}

	}
	////////////////move
	{
		{ // 캐릭터 아래로 걷는 모션
			Body->CreateAnimation("Body.bmp", "FrontWalk", 1, 2, 0.3f, true);
			Arm->CreateAnimation("Body.bmp", "FrontWalk", 7, 8, 0.3f, true);
			Pants->CreateAnimation("Body.bmp", "FrontWalk", 19, 20, 0.3f, true);
			Hair->CreateAnimation("Hair.bmp", "FrontWalk", 101, 101, 0.3f, true);
			Shirts->CreateAnimation("Shirts.bmp", "FrontWalk", ShirtsNum, ShirtsNum, 0.15f, true);
		}
		{ // 캐릭터 오른쪽으로 걷는 모션
			Body->CreateAnimation("Body.bmp", "RightWalk", 25, 26, 0.4f, true);
			Arm->CreateAnimation("Body.bmp", "RightWalk", 31, 32, 0.4f, true);
			Pants->CreateAnimation("Body.bmp", "RightWalk", 43, 44, 0.4f, true);
			Hair->CreateAnimation("Hair.bmp", "RightWalk", 109, 109, 0.4f, true);
			Shirts->CreateAnimation("Shirts.bmp", "RightWalk", ShirtsNum + 16, ShirtsNum + 16, 0.6f, true);
		}
		{ // 캐릭터 왼쪽으로 걷는 모션
			Body->CreateAnimation("Body2.bmp", "LeftWalk", 45, 46, 0.4f, true);
			Arm->CreateAnimation("Body2.bmp", "LeftWalk", 40, 41, 0.4f, true);
			Pants->CreateAnimation("Body2.bmp", "LeftWalk", 27, 28, 0.4f, true);
			Hair->CreateAnimation("Hair2.bmp", "LeftWalk", 106, 106, 0.4f, true);
			Shirts->CreateAnimation("Shirts.bmp", "LeftWalk", ShirtsNum + 32, ShirtsNum + 32, 0.6f, true);
		}
		{ // 캐릭터 위로 걷는 모션
			Body->CreateAnimation("Body.bmp", "BackWalk", 49, 50, 0.3f, true);
			Arm->CreateAnimation("Body.bmp", "BackWalk", 55, 56, 0.3f, true);
			Pants->CreateAnimation("Body.bmp", "BackWalk", 67, 68, 0.3f, true);
			Hair->CreateAnimation("Hair.bmp", "BackWalk", 117, 117, 0.3f, true);
			Shirts->CreateAnimation("Shirts.bmp", "BackWalk", ShirtsNum + 48, ShirtsNum + 48, 0.15f, true);
		}
	}
	//////////////////Wield
	//Left 수정 , 옷 수정
	{
		{ // 내려치는 방향 : 앞
			Body->CreateAnimation("Body.bmp", "FrontWield", 264, 268, 0.1f, true); // 24 한줄에
			Arm->CreateAnimation("Body.bmp", "FrontWield", 270, 274, 0.1f, true);
			Pants->CreateAnimation("Body.bmp", "FrontWield", 282, 287, 0.1f, true);
			Hair->CreateAnimation("Hair.bmp", "FrontWield", 101, 101, 0.1f, true);
			Shirts->CreateAnimation("Shirts.bmp", "FrontWield", ShirtsNum, ShirtsNum, 0.15f, true);
		}
		{ // 내려치는 방향 : 오른쪽
			Body->CreateAnimation("Body.bmp", "RightWield", 192, 196, 0.1f, true);
			Arm->CreateAnimation("Body.bmp", "RightWield", 198, 202, 0.1f, true);
			Pants->CreateAnimation("Body.bmp", "RightWield", 210, 214, 0.1f, true);
			Hair->CreateAnimation("Hair.bmp", "RightWield", 109, 109, 0.1f, true);
			Shirts->CreateAnimation("Shirts.bmp", "RightWield", ShirtsNum + 16, ShirtsNum + 16, 0.15f, true);
		}
		{ // 내려치는 방향 : 왼쪽
			Body->CreateAnimation("Body3.bmp", "LeftWield", 192, 196, 0.1f, true);
			Arm->CreateAnimation("Body3.bmp", "LeftWield", 198, 202, 0.1f, true);
			Pants->CreateAnimation("Body3.bmp", "LeftWield", 210, 214, 0.1f, true);
			Hair->CreateAnimation("Hair2.bmp", "LeftWield", 106, 106, 0.1f, true);
			Shirts->CreateAnimation("Shirts.bmp", "LeftWield", ShirtsNum + 32, ShirtsNum + 32, 0.15f, true);
		}
		{ // 내려치는 방향 : 뒤
			Body->CreateAnimation("Body.bmp", "BackWield", 242, 243, 0.3f, true);
			Arm->CreateAnimation("Body.bmp", "BackWield", 151, 153, 0.2f, true);
			Pants->CreateAnimation("Body.bmp", "BackWield", 260, 261, 0.3f, true);
			Hair->CreateAnimation("Hair.bmp", "BackWield", 117, 117, 0.3f, true);
			Shirts->CreateAnimation("Shirts.bmp", "BackWield", ShirtsNum + 48, ShirtsNum + 48, 0.15f, true);
		}
	}
	////////////////////Hit
	// Left 수정, 옷 수정
	{
		{ // 때리는 방향 : 앞
			Body->CreateAnimation("Body.bmp", "FrontHit", 96, 101, 0.05f, true); // 24 한줄에
			Arm->CreateAnimation("Body.bmp", "FrontHit", 108, 113, 0.05f, true);
			Pants->CreateAnimation("Body.bmp", "FrontHit", 114, 119, 0.05f, true);
			Hair->CreateAnimation("Hair.bmp", "FrontHit", 101, 101, 0.15f, true);
			Shirts->CreateAnimation("Shirts.bmp", "FrontHit", ShirtsNum, ShirtsNum, 0.15f, true);
		}
		{ // 때리는 방향  : 오른쪽
			Body->CreateAnimation("Body.bmp", "RightHit", 120, 125, 0.05f, true);
			Arm->CreateAnimation("Body.bmp", "RightHit", 132, 137, 0.05f, true);
			Pants->CreateAnimation("Body.bmp", "RightHit", 138, 143, 0.05f, true);
			Hair->CreateAnimation("Hair.bmp", "RightHit", 109, 109, 0.15f, true);
			Shirts->CreateAnimation("Shirts.bmp", "RightHit", ShirtsNum + 16, ShirtsNum + 16, 0.15f, true);
		}
		{ // 때리는 방향  : 왼쪽
			Body->CreateAnimation("Body3.bmp", "LeftHit", 120, 125, 0.05f, true);
			Arm->CreateAnimation("Body3.bmp", "LeftHit", 132, 137, 0.05f, true);
			Pants->CreateAnimation("Body3.bmp", "LeftHit", 138, 143, 0.05f, true);
			Hair->CreateAnimation("Hair2.bmp", "LeftHit", 106, 106, 0.15f, true);
			Shirts->CreateAnimation("Shirts.bmp", "LeftHit", ShirtsNum + 32, ShirtsNum + 32, 0.15f, true);
		}
		{ // 때리는 방향  : 뒤
			Body->CreateAnimation("Body.bmp", "BackHit", 144, 149, 0.05f, true);
			Arm->CreateAnimation("Body.bmp", "BackHit", 156, 161, 0.05f, true);
			Pants->CreateAnimation("Body.bmp", "BackHit", 162, 167, 0.05f, true);
			Hair->CreateAnimation("Hair.bmp", "BackHit", 117, 117, 0.15f, true);
			Shirts->CreateAnimation("Shirts.bmp", "BackHit", ShirtsNum + 48, ShirtsNum + 48, 0.15f, true);
		}
	}

	///////////////////Craft
	{
		
	}
	ChangeAni("FrontIdle");
	if (false == GameEngineInput::GetInst()->IsKey("LeftWalk"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftWalk", 'A');
		GameEngineInput::GetInst()->CreateKey("RightWalk", 'D');
		GameEngineInput::GetInst()->CreateKey("BackWalk", 'W');
		GameEngineInput::GetInst()->CreateKey("FrontWalk", 'S');
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);
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

bool Player::DirKeyCheck() 
{

	if (true == GameEngineInput::GetInst()->IsPress("LeftWalk")) 
	{
		CurDir_ = PlayerDir::Left;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("RightWalk"))
	{
		CurDir_ = PlayerDir::Right;
	}

	if (true == GameEngineInput::GetInst()->IsPress("FrontWalk"))
	{
		CurDir_ = PlayerDir::Front;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("BackWalk"))
	{
		CurDir_ = PlayerDir::Back;
	}

	if (PrevDir_ != CurDir_)
	{
		PrevDir_ = CurDir_;
		DirAnimationChange();
		return true;
	}

	return false;
}

// 좋은 함수가 아닌거 같습니다.
bool Player::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsDown("LeftWalk") &&
		false == GameEngineInput::GetInst()->IsDown("RightWalk") &&
		false == GameEngineInput::GetInst()->IsDown("BackWalk") &&
		false == GameEngineInput::GetInst()->IsDown("FrontWalk"))
	{
		if (CurState_ == PlayerState::Idle)
		{
			return false;

		}
		
	}
	if (true == GameEngineInput::GetInst()->IsFree("LeftWalk") &&
		true == GameEngineInput::GetInst()->IsFree("RightWalk") &&
		true == GameEngineInput::GetInst()->IsFree("BackWalk") &&
		true == GameEngineInput::GetInst()->IsFree("FrontWalk"))
	{
		return false;
	}
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

