#include "Player.h"
#include "BackGround.h"
#include "ContentsEnums.h"
#include "Tool.h"
#include "DropItem.h"
#include "TileAnimation.h"
#include "Mine1Object.h"
#include "Mine2Object.h"
#include "HealthUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>


Player* Player::MainPlayer = nullptr;

Player::Player()
	:Speed_(250.0f),
	IsLeftMouse(false),
	ColMap_(" "),
	CurDir_(PlayerDir::Front),
	PrevDir_(PlayerDir::Front),
	CurItemKind_(PlayerItemKind::WieldItem),
	CurState_(PlayerState::Idle),
	CurItem_(PlayerItem::HoeItem),
	CurHairStyle_(PlayerHairStyle::First),
	CurHairColor_(PlayerHairColor::Black),
	CurShirts_(PlayerShirts::First),
	CurPants_(PlayerPants::First),
	CurDay_(1),
	CurHour_(0),
	CropNum_(0),
	MineTileMap_(nullptr),
	CropsTileMap_(nullptr),
	GroundTileMap_(nullptr),
	IsHit_(false),
	IsCreate_(false)
{

	ArrAnimationName[static_cast<int>(PlayerState::Idle)] = "Idle";
	ArrAnimationName[static_cast<int>(PlayerState::Walk)] = "Walk";
	ArrAnimationName[static_cast<int>(PlayerState::Wield)] = "Wield";
	ArrAnimationName[static_cast<int>(PlayerState::Hit)] = "Hit";
	ArrAnimationName[static_cast<int>(PlayerState::Water)] = "Water";
	ArrAnimationName[static_cast<int>(PlayerState::Seed)] = "Idle";
	ArrAnimationName[static_cast<int>(PlayerState::Harvest)] = "Hit"; // 낫으로 수확하게 하도록 했기 때문에 

	ArrCheckDir[static_cast<int>(PlayerDir::Front)] = float4{ 0.0f,64.0f };
	ArrCheckDir[static_cast<int>(PlayerDir::Right)] = float4{ 32.0f,62.0f };
	ArrCheckDir[static_cast<int>(PlayerDir::Left)] = float4{ -32.0f,62.0f };
	ArrCheckDir[static_cast<int>(PlayerDir::Back)] = float4{ 0.0f,62.0f };


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
		CurState_ = _State;
		ChangeAni(GetDirString() + ArrAnimationName[static_cast<int>(CurState_)]);

		switch (CurState_)
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
		case PlayerState::Water:
			WaterStart();
			break;
		case PlayerState::Seed:
			SeedStart();
			break;
		case PlayerState::Harvest:
			HarvestStart();
			break;
		default:
			break;
		}
	}

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
	case PlayerState::Water:
		WaterUpdate();
		break;
	case PlayerState::Seed:
		SeedUpdate();
		break;
	case PlayerState::Harvest:
		HarvestUpdate();
		break;
	default:
		break;
	}
}
void Player::Update()
{
	if (IsCreate_ == false)
	{
		Create();
		IsCreate_ = true;
	}
	StateUpdate();
	IsDebugModeONOFF();
	CropsGrowUpdate();
	MonsterCheck();
	CameraCheck();
}



void Player::Render()
{

}

void Player::CameraCheck() /// BusStopLevel  카메라 흔들림 문제..
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
	else if (MapScaleX_ <= GetLevel()->GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		CurCameraPos.x = static_cast<int>(GetLevel()->GetCameraPos().ix() - (GetLevel()->GetCameraPos().ix() + CameraRectX - MapScaleX_));
		GetLevel()->SetCameraPos(CurCameraPos);
	}


	if (0 >= GetLevel()->GetCameraPos().y)
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}



	else if (MapScaleY_ <= (GetLevel()->GetCameraPos().y + CameraRectY))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = static_cast<int>(GetLevel()->GetCameraPos().iy() - (GetLevel()->GetCameraPos().iy() + CameraRectY - MapScaleY_));
		GetLevel()->SetCameraPos(CurCameraPos);
	}



}
void Player::ChangeAni(std::string _Name)
{
	std::string Item_ = GetItemString();

	if (PlayerState::Wield == CurState_)
	{
		if (PlayerDir::Back == CurDir_)
		{
			BackItem_->ChangeAnimation(GetDirString() + Item_);

		}
		else
		{
			WieldItem_->ChangeAnimation(GetDirString() + Item_);

		}
	}
	else if (PlayerState::Water == CurState_)
	{
		if (PlayerDir::Back == CurDir_)
		{
			BackItem_->ChangeAnimation(GetDirString() + Item_);
		}
		else
		{
			WaterItem_->ChangeAnimation(GetDirString() + Item_);
		}
	}
	else if (PlayerState::Hit == CurState_ || PlayerState::Harvest == CurState_)
	{
		if (PlayerDir::Back == CurDir_)
		{
			BackItem_->ChangeAnimation(GetDirString() + Item_);
		}
		else
		{
			HitItem_->ChangeAnimation(GetDirString() + Item_);
		}
	}
	else
	{
		BackItem_->ChangeAnimation("ItemIdle");
		WieldItem_->ChangeAnimation("ItemIdle");
		WaterItem_->ChangeAnimation("ItemIdle");
		HitItem_->ChangeAnimation("ItemIdle");
	}
	Body_->ChangeAnimation(_Name);
	Arm_->ChangeAnimation(_Name);
	Pants_->ChangeAnimation(_Name);
	Shirts_->ChangeAnimation(_Name);
	Hair_->ChangeAnimation(_Name);
}
void Player::Create()
{
	std::string HairColor_ = GetHairColorString();
	std::string HairStyle_ = GetHairStyleString();
	std::string ShirtsStyle_ = GetShirtsStyleString();
	std::string PantsStyle_ = GetPantsStyleString();


	////////////idle
	{
		{// 캐릭터 front idle 상태
			Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontIdle", 0, 0, 0.15f, false); // 24 한줄에
			Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontIdle", 6, 6, 0.15f, false);
			Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "FrontIdle", 0, 0, 0.15f, false);
			Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "FrontIdle", 0, 0, 0.15f, false);
			Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "FrontIdle", 0, 0, 0.15f, false);
		}
		{// 캐릭터 right idle 상태
			Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightIdle", 24, 24, 0.15f, false);//+24
			Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightIdle", 30, 30, 0.15f, false);
			Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "RightIdle", 24, 24, 0.15f, false);
			Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "RightIdle", 24, 24, 0.15f, false);
			Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "RightIdle", 24, 24, 0.15f, false);//+24
		}
		{// 캐릭터 Left idle 상태
			Body_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftIdle", 24, 24, 0.15f, false);
			Arm_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftIdle", 30, 30, 0.15f, false);
			Pants_->CreateAnimation("PantsL" + PantsStyle_ + ".bmp", "LeftIdle", 24, 24, 0.15f, false);
			Hair_->CreateAnimation("HairL" + HairStyle_ + HairColor_ + ".bmp", "LeftIdle", 24, 24, 0.15f, false);
			Shirts_->CreateAnimation("ShirtsL" + ShirtsStyle_ + ".bmp", "LeftIdle", 24, 24, 0.15f, false);
		}
		{// 캐릭터 Back idle 상태
			Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackIdle", 48, 48, 0.15f, false); // 24 한줄에
			Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackIdle", 54, 54, 0.15f, false);
			Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "BackIdle", 48, 48, 0.15f, false);
			Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "BackIdle", 48, 48, 0.15f, false);
			Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "BackIdle", 48, 48, 0.15f, false);
		}

	}
	////////////////move
	{
		{ // 캐릭터 아래로 걷는 모션
			Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontWalk", 1, 4, 0.15f, true);
			Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontWalk", 7, 10, 0.15f, true);
			Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "FrontWalk", 1, 4, 0.15f, true);
			Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "FrontWalk", 1, 4, 0.15f, true);
			Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "FrontWalk", 1, 4, 0.15f, true);
		}
		{ // 캐릭터 오른쪽으로 걷는 모션
			Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightWalk", 25, 29, 0.15f, true);
			Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightWalk", 31, 35, 0.15f, true);
			Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "RightWalk", 25, 29, 0.15f, true);
			Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "RightWalk", 25, 29, 0.15f, true);
			Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "RightWalk", 25, 29, 0.15f, true);
		}
		{ // 캐릭터 왼쪽으로 걷는 모션
			Body_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftWalk", 25, 29, 0.13f, true);
			Arm_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftWalk", 31, 35, 0.13f, true);
			Pants_->CreateAnimation("PantsL" + PantsStyle_ + ".bmp", "LeftWalk", 25, 29, 0.13f, true);
			Hair_->CreateAnimation("HairL" + HairStyle_ + HairColor_ + ".bmp", "LeftWalk", 25, 29, 0.13f, true);
			Shirts_->CreateAnimation("ShirtsL" + ShirtsStyle_ + ".bmp", "LeftWalk", 25, 29, 0.13f, true);
		}
		{ // 캐릭터 위로 걷는 모션
			Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackWalk", 49, 52, 0.15f, true);
			Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackWalk", 55, 58, 0.15f, true);
			Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "BackWalk", 49, 52, 0.15f, true);
			Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "BackWalk", 49, 52, 0.15f, true);
			Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "BackWalk", 49, 52, 0.15f, true);
		}

		//////////////////Wield

		WieldItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.15f, false);
		BackItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.15f, false);
		//Left 수정 , 옷 수정
		{
			{ // 내려치는 방향 : 앞

				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontWield", 264, 268, 0.1f, false); // 24 한줄에
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontWield", 270, 274, 0.1f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "FrontWield", 264, 268, 0.1f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "FrontWield", 264, 268, 0.1f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "FrontWield", 264, 268, 0.1f, false);

				WieldItem_->CreateAnimation("FrontHoe.bmp", "FrontHoe", 0, 4, 0.1f, false);
				WieldItem_->CreateAnimation("FrontAx.bmp", "FrontAx", 0, 4, 0.1f, false);
				WieldItem_->CreateAnimation("FrontPick.bmp", "FrontPick", 0, 4, 0.1f, false);
			}
			{ // 내려치는 방향 : 오른쪽
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightWield", 192, 196, 0.1f, false);
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightWield", 198, 202, 0.1f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "RightWield", 192, 196, 0.1f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "RightWield", 192, 196, 0.1f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "RightWield", 192, 196, 0.1f, false);

				WieldItem_->CreateAnimation("RightHoe.bmp", "RightHoe", 0, 4, 0.1f, false);
				WieldItem_->CreateAnimation("RightAx.bmp", "RightAx", 0, 4, 0.1f, false);
				WieldItem_->CreateAnimation("RightPick.bmp", "RightPick", 0, 4, 0.1f, false);
			}
			{ // 내려치는 방향 : 왼쪽
				Body_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftWield", 192, 196, 0.1f, false);
				Arm_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftWield", 198, 202, 0.1f, false);
				Pants_->CreateAnimation("PantsL" + PantsStyle_ + ".bmp", "LeftWield", 192, 196, 0.1f, false);
				Hair_->CreateAnimation("HairL" + HairStyle_ + HairColor_ + ".bmp", "LeftWield", 192, 196, 0.1f, false);
				Shirts_->CreateAnimation("ShirtsL" + ShirtsStyle_ + ".bmp", "LeftWield", 192, 196, 0.1f, false);

				WieldItem_->CreateAnimation("LeftHoe.bmp", "LeftHoe", 0, 4, 0.1f, false);
				WieldItem_->CreateAnimation("LeftAx.bmp", "LeftAx", 0, 4, 0.1f, false);
				WieldItem_->CreateAnimation("LeftPick.bmp", "LeftPick", 0, 4, 0.1f, false);

			}
			{ // 내려치는 방향 : 뒤
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackWield", 242, 243, 0.1f, false);
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackWield", 151, 153, 0.1f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "BackWield", 242, 243, 0.1f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "BackWield", 242, 243, 0.1f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "BackWield", 242, 243, 0.1f, false);

				BackItem_->CreateAnimation("Tools.bmp", "BackHoe", 24, 25, 0.1f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackAx", 66 + 42, 67 + 42, 0.1f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackPick", 66, 67, 0.1f, false);
			}
		}
		////////////////////Hit
		HitItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.1f, false);
		// Left 수정, 옷 수정
		{
			{ // 때리는 방향 : 앞
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontHit", 96, 101, 0.08f, false); // 24 한줄에
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontHit", 108, 113, 0.08f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "FrontHit", 96, 101, 0.08f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "FrontHit", 96, 101, 0.08f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "FrontHit", 96, 101, 0.08f, false);

				HitItem_->CreateAnimation("FrontSickle.bmp", "FrontSickle", 0, 5, 0.08f, false);
				HitItem_->CreateAnimation("FrontSword.bmp", "FrontSword", 0, 5, 0.08f, false);
			}
			{ // 때리는 방향  : 오른쪽
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightHit", 120, 125, 0.08f, false);
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightHit", 132, 137, 0.08f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "RightHit", 120, 125, 0.08f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "RightHit", 120, 125, 0.08f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "RightHit", 120, 125, 0.08f, false);

				HitItem_->CreateAnimation("RightSickle.bmp", "RightSickle", 0, 5, 0.08f, false);
				HitItem_->CreateAnimation("RightSword.bmp", "RightSword", 0, 5, 0.08f, false);
			}
			{ // 때리는 방향  : 왼쪽
				Body_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftHit", 120, 125, 0.08f, false);
				Arm_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftHit", 132, 137, 0.08f, false);
				Pants_->CreateAnimation("PantsL" + PantsStyle_ + ".bmp", "LeftHit", 120, 125, 0.08f, false);
				Hair_->CreateAnimation("HairL" + HairStyle_ + HairColor_ + ".bmp", "LeftHit", 120, 125, 0.08f, false);
				Shirts_->CreateAnimation("ShirtsL" + ShirtsStyle_ + ".bmp", "LeftHit", 120, 125, 0.08f, false);

				HitItem_->CreateAnimation("LeftSickle.bmp", "LeftSickle", 0, 5, 0.08f, false);
				HitItem_->CreateAnimation("LeftSword.bmp", "LeftSword", 0, 5, 0.08f, false);
			}
			{ // 때리는 방향  : 뒤
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackHit", 144, 149, 0.08f, false);
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackHit", 156, 161, 0.08f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "BackHit", 144, 149, 0.08f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "BackHit", 144, 149, 0.08f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "BackHit", 144, 149, 0.08f, false);

				BackItem_->CreateAnimation("BackSickle.bmp", "BackSickle", 0, 5, 0.08f, false);
				BackItem_->CreateAnimation("BackSword.bmp", "BackSword", 0, 5, 0.08f, false);
			}
		}
		WaterItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.3f, false);
		///////////////////Water
		{
			{ // 물주는 방향 : 앞
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontWater", 96, 96, 0.8f, false); // 24 한줄에
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "FrontWater", 103, 103, 0.8f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "FrontWater", 96, 96, 0.8f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "FrontWater", 96, 96, 0.8f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "FrontWater", 96, 96, 0.8f, false);
				WaterItem_->CreateAnimation("FrontWateringCan.bmp", "FrontWateringCan", 0, 0, 0.8f, false);
			}
			{ // 물주는 방향  : 오른쪽
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightWater", 171, 171, 0.8f, false);
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "RightWater", 183, 183, 0.8f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "RightWater", 171, 171, 0.8f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "RightWater", 171 + 24, 171 + 24, 0.8f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "RightWater", 171, 171, 0.8f, false);

				WaterItem_->CreateAnimation("RightWateringCan.bmp", "RightWateringCan", 0, 0, 0.8f, false);
			}
			{ // 물주는 방향  : 왼쪽
				Body_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftWater", 171, 171, 0.8f, false);
				Arm_->CreateAnimation("BodyLShirts" + ShirtsStyle_ + ".bmp", "LeftWater", 183, 183, 0.8f, false);
				Pants_->CreateAnimation("PantsL" + PantsStyle_ + ".bmp", "LeftWater", 171, 171, 0.8f, false);
				Hair_->CreateAnimation("HairL" + HairStyle_ + HairColor_ + ".bmp", "LeftWater", 171, 171, 0.8f, false);
				Shirts_->CreateAnimation("ShirtsL" + ShirtsStyle_ + ".bmp", "LeftWater", 171, 171, 0.8f, false);
				WaterItem_->CreateAnimation("LeftWateringCan.bmp", "LeftWateringCan", 0, 0, 0.8f, false);
			}
			{ // 물주는 방향  : 뒤
				Body_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackWater", 172, 172, 0.8f, false);
				Arm_->CreateAnimation("BodyShirts" + ShirtsStyle_ + ".bmp", "BackWater", 184, 184, 0.8f, false);
				Pants_->CreateAnimation("Pants" + PantsStyle_ + ".bmp", "BackWater", 172, 172, 0.8f, false);
				Hair_->CreateAnimation("Hair" + HairStyle_ + HairColor_ + ".bmp", "BackWater", 172, 172, 0.8f, false);
				Shirts_->CreateAnimation("Shirts" + ShirtsStyle_ + ".bmp", "BackWater", 172, 172, 0.8f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackWateringCan", 151, 151, 0.8f, false);
			}
		}
	}
	ChangeAni("FrontIdle");


}
void Player::Start()
{
	PlayerCol_ = CreateCollision("Player", { 48,16 }, { 0,56 });
	PlayerMonsterCheckCol_ = CreateCollision("Player", { 48,128 });
	LongSwordCol_ = CreateCollision("LongSword", { 98,128 });
	LongSwordCol_->Off();

	std::string HairColor_ = GetHairColorString();
	std::string HairStyle_ = GetHairStyleString();
	std::string ShirtsStyle_ = GetShirtsStyleString();
	std::string PantsStyle_ = GetPantsStyleString();

	BackItem_ = CreateRendererToScale("Tools.bmp", { 56,112 }, static_cast<int>(ORDER::PLAYER));
	Body_ = CreateRendererToScale("BodyShirts" + ShirtsStyle_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Pants_ = CreateRendererToScale("Pants" + PantsStyle_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Shirts_ = CreateRendererToScale("Shirts" + ShirtsStyle_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Hair_ = CreateRendererToScale("Hair" + HairStyle_ + HairColor_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Arm_ = CreateRendererToScale("BodyShirts" + ShirtsStyle_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);

	WieldItem_ = CreateRendererToScale("Tools.bmp", { 224, 160 }, static_cast<int>(ORDER::PLAYERITEM), RenderPivot::CENTER, { 0,-17 });
	HitItem_ = CreateRendererToScale("Tools.bmp", { 224, 200 }, static_cast<int>(ORDER::PLAYERITEM), RenderPivot::CENTER, { 0, 32 });
	WaterItem_ = CreateRendererToScale("Tools.bmp", { 192,128 }, static_cast<int>(ORDER::PLAYERITEM), RenderPivot::CENTER, { 0,20 });
	if (false == GameEngineInput::GetInst()->IsKey("LeftWalk"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftWalk", 'A');
		GameEngineInput::GetInst()->CreateKey("RightWalk", 'D');
		GameEngineInput::GetInst()->CreateKey("BackWalk", 'W');
		GameEngineInput::GetInst()->CreateKey("FrontWalk", 'S');
		GameEngineInput::GetInst()->CreateKey("DebugONOFF", 'Q');
	}
}


bool Player::DirKeyCheck()
{

	if (true == GameEngineInput::GetInst()->IsPress("FrontWalk"))
	{
		CurDir_ = PlayerDir::Front;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("BackWalk"))
	{
		CurDir_ = PlayerDir::Back;
	}

	if (true == GameEngineInput::GetInst()->IsPress("LeftWalk"))
	{
		CurDir_ = PlayerDir::Left;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("RightWalk"))
	{
		CurDir_ = PlayerDir::Right;
	}


	if (PrevDir_ != CurDir_)
	{
		PrevDir_ = CurDir_;
		DirAnimationChange();
		return true;
	}

	return false;
}
///////////////
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////농사 타일맵 관련 함수//////////////////////////////////////////////
bool Player::IsHoeTileCreate()
{
	TileCheckDir();

	Sound_ = GameEngineSound::SoundPlayControl("hoeHit.wav");
	Sound_.Volume(0.8f);
	PlayerTile* Tile = GroundTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);

	if (nullptr == Tile && PlayerItem::HoeItem == CurItem_) // 맨땅이라면
	{
		return true;
	}

	return false;
}

bool Player::IsWaterTileCreate()
{
	TileCheckDir();
	PlayerTile* GroundTile = GroundTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);
	if (nullptr == GroundTile)
	{
		return false;
	}
	else
	{
		if (CurItem_ == PlayerItem::WateringCanItem)
		{

			if (TileType::SeedTile == GroundTile->Dirt_ || TileType::HoeDirt == GroundTile->Dirt_) // 씨앗상태와 관계없이 물은 준다.
			{
				return true;
			}
		}
		return false;
	}

}
bool Player::IsSeedTileCreate()
{
	TileCheckDir();
	Sound_ = GameEngineSound::SoundPlayControl("sandstep2.wav");
	Sound_.Volume(0.8f);
	PlayerTile* GroundTile = GroundTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);
	if (nullptr == GroundTile)
	{
		return false;
	}
	if (CurItemKind_ == PlayerItemKind::SeedItem && false == GroundTile->IsSeed_)
	{
		return true;
	}
	return false;
}
void Player::DirHoeDirtCreateTile()
{
	TileCheckDir();
	PlayerTile* Tile = GroundTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "hoeDirt.bmp", 0, static_cast<int>(ORDER::GROUND));
	Tile->Dirt_ = TileType::HoeDirt;
}

void Player::DirWaterDirtCreateTile()
{
	TileCheckDir();

	PlayerTile* GroundTile = GroundTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);
	if (true == GroundTile->IsSeed_)
	{
		PlayerTile* CropsTile = CropsTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);
		CropsTile->Dirt_ = TileType::WaterDirt;
		GroundTile = GroundTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "hoeDirtDark.bmp", 0, static_cast<int>(ORDER::GROUND));
		GroundTile->Dirt_ = TileType::WaterDirt;
	}
	else
	{
		GroundTile = GroundTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "hoeDirtDark.bmp", 0, static_cast<int>(ORDER::GROUND));
		GroundTile->Dirt_ = TileType::WaterDirt;
	}


}
void Player::DirSeedCreateTile()
{

	TileCheckDir();
	PlayerTile* GroundTile = GroundTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);

	PlayerTile* CropsTile = SetCropTile();

	if (CropsTile == nullptr)
	{
		return;
	}
	CropsTile->Dirt_ = GroundTile->Dirt_;
	CropsTile->SeedDay_ = Time::TimeSet->GetGameDay_(); // 심은 날짜 저장.
	CropsTile->DirtTilePosX_ = TileIndexX_;
	CropsTile->DirtTilePosY_ = TileIndexY_;
	IsCropsTile_.push_back(CropsTile);

	GroundTile->Dirt_ = TileType::SeedTile;
	GroundTile->Seed_ = CropsTile->Seed_;
	GroundTile->IsSeed_ = true;

	Tool::ToolSet->ItemUse(CurItem_); // 아이템 사용하면 하나 없애기

}


void Player::CropsGrowDay(PlayerTile* _Tile)
{
	SetCropGrowIndex(_Tile->Seed_);

	int _GrowDay = Time::TimeSet->GetGameDay_() - _Tile->SeedDay_;

	_Tile = CropsTileMap_->CreateTile<PlayerTile>(_Tile->DirtTilePosX_, _Tile->DirtTilePosY_, "Crops.bmp", TileUpdateIndex_ + (_GrowDay), static_cast<int>(ORDER::GROUND)); // 타일 변경

	if (HarvestDay_ <= _GrowDay)
	{
		_Tile->Isharvest_ = true;
		CropsHarvestSet(_Tile);
	}

}

void Player::CropsHarvestSet(PlayerTile* _Tile)
{
	CreateCropPos_ = { (static_cast<float>(_Tile->DirtTilePosX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(_Tile->DirtTilePosY_) + 0.5f) * (MapScaleY_ / 65) };

	_Tile->CropsActor_ = GetLevel()->CreateActor<Crops>(static_cast<int>(ORDER::PLAYER), CheckSeedSting(_Tile->Seed_)); // 다 자라면 수확하기 위해 엑터로 변경
	_Tile->CropsActor_->SetPosition(CreateCropPos_); // 타일 위치 넣어주기
	_Tile->CropsActor_->SetCropsType(_Tile->Seed_); // 수확할 작물 종류 넣어주기

	_Tile = CropsTileMap_->CreateTile<PlayerTile>(_Tile->DirtTilePosX_, _Tile->DirtTilePosY_, "Crops.bmp", 6, static_cast<int>(ORDER::GROUND));
	_Tile->Isharvest_ = true;

	PlayerTile* GroundTile = GroundTileMap_->GetTile<PlayerTile>(_Tile->DirtTilePosX_, _Tile->DirtTilePosY_);
	GroundTile->IsSeed_ = false;
}

bool Player::IsCheckHarvestTile()
{
	TileCheckDir();

	PlayerTile* _Tile = CropsTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);

	if (nullptr == _Tile)
	{
		return false;
	}

	if (true == _Tile->Isharvest_)
	{
		return true;
	}

	return false;

}

void Player::CropsHarvest()
{
	TileCheckDir();
	PlayerTile* _Tile = CropsTileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);

	DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
	DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
	DropItem_->SetItem(_Tile->CropsActor_->Item_);
	DropItem_->SetItemKind(_Tile->CropsActor_->ItemKind_);
	_Tile->Isharvest_ = false;
	CropsTileMap_->DeleteTile(TileIndexX_, TileIndexY_);
	Sound_ = GameEngineSound::SoundPlayControl("cut.wav");
	Sound_.Volume(0.8f);
}
void Player::CropsGrowUpdate()
{
	if (CurDay_ != Time::TimeSet->GetGameDay_())
	{
		std::list<PlayerTile*>::iterator StartIter = IsCropsTile_.begin();
		std::list<PlayerTile*>::iterator EndIter = IsCropsTile_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == *StartIter)
			{
				continue;
			}

			else if (false == (*StartIter)->Isharvest_)
			{
				if (TileType::WaterDirt == (*StartIter)->Dirt_) // 물을 줬을때
				{
					CropsGrowDay(*StartIter);
				}
				else //물을 안줬을때
				{
					if (CurDay_ != Time::TimeSet->GetGameDay_())
					{
						(*StartIter)->SeedDay_ += 1;
					}
				}
			}
			else
			{
				
			}
		}

		DayChangeSetCrops();
	}

}
void Player::DayChangeSetCrops()
{
	std::list<PlayerTile*>::iterator StartIter = IsCropsTile_.begin();
	std::list<PlayerTile*>::iterator EndIter = IsCropsTile_.end();

	PlayerTile* GroundTile;
	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}
		if ((*StartIter)->DirtTilePosX_ > 0) // 수확된 타일은 검사 안하도록
		{
			GroundTile = GroundTileMap_->GetTile<PlayerTile>((*StartIter)->DirtTilePosX_, (*StartIter)->DirtTilePosY_);
			GroundTile = GroundTileMap_->CreateTile<PlayerTile>((*StartIter)->DirtTilePosX_, (*StartIter)->DirtTilePosY_, "hoeDirt.bmp", 0, static_cast<int>(ORDER::GROUND));
			(*StartIter)->Dirt_ = TileType::HoeDirt;
			GroundTile->Dirt_ = TileType::HoeDirt; //마른땅으로 초기화
		}
	}

	CurDay_ = Time::TimeSet->GetGameDay_();

}

PlayerTile* Player::SetCropTile()
{
	PlayerTile* _Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 6, static_cast<int>(ORDER::GROUND));

	if (PlayerItem::CauliFlowerSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 16, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Cauliflower;
	}
	else if (PlayerItem::PhatatoSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 24, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Photato;
	}
	else if (PlayerItem::KaleSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 41, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Kale;
	}
	else if (PlayerItem::ParsnipSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 0, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Parsnip;
	}
	else if (PlayerItem::BeanSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 8, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Bean;
	}
	else if (PlayerItem::BlueberrieSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 56, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Blueberrie;
	}
	else if (PlayerItem::PepperSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 48, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Pepper;
	}
	else if (PlayerItem::MelonSeedItem == CurItem_)
	{
		_Tile = CropsTileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 32, static_cast<int>(ORDER::GROUND));
		_Tile->Seed_ = SeedType::Melon;
	}


	return _Tile;
}
void Player::SetCropGrowIndex(SeedType _Seed)
{
	if (_Seed == SeedType::Photato)
	{
		HarvestDay_ = 6;
		TileUpdateIndex_ = 24;
	}

	else if (_Seed == SeedType::Cauliflower)
	{
		HarvestDay_ = 6;
		TileUpdateIndex_ = 16;
	}
	else if (_Seed == SeedType::Kale)
	{
		HarvestDay_ = 4;
		TileUpdateIndex_ = 41;
		
	}
	else if (_Seed == SeedType::Bean)
	{
		HarvestDay_ = 6;
		TileUpdateIndex_ = 8;

	}
	else if (_Seed == SeedType::Blueberrie)
	{
		HarvestDay_ = 6;
		TileUpdateIndex_ = 56;

	}
	else if (_Seed == SeedType::Melon)
	{
		HarvestDay_ = 6;
		TileUpdateIndex_ = 32;

	}
	else if (_Seed == SeedType::Parsnip)
	{
		HarvestDay_ = 5;
		TileUpdateIndex_ = 0;

	}
	else if (_Seed == SeedType::Pepper)
	{
		HarvestDay_ = 6;
		TileUpdateIndex_ = 48;

	}
}

void Player::TileCheckDir()
{
	if (CurDir_ == PlayerDir::Front) {
		TileIndexX_ = static_cast<int>(GetPosition().x / 64);
		TileIndexY_ = static_cast<int>((GetPosition().y + 64.0f) / 64) + 1;
	}
	else if (CurDir_ == PlayerDir::Right) {
		TileIndexX_ = static_cast<int>(GetPosition().x / 64) + 1;
		TileIndexY_ = static_cast<int>((GetPosition().y + 32.0f) / 64);
	}
	else if (CurDir_ == PlayerDir::Left) {
		TileIndexX_ = static_cast<int>(GetPosition().x / 64) - 1;
		TileIndexY_ = static_cast<int>((GetPosition().y + 32.0f) / 64);
	}
	else if (CurDir_ == PlayerDir::Back) {
		TileIndexX_ = static_cast<int>(GetPosition().x / 64);
		TileIndexY_ = static_cast<int>((GetPosition().y + 32.0f) / 64) - 1;
	}

}
float4 Player::TileCheckDirPos()
{
	
	if (CurDir_ == PlayerDir::Front) {

		return GetPosition() + float4(0, 96);
	}
	else if (CurDir_ == PlayerDir::Right) {
		return GetPosition() + float4(64, 32);
	}
	else if (CurDir_ == PlayerDir::Left) {
		return GetPosition() + float4(-64, 32);
	}
	else if (CurDir_ == PlayerDir::Back) {
		return GetPosition() + float4(0, -32);
	}

}




///////////////
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////오브젝트 상호작용 관련 함수/////////////////////////////////////////////

bool Player::IsCheckFarmObjectTile()
{
	TileCheckDir();
	if (GetLevel()->GetNameCopy() == "FarmLevel")
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);

		if (nullptr == _Tile)
		{
			return false;
		}

		else
		{
			return true;
		}
	}


}
bool Player::IsCheckMineObjectTile()
{
	TileCheckDir();
	if (GetLevel()->GetNameCopy() == "Mine1Level")
	{
		MineTile* _Tile = Mine1Object::MainMine1Tile->ReturnMineTileObejctMap_()->GetTile<MineTile>(TileIndexX_, TileIndexY_);

		if (nullptr == _Tile)
		{
			return false;
		}

		else
		{
			return true;
		}

	}
	if (GetLevel()->GetNameCopy() == "Mine2Level")
	{
		MineTile* _Tile = Mine2Object::MainMine2Tile->ReturnMineTileObejctMap_()->GetTile<MineTile>(TileIndexX_, TileIndexY_);

		if (nullptr == _Tile)
		{
			return false;
		}

		else
		{
			return true;
		}

	}


}
void Player::HitObject()
{
	TileCheckDir();
	if (CurItem_ == PlayerItem::SickleItem && GetLevel()->GetNameCopy() == "FarmLevel")
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);
		if (_Tile->EnvironmentType_ == EnvironmentTileType::Grass)
		{
			Sound_ = GameEngineSound::SoundPlayControl("cut.wav");
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();

			TileAnimation* TileAni_ = GetLevel()->CreateActor<TileAnimation>(static_cast<int>(ORDER::PLAYER), "GrassAni");
			if (CurDir_ == PlayerDir::Back)
			{
				TileAni_->SetOrder(static_cast<int>(ORDER::BACKEFFECT));
			}
			TileAni_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80), (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			TileAni_->SetAniString("GrassAni");


			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::GrassItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->DeleteTile(TileIndexX_, TileIndexY_);
			return;
		}

	}
}
void Player::WieldMineObject()
{
	TileCheckDir();
	if (CurItem_ == PlayerItem::PickItem&& GetLevel()->GetNameCopy() == "Mine1Level")
	{
		MineTile* _Tile = Mine1Object::MainMine1Tile->ReturnMineTileObejctMap_()->GetTile<MineTile>(TileIndexX_, TileIndexY_);
		if (_Tile == nullptr)
		{
			return;
		}
		if (TileIndexX_ == 8 && TileIndexY_ == 8)
		{
			_Tile = Mine1Object::MainMine1Tile->ReturnMineTileObejctMap_()->CreateTile<MineTile>(TileIndexX_, TileIndexY_, "GoMine2.bmp", static_cast<int>(ORDER::GROUND));
		}
		else
		{
			_Tile = Mine1Object::MainMine1Tile->ReturnMineTileObejctMap_()->CreateTile<MineTile>(TileIndexX_, TileIndexY_,"Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
		}
		_Tile->TileCol_->Death();

		TileAnimation* TileAni_ = GetLevel()->CreateActor<TileAnimation>(static_cast<int>(ORDER::PLAYER), "StoneAni");
		if (CurDir_ == PlayerDir::Back)
		{
			TileAni_->SetOrder(static_cast<int>(ORDER::BACKEFFECT));
		}
		TileAni_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 20), (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 20) });
		TileAni_->SetAniString("StoneAni");
		//_Tile->IsDestroy_ = true;
		Sound_ = GameEngineSound::SoundPlayControl("hammer.wav");
		DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
		DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 20) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 20) });

		DropItem_->SetItem(ReturnMineItem(_Tile->TileType_));
		DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
		Mine1Object::MainMine1Tile->ReturnMineTileObejctMap_()->DeleteTile(TileIndexX_, TileIndexY_);
		return;
	}
	if (CurItem_ == PlayerItem::PickItem && GetLevel()->GetNameCopy() == "Mine2Level")
	{
		MineTile* _Tile = Mine2Object::MainMine2Tile->ReturnMineTileObejctMap_()->GetTile<MineTile>(TileIndexX_, TileIndexY_);
		if (_Tile == nullptr)
		{
			return;
		}
		_Tile = Mine2Object::MainMine2Tile->ReturnMineTileObejctMap_()->CreateTile<MineTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
		_Tile->TileCol_->Death();

		TileAnimation* TileAni_ = GetLevel()->CreateActor<TileAnimation>(static_cast<int>(ORDER::PLAYER), "StoneAni");
		if (CurDir_ == PlayerDir::Back)
		{
			TileAni_->SetOrder(static_cast<int>(ORDER::BACKEFFECT));
		}
		TileAni_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 35), (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 35) });
		TileAni_->SetAniString("StoneAni");
		//_Tile->IsDestroy_ = true;
		Sound_ = GameEngineSound::SoundPlayControl("hammer.wav");
		DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
		DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 35) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 35) });

		DropItem_->SetItem(ReturnMineItem(_Tile->TileType_));
		DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
		Mine2Object::MainMine2Tile->ReturnMineTileObejctMap_()->DeleteTile(TileIndexX_, TileIndexY_);
		return;
	}
}
void Player::LongSwordColCheck()
{
	if (CurDir_ == PlayerDir::Right)
	{
		LongSwordCol_->On();
		LongSwordCol_->SetScale({ 98, 128 });
		LongSwordCol_->SetPivot({ 49,0 });
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		LongSwordCol_->On();
		LongSwordCol_->SetScale({ 98, 128 });
		LongSwordCol_->SetPivot({ -49,0 });
	}
	else if (CurDir_ == PlayerDir::Front)
	{
		LongSwordCol_->On();
		LongSwordCol_->SetScale({ 192, 80 });
		LongSwordCol_->SetPivot({ 0,80 });
	}
	else if (CurDir_ == PlayerDir::Back)
	{
		LongSwordCol_->On();
		LongSwordCol_->SetScale({ 192, 80 });
		LongSwordCol_->SetPivot({ 0,-80 });
	}

	if (LongSwordCol_->CollisionCheck("Monster") == true)
	{
	
		IsHit_ = true;
	}
	else
	{
		Sound_ = GameEngineSound::SoundPlayControl("cast.wav");
		Sound_.Volume(0.8f);
	}
}
void Player::MonsterCheck()
{
	if (PlayerMonsterCheckCol_->CollisionCheck("Monster"))
	{
		
		HealthUI::HealthUISet->MinusPlayerHP();

	}


}
PlayerItem Player::ReturnMineItem(MineTileType _Type)
{
	if (_Type == MineTileType::amethyst)
	{
		return PlayerItem::amethystItem;
	}
	if (_Type == MineTileType::Coal)
	{
		return PlayerItem::CoalItem;
	}	
	if (_Type == MineTileType::Copper)
	{
		return PlayerItem::CopperItem;
	}	
	if (_Type == MineTileType::Diamond)
	{
		return PlayerItem::DiamondItem;
	}	
	if (_Type == MineTileType::Emerald)
	{
		return PlayerItem::EmeraldItem;
	}	
	if (_Type == MineTileType::Ruby)
	{
		return PlayerItem::RubyItem;
	}	
	if (_Type == MineTileType::Stone)
	{
		return PlayerItem::StoneItem;
	}
}
void Player::WieldFarmObject()
{
	if (GetLevel()->GetNameCopy() != "FarmLevel")
	{
		return;
	}
	TileCheckDir();
	if (CurItem_ == PlayerItem::PickItem)
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);
		if (_Tile == nullptr)
		{
			return;
		}
		if (_Tile->EnvironmentType_ == EnvironmentTileType::Stone)
		{
			Sound_ = GameEngineSound::SoundPlayControl("hammer.wav");
			Sound_.Volume(0.8f);
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();

			TileAnimation* TileAni_ = GetLevel()->CreateActor<TileAnimation>(static_cast<int>(ORDER::PLAYER), "StoneAni");
			if (CurDir_ == PlayerDir::Back)
			{
				TileAni_->SetOrder(static_cast<int>(ORDER::BACKEFFECT));
			}
			TileAni_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80), (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			TileAni_->SetAniString("StoneAni");
			//_Tile->IsDestroy_ = true;

			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::StoneItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->DeleteTile(TileIndexX_, TileIndexY_);
			return;
		}

	}

	else if (CurItem_ == PlayerItem::AxItem)
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);
		if (_Tile == nullptr)
		{
			return;
		}
		if (_Tile->EnvironmentType_ == EnvironmentTileType::Branch)
		{
			Sound_ = GameEngineSound::SoundPlayControl("axchop.wav");
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();
			//_Tile->IsDestroy_ = true;

			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::BranchItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->DeleteTile(TileIndexX_, TileIndexY_);
			return;
		}

		else if (_Tile->EnvironmentType_ == EnvironmentTileType::Tree)
		{
			_Tile->DeathCount_ -= 1;
			if (_Tile->DeathCount_ != 0 )
			{
				Sound_ = GameEngineSound::SoundPlayControl("axchop.wav");
				Sound_.Volume(0.8f);
				if (_Tile->DeathCount_ > 3)
				{
					_Tile->IsShake_ = true;
				}

				if (_Tile->DeathCount_ == 3)
				{
					_Tile->TreeTop_->Death();

					DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
					DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
					DropItem_->SetItem(PlayerItem::BranchItem);
					DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
				}
				
			
				return;
			}

			Sound_ = GameEngineSound::SoundPlayControl("axchop.wav");
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->IsDestroy_ = true; 

			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::PLAYER));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::BranchItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			_Tile->EnvironmentType_ = EnvironmentTileType::Max;
			_Tile->TileCol_-> Death();
			//FarmObjectEnvironment::MainFarmObject->ReturnFarmTileObejctMap_()->DeleteTile(TileIndexX_, TileIndexY_);
			return;
		}

	}

	
}

bool Player::IsIdleKey()
{
	if (true == GameEngineInput::GetInst()->IsFree("LeftWalk") &&
		true == GameEngineInput::GetInst()->IsFree("RightWalk") &&
		true == GameEngineInput::GetInst()->IsFree("BackWalk") &&
		true == GameEngineInput::GetInst()->IsFree("FrontWalk"))
	{
		return true;
	}
	return false;
}

bool Player::IsWalkKey()
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


//////////////////////string 관련
std::string Player::GetHairColorString()
{
	if (CurHairColor_ == PlayerHairColor::Black)
	{
		return "Black";
	}
	else if (CurHairColor_ == PlayerHairColor::Blue)
	{
		return "Blue";
	}
	else if (CurHairColor_ == PlayerHairColor::Red)
	{
		return "Red";
	}

	return "";
}
std::string Player::GetHairStyleString()
{

	if (CurHairStyle_ == PlayerHairStyle::First)
	{
		return "1";
	}
	else if (CurHairStyle_ == PlayerHairStyle::Second)
	{
		return "2";
	}
	return "";
}
std::string Player::GetShirtsStyleString()
{

	if (CurShirts_ == PlayerShirts::First)
	{
		return "1";
	}
	else if (CurShirts_ == PlayerShirts::Second)
	{
		return "2";
	}
	else if (CurShirts_ == PlayerShirts::Third)
	{
		return "3";
	}
	return "";
}
std::string Player::GetPantsStyleString()
{

	if (CurPants_ == PlayerPants::First)
	{
		return "1";
	}
	else if (CurPants_ == PlayerPants::Second)
	{
		return "2";
	}
	return "";
}
std::string Player::GetItemString()
{

	if (CurItem_ == PlayerItem::HoeItem)
	{
		return "Hoe";
	}
	else if (CurItem_ == PlayerItem::AxItem)
	{
		return "Ax";
	}
	else if (CurItem_ == PlayerItem::PickItem)
	{
		return "Pick";
	}
	else if (CurItem_ == PlayerItem::WateringCanItem)
	{
		return "WateringCan";
	}
	else if (CurItem_ == PlayerItem::SickleItem)
	{
		return "Sickle";
	}
	else if (CurItem_ == PlayerItem::LongSwordItem)
	{
		return "Sword";
	}
	else
	{
		return "Nothing";
	}
	return "";
}
std::string Player::CheckSeedSting(SeedType _Type)
{
	if (SeedType::Photato == _Type)
	{
		return "Photato" + CropNum_;
	}
	else if (SeedType::Kale == _Type)
	{
		return "Kale" + CropNum_;
	}
	else if (SeedType::Cauliflower == _Type)
	{
		return "Cauliflower" + CropNum_;
	}
	else if (SeedType::Bean == _Type)
	{
		return "Bean" + CropNum_;
	}
	else if (SeedType::Blueberrie == _Type)
	{
		return "Blueberrie" + CropNum_;
	}
	else if (SeedType::Melon == _Type)
	{
		return "Melon" + CropNum_;
	}
	else if (SeedType::Parsnip == _Type)
	{
		return "Parsnip" + CropNum_;
	}
	else if (SeedType::Pepper == _Type)
	{
		return "Pepper" + CropNum_;
	}
	else
	{
		return "";
	}
}
void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;

	if ("TitleLevel" == _PrevLevel->GetNameCopy())
	{
		BgmPlayer = GameEngineSound::SoundPlayControl("spring_day.wav");
		BgmPlayer.Volume(0.6f);
	}	
	if ("FarmHouseLevel" == _PrevLevel->GetNameCopy() && "FarmLevel" == GetLevel()->GetNameCopy())
	{
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("Spring (It's A Big World Outside).mp3");
		BgmPlayer.Volume(0.6f);
	}
	if ("SeedShopLevel" == GetLevel()->GetNameCopy())
	{
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("Country Shop.mp3");
	}
	if ("SeedShopLevel" == _PrevLevel->GetNameCopy()&& "TownLevel" == GetLevel()->GetNameCopy())
	{
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("Spring (It's A Big World Outside).mp3");
		BgmPlayer.Volume(0.6f);
	}
	if ("MineEntryLevel" == GetLevel()->GetNameCopy()&& "Mine2Level" != _PrevLevel->GetNameCopy())
	{
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("Mines (Crystal Bells).mp3");
		BgmPlayer.Volume(0.6f);
	}
	if ("MineEntryLevel" == _PrevLevel->GetNameCopy()&& "Town2Level" == GetLevel()->GetNameCopy())
	{
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("Pelican Town.mp3");
		BgmPlayer.Volume(0.6f);
	}
	if ("ForestLevel" == _PrevLevel->GetNameCopy() && "AnimalShopLevel" == GetLevel()->GetNameCopy())
	{
		BgmPlayer.Stop();
		BgmPlayer = GameEngineSound::SoundPlayControl("Country Shop.mp3");
		BgmPlayer.Volume(0.6f);
	}
}

void Player::IsDebugModeONOFF()
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugONOFF"))
	{
		GetLevel()->IsDebugModeSwitch();
	}
}