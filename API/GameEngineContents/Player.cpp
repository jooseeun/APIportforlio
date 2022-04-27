#include "Player.h"
#include "BackGround.h"
#include "ContentsEnums.h"
#include "Tool.h"
#include "DropItem.h"
#include "TileAnimation.h"
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
	:Speed_(705.0f),
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
	CurDay_(1),
	CurHour_(0),
	CropNum_(0)
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

void Player::Start()
{
	PlayerCol_ = CreateCollision("Player", { 48,16 }, { 0,56 });

	int HairNum_ = static_cast<int>(CurHairStyle_);
	std::string HairColor_ = GetHairColorString();
	std::string HairStyle_ = GetHairStyleString();
	BackItem_ = CreateRendererToScale("Tools.bmp", { 56,112 }, static_cast<int>(ORDER::PLAYER));
	Body_ = CreateRendererToScale("Body.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Pants_ = CreateRendererToScale("BodyShirts.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Shirts_ = CreateRendererToScale("BodyShirts.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Hair_ = CreateRendererToScale("Hair" + HairColor_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,4 });
	Arm_ = CreateRendererToScale("BodyShirts.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,2 });
	WieldItem_ = CreateRendererToScale("Tools.bmp", { 224, 160 }, static_cast<int>(ORDER::PLAYERITEM), RenderPivot::CENTER, { 0,-17 });
	HitItem_ = CreateRendererToScale("Tools.bmp", { 224, 200 }, static_cast<int>(ORDER::PLAYERITEM), RenderPivot::CENTER, { 0, 32 });
	WaterItem_ = CreateRendererToScale("Tools.bmp", { 192,128 }, static_cast<int>(ORDER::PLAYERITEM), RenderPivot::CENTER, { 0,20 });


	// BackHit 리소스 다시 수정하기
	////////////idle
	{
		{// 캐릭터 front idle 상태
			Body_->CreateAnimation("Body.bmp", "FrontIdle", 0, 0, 0.15f, false); // 24 한줄에
			Arm_->CreateAnimation("BodyShirts.bmp", "FrontIdle", 6, 6, 0.15f, false);
			Pants_->CreateAnimation("BodyShirts.bmp", "FrontIdle", 18, 18, 0.15f, false);
			Hair_->CreateAnimation("Hair" + HairColor_ + ".bmp", "FrontIdle", HairNum_, HairNum_, 0.15f, false);
			Shirts_->CreateAnimation("BodyShirts.bmp", "FrontIdle", 0, 0, 0.15f, false);
		}
		{// 캐릭터 right idle 상태
			Body_->CreateAnimation("Body.bmp", "RightIdle", 24, 24, 0.15f, false);//+24
			Arm_->CreateAnimation("BodyShirts.bmp", "RightIdle", 30, 30, 0.15f, false);
			Pants_->CreateAnimation("BodyShirts.bmp", "RightIdle", 42, 42, 0.15f, false);
			Hair_->CreateAnimation("Hair" + HairColor_ + ".bmp", "RightIdle", HairNum_ + 8, HairNum_ + 8, 0.15f, false);
			Shirts_->CreateAnimation("BodyShirts.bmp", "RightIdle", 24, 24, 0.15f, false);//+24
		}
		{// 캐릭터 Left idle 상태
			Body_->CreateAnimation("Body2.bmp", "LeftIdle", 47, 47, 0.15f, false);
			Arm_->CreateAnimation("Body2Shirts.bmp", "LeftIdle", 41, 41, 0.15f, false);
			Pants_->CreateAnimation("Body2Shirts.bmp", "LeftIdle", 29, 29, 0.15f, false);
			Hair_->CreateAnimation("HairL" + HairColor_ + ".bmp", "LeftIdle", 7 - HairNum_ + 8, 7 - HairNum_ + 8, 0.15f, false);
			Shirts_->CreateAnimation("Body2Shirts.bmp", "LeftIdle", 47, 47, 0.15f, false);
		}
		{// 캐릭터 Back idle 상태
			Body_->CreateAnimation("Body.bmp", "BackIdle", 48, 48, 0.15f, false); // 24 한줄에
			Arm_->CreateAnimation("BodyShirts.bmp", "BackIdle", 54, 54, 0.15f, false);
			Pants_->CreateAnimation("BodyShirts.bmp", "BackIdle", 66, 66, 0.15f, false);
			Hair_->CreateAnimation("Hair" + HairColor_ + ".bmp", "BackIdle", HairNum_ + 16, HairNum_ + 16, 0.15f, false);
			Shirts_->CreateAnimation("BodyShirts.bmp", "BackIdle", 48, 48, 0.15f, false);
		}

	}
	////////////////move
	{
		{ // 캐릭터 아래로 걷는 모션
			Body_->CreateAnimation("Body.bmp", "FrontWalk", 1, 2, 0.3f, true);
			Arm_->CreateAnimation("BodyShirts.bmp", "FrontWalk", 7, 8, 0.3f, true);
			Pants_->CreateAnimation("BodyShirts.bmp", "FrontWalk", 19, 20, 0.3f, true);
			Hair_->CreateAnimation("HairDown" + HairColor_ + ".bmp", "FrontWalk", HairNum_, HairNum_, 0.3f, true);
			Shirts_->CreateAnimation("BodyShirts.bmp", "FrontWalk", 1, 2, 0.3f, true);
		}
		{ // 캐릭터 오른쪽으로 걷는 모션
			Body_->CreateAnimation("Body.bmp", "RightWalk", 25, 26, 0.4f, true);
			Arm_->CreateAnimation("BodyShirts.bmp", "RightWalk", 31, 32, 0.4f, true);
			Pants_->CreateAnimation("BodyShirts.bmp", "RightWalk", 43, 44, 0.4f, true);
			Hair_->CreateAnimation("HairDown" + HairColor_ + ".bmp", "RightWalk", HairNum_ + 8, HairNum_ + 8, 0.4f, true);
			Shirts_->CreateAnimation("BodyShirts.bmp", "RightWalk", 25, 26, 0.4f, true);
		}
		{ // 캐릭터 왼쪽으로 걷는 모션
			Body_->CreateAnimation("Body2.bmp", "LeftWalk", 45, 46, 0.4f, true);
			Arm_->CreateAnimation("Body2Shirts.bmp", "LeftWalk", 40, 41, 0.4f, true);
			Pants_->CreateAnimation("Body2Shirts.bmp", "LeftWalk", 27, 28, 0.4f, true);
			Hair_->CreateAnimation("HairDownL" + HairColor_ + ".bmp", "LeftWalk", 7 - HairNum_ + 8, 7 - HairNum_ + 8, 0.4f, true);
			Shirts_->CreateAnimation("Body2Shirts.bmp", "LeftWalk", 45, 46, 0.4f, true);
		}
		{ // 캐릭터 위로 걷는 모션
			Body_->CreateAnimation("Body.bmp", "BackWalk", 49, 50, 0.3f, true);
			Arm_->CreateAnimation("BodyShirts.bmp", "BackWalk", 55, 56, 0.3f, true);
			Pants_->CreateAnimation("BodyShirts.bmp", "BackWalk", 67, 68, 0.3f, true);
			Hair_->CreateAnimation("HairDown" + HairColor_ + ".bmp", "BackWalk", HairNum_ + 16, HairNum_ + 16, 0.3f, true);
			Shirts_->CreateAnimation("BodyShirts.bmp", "BackWalk", 49, 50, 0.3f, true);
		}

		//////////////////Wield

		WieldItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.15f, false);
		BackItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.15f, false);
		//Left 수정 , 옷 수정
		{
			{ // 내려치는 방향 : 앞

				Body_->CreateAnimation("Body.bmp", "FrontWield", 264, 268, 0.08f, false); // 24 한줄에
				Arm_->CreateAnimation("BodyShirts.bmp", "FrontWield", 270, 274, 0.08f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "FrontWield", 282, 287, 0.08f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "FrontWield", 264, 268, 0.08f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "FrontWield", 264, 268, 0.08f, false);
				WieldItem_->CreateAnimation("FrontHoe.bmp", "FrontHoe", 0, 4, 0.08f, false);
				WieldItem_->CreateAnimation("FrontAx.bmp", "FrontAx", 0, 4, 0.08f, false);
				WieldItem_->CreateAnimation("FrontPick.bmp", "FrontPick", 0, 4, 0.08f, false);
			}
			{ // 내려치는 방향 : 오른쪽
				Body_->CreateAnimation("Body.bmp", "RightWield", 192, 196, 0.08f, false);
				Arm_->CreateAnimation("BodyShirts.bmp", "RightWield", 198, 202, 0.08f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "RightWield", 210, 214, 0.08f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "RightWield", 192, 196, 0.08f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "RightWield", 192, 196, 0.08f, false);
				WieldItem_->CreateAnimation("RightHoe.bmp", "RightHoe", 0, 4, 0.08f, false);
				WieldItem_->CreateAnimation("RightAx.bmp", "RightAx", 0, 4, 0.08f, false);
				WieldItem_->CreateAnimation("RightPick.bmp", "RightPick", 0, 4, 0.08f, false);
			}
			{ // 내려치는 방향 : 왼쪽
				Body_->CreateAnimation("Body3.bmp", "LeftWield", 192, 196, 0.08f, false);
				Arm_->CreateAnimation("Body3Shirts.bmp", "LeftWield", 198, 202, 0.08f, false);
				Pants_->CreateAnimation("Body3Shirts.bmp", "LeftWield", 210, 214, 0.08f, false);
				Hair_->CreateAnimation("HairAniL" + HairStyle_ + HairColor_ + ".bmp", "LeftWield", 192, 196, 0.08f, false);
				Shirts_->CreateAnimation("Body3Shirts.bmp", "LeftWield", 192, 196, 0.08f, false);
				WieldItem_->CreateAnimation("LeftHoe.bmp", "LeftHoe", 0, 4, 0.08f, false);
				WieldItem_->CreateAnimation("LeftAx.bmp", "LeftAx", 0, 4, 0.08f, false);
				WieldItem_->CreateAnimation("LeftPick.bmp", "LeftPick", 0, 4, 0.08f, false);

			}
			{ // 내려치는 방향 : 뒤
				Body_->CreateAnimation("Body.bmp", "BackWield", 242, 243, 0.08f, false);
				Arm_->CreateAnimation("BodyShirts.bmp", "BackWield", 151, 153, 0.08f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "BackWield", 260, 261, 0.08f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "BackWield", 242, 243, 0.08f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "BackWield", 242, 243, 0.08f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackHoe", 24, 25, 0.08f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackAx", 66 + 42, 67 + 42, 0.08f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackPick", 66, 67, 0.08f, false);
			}
		}
		////////////////////Hit
		HitItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.1f, false);
		// Left 수정, 옷 수정
		{
			{ // 때리는 방향 : 앞
				Body_->CreateAnimation("Body.bmp", "FrontHit", 96, 101, 0.08f, false); // 24 한줄에
				Arm_->CreateAnimation("BodyShirts.bmp", "FrontHit", 108, 113, 0.08f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "FrontHit", 114, 119, 0.08f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "FrontHit", 96, 101, 0.08f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "FrontHit", 96, 101, 0.08f, false);
				HitItem_->CreateAnimation("FrontSickle.bmp", "FrontSickle", 0, 5, 0.08f, false);
				HitItem_->CreateAnimation("FrontSword.bmp", "FrontSword", 0, 5, 0.08f, false);
			}
			{ // 때리는 방향  : 오른쪽
				Body_->CreateAnimation("Body.bmp", "RightHit", 120, 125, 0.08f, false);
				Arm_->CreateAnimation("BodyShirts.bmp", "RightHit", 132, 137, 0.08f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "RightHit", 138, 143, 0.08f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "RightHit", 120, 125, 0.08f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "RightHit", 120, 125, 0.08f, false);
				HitItem_->CreateAnimation("RightSickle.bmp", "RightSickle", 0, 5, 0.08f, false);
				HitItem_->CreateAnimation("RightSword.bmp", "RightSword", 0, 5, 0.08f, false);
			}
			{ // 때리는 방향  : 왼쪽
				Body_->CreateAnimation("Body3.bmp", "LeftHit", 120, 125, 0.08f, false);
				Arm_->CreateAnimation("Body3Shirts.bmp", "LeftHit", 132, 137, 0.08f, false);
				Pants_->CreateAnimation("Body3Shirts.bmp", "LeftHit", 138, 143, 0.08f, false);
				Hair_->CreateAnimation("HairAniL" + HairStyle_ + HairColor_ + ".bmp", "LeftHit", 120, 125, 0.08f, false);
				Shirts_->CreateAnimation("Body3Shirts.bmp", "LeftHit", 120, 125, 0.08f, false);
				HitItem_->CreateAnimation("LeftSickle.bmp", "LeftSickle", 0, 5, 0.08f, false);
				HitItem_->CreateAnimation("LeftSword.bmp", "LeftSword", 0, 5, 0.08f, false);
			}
			{ // 때리는 방향  : 뒤
				Body_->CreateAnimation("Body.bmp", "BackHit", 144, 149, 0.08f, false);
				Arm_->CreateAnimation("BodyShirts.bmp", "BackHit", 156, 161, 0.08f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "BackHit", 162, 167, 0.08f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "BackHit", 144, 149, 0.08f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "BackHit", 144, 149, 0.08f, false);
				BackItem_->CreateAnimation("BackSickle.bmp", "BackSickle", 0, 5, 0.08f, false);
				BackItem_->CreateAnimation("BackSword.bmp", "BackSword", 0, 5, 0.08f, false);
			}
		}
		WaterItem_->CreateAnimation("Tools.bmp", "ItemIdle", 20, 20, 0.3f, false);
		///////////////////Water
		{
			{ // 물주는 방향 : 앞
				Body_->CreateAnimation("Body.bmp", "FrontWater", 96, 96, 0.8f, false); // 24 한줄에
				Arm_->CreateAnimation("BodyShirts.bmp", "FrontWater", 103, 103, 0.8f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "FrontWater", 114, 114, 0.8f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "FrontWater", 96, 96, 0.8f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "FrontWater", 96, 96, 0.8f, false);
				WaterItem_->CreateAnimation("FrontWateringCan.bmp", "FrontWateringCan", 0, 0, 0.8f, false);
			}
			{ // 물주는 방향  : 오른쪽
				Body_->CreateAnimation("Body.bmp", "RightWater", 171, 171, 0.8f, false);
				Arm_->CreateAnimation("BodyShirts.bmp", "RightWater", 183, 183, 0.8f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "RightWater", 189, 189, 0.8f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "RightWater", 171 + 24, 171 + 24, 0.8f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "RightWater", 171, 171, 0.8f, false);
				WaterItem_->CreateAnimation("RightWateringCan.bmp", "RightWateringCan", 0, 0, 0.8f, false);
			}
			{ // 물주는 방향  : 왼쪽
				Body_->CreateAnimation("Body2.bmp", "LeftWater", 188, 188, 0.8f, false);
				Arm_->CreateAnimation("Body2Shirts.bmp", "LeftWater", 176, 176, 0.8f, false);
				Pants_->CreateAnimation("Body2Shirts.bmp", "LeftWater", 170, 170, 0.8f, false);
				Hair_->CreateAnimation("HairAniL" + HairStyle_ + HairColor_ + ".bmp", "LeftWater", 171 + 24, 171 + 24, 0.8f, false);
				Shirts_->CreateAnimation("Body2Shirts.bmp", "LeftWater", 188, 188, 0.8f, false);
				WaterItem_->CreateAnimation("LeftWateringCan.bmp", "LeftWateringCan", 0, 0, 0.8f, false);
			}
			{ // 물주는 방향  : 뒤
				Body_->CreateAnimation("Body.bmp", "BackWater", 172, 172, 0.8f, false);
				Arm_->CreateAnimation("BodyShirts.bmp", "BackWater", 184, 184, 0.8f, false);
				Pants_->CreateAnimation("BodyShirts.bmp", "BackWater", 190, 190, 0.8f, false);
				Hair_->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "BackWater", 172 - 25, 172 - 25, 0.8f, false);
				Shirts_->CreateAnimation("BodyShirts.bmp", "BackWater", 172, 172, 0.8f, false);
				BackItem_->CreateAnimation("Tools.bmp", "BackWateringCan", 151, 151, 0.8f, false);
			}
		}
	}
	ChangeAni("FrontIdle");
	if (false == GameEngineInput::GetInst()->IsKey("LeftWalk"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftWalk", 'A');
		GameEngineInput::GetInst()->CreateKey("RightWalk", 'D');
		GameEngineInput::GetInst()->CreateKey("BackWalk", 'W');
		GameEngineInput::GetInst()->CreateKey("FrontWalk", 'S');
		GameEngineInput::GetInst()->CreateKey("DebugONOFF", 'Q');
	}

}

void Player::Update()
{
	StateUpdate();
	CameraCheck();
	IsDebugModeONOFF();
	CropsGrowUpdate();
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
///////////////
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////농사 타일맵 관련 함수//////////////////////////////////////////////
bool Player::IsHoeTileCreate()
{
	TileCheckDir();

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

	_Tile->CropsActor_ = GetLevel()->CreateActor<Crops>(static_cast<int>(ORDER::GROUND), CheckSeedSting(_Tile->Seed_)); // 다 자라면 수확하기 위해 엑터로 변경
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

	DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::CROP));
	DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
	DropItem_->SetItem(_Tile->CropsActor_->Item_);
	DropItem_->SetItemKind(_Tile->CropsActor_->ItemKind_);
	CropsTileMap_->DeleteTile(TileIndexX_, TileIndexY_);
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
				IsCropsTile_.erase(StartIter);
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
		GroundTile = GroundTileMap_->GetTile<PlayerTile>((*StartIter)->DirtTilePosX_, (*StartIter)->DirtTilePosY_);
		GroundTile = GroundTileMap_->CreateTile<PlayerTile>((*StartIter)->DirtTilePosX_, (*StartIter)->DirtTilePosY_, "hoeDirt.bmp", 0, static_cast<int>(ORDER::GROUND));
		(*StartIter)->Dirt_ = TileType::HoeDirt;
		GroundTile->Dirt_ = TileType::HoeDirt; //마른땅으로 초기화
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
		HarvestDay_ = 5;
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
		return GetPosition() + float4(0, -64+32);
	}

}




///////////////
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////오브젝트 상호작용 관련 함수/////////////////////////////////////////////

bool Player::IsCheckObjectTile()
{
	TileCheckDir();

	EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);

	if (nullptr == _Tile)
	{
		return false;
	}

	else
	{
		return true;
	}

}
void Player::HitObject()
{
	TileCheckDir();
	if (CurItem_ == PlayerItem::SickleItem && GetLevel()->GetNameCopy() == "FarmLevel")
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);
		if (_Tile->EnvironmentType_ == EnvironmentTileType::Grass)
		{
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();

			TileAnimation* TileAni_ = GetLevel()->CreateActor<TileAnimation>(static_cast<int>(ORDER::TILEEFFECT), "GrassAni");
			if (CurDir_ == PlayerDir::Back)
			{
				TileAni_->SetOrder(static_cast<int>(ORDER::BACKEFFECT));
			}
			TileAni_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80), (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			TileAni_->SetAniString("GrassAni");


			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::ITEM));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::GrassItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			return;
		}

	}
}
void Player::WieldObject()
{
	TileCheckDir();
	if (CurItem_ == PlayerItem::PickItem && GetLevel()->GetNameCopy() == "FarmLevel")
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);
		if (_Tile == nullptr)
		{
			return;
		}
		if (_Tile->EnvironmentType_ == EnvironmentTileType::Stone)
		{
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();

			TileAnimation* TileAni_ = GetLevel()->CreateActor<TileAnimation>(static_cast<int>(ORDER::TILEEFFECT), "StoneAni");
			if (CurDir_ == PlayerDir::Back)
			{
				TileAni_->SetOrder(static_cast<int>(ORDER::BACKEFFECT));
			}
			TileAni_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80), (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			TileAni_->SetAniString("StoneAni");
			//_Tile->IsDestroy_ = true;

			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::ITEM));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::StoneItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			return;
		}

	}
	
	else if (CurItem_ == PlayerItem::AxItem && GetLevel()->GetNameCopy() == "FarmLevel")
	{
		EnvironmentTile* _Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->GetTile<EnvironmentTile>(TileIndexX_, TileIndexY_);
		if (_Tile == nullptr)
		{
			return;
		}
		if (_Tile->EnvironmentType_ == EnvironmentTileType::Branch)
		{
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();
			//_Tile->IsDestroy_ = true;

			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::ITEM));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::BranchItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
			return;
		}

		else if (_Tile->EnvironmentType_ == EnvironmentTileType::Tree)
		{
			
			if (_Tile->DeathCount_ != 0 )
			{
				if (_Tile->DeathCount_ >= 3)
				{
					_Tile->IsShake_ = true;
				}

				if (_Tile->DeathCount_ == 3)
				{
					_Tile->TreeTop_->Death();
					//_Tile->IsDestroy_ = true;

					DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::ITEM));
					DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
					DropItem_->SetItem(PlayerItem::BranchItem);
					DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
				}
				
				_Tile->DeathCount_ -= 1;

				return;
			}

			
			_Tile = FarmObjectEnvironment::MainFarmObject->ReturnFarTileObejctMap_()->CreateTile<EnvironmentTile>(TileIndexX_, TileIndexY_, "Objects.bmp", 23, static_cast<int>(ORDER::GROUND));
			_Tile->TileCol_->Death();
			//_Tile->IsDestroy_ = true;

			DropItem* DropItem_ = GetLevel()->CreateActor<DropItem>(static_cast<int>(ORDER::ITEM));
			DropItem_->SetPosition({ (static_cast<float>(TileIndexX_) + 0.5f) * (MapScaleX_ / 80) , (static_cast<float>(TileIndexY_) + 0.5f) * (MapScaleY_ / 65) });
			DropItem_->SetItem(PlayerItem::BranchItem);
			DropItem_->SetItemKind(PlayerItemKind::ObjectItem);
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
	else if (CurHairColor_ == PlayerHairColor::Grey)
	{
		return "Grey";
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
		return "First";
	}
	else if (CurHairStyle_ == PlayerHairStyle::Second)
	{
		return "Second";
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
}

void Player::IsDebugModeONOFF()
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugONOFF"))
	{
		GetLevel()->IsDebugModeSwitch();
	}
}