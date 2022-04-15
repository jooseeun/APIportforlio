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
	CurItemKind_(PlayerItemKind::NoItem),
	CurState_(PlayerState::Idle),
	CurItem_(PlayerItem::Nothing),
	CurHairStyle_(PlayerHairStyle::First),
	CurHairColor_(PlayerHairColor::Red),
	CurShirts_(PlayerShirts::First)
{
	ArrAnimationName[static_cast<int>(PlayerState::Idle)] = "Idle";
	ArrAnimationName[static_cast<int>(PlayerState::Walk)] = "Walk";
	ArrAnimationName[static_cast<int>(PlayerState::Wield)] = "Wield";
	ArrAnimationName[static_cast<int>(PlayerState::Hit)] = "Hit";
	ArrAnimationName[static_cast<int>(PlayerState::Water)] = "Water";
	ArrAnimationName[static_cast<int>(PlayerState::Seed)] = "Idle";

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
		case PlayerState::Water:
			WaterStart();
			break;
		case PlayerState::Seed:
			SeedStart();
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
	case PlayerState::Water:
		WaterUpdate();
		break;
	case PlayerState::Seed:
		SeedUpdate();
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
	int HairNum_ = static_cast<int>(CurHairStyle_);
	std::string HairColor_ = GetHairColorString();
	std::string HairStyle_ = GetHairStyleString();
	Body = CreateRendererToScale("Body.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Pants = CreateRendererToScale("BodyShirts.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER));
	Shirts = CreateRendererToScale("BodyShirts.bmp", { 32, 32 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER);
	Hair = CreateRendererToScale("Hair" + HairColor_ + ".bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,4 });
	Arm = CreateRendererToScale("BodyShirts.bmp", { 64, 128 }, static_cast<int>(ORDER::PLAYER), RenderPivot::CENTER, { 0,2 });
	//Tool = CreateRendererToScale("Tools.bmp", { 56, 112 }, 15);

	////////////idle
	{ 
		{// 캐릭터 front idle 상태
			Body->CreateAnimation("Body.bmp", "FrontIdle", 0, 0, 0.15f, false); // 24 한줄에
			Arm->CreateAnimation("BodyShirts.bmp", "FrontIdle", 6, 6, 0.15f, false);
			Pants->CreateAnimation("BodyShirts.bmp", "FrontIdle", 18, 18, 0.15f, false);
			Hair->CreateAnimation("Hair"+HairColor_+".bmp", "FrontIdle", HairNum_, HairNum_, 0.15f, false);
			Shirts->CreateAnimation("BodyShirts.bmp", "FrontIdle", 0, 0, 0.15f, false);
		}
		{// 캐릭터 right idle 상태
			Body->CreateAnimation("Body.bmp", "RightIdle", 24, 24, 0.15f, false);//+24
			Arm->CreateAnimation("BodyShirts.bmp", "RightIdle", 30, 30, 0.15f, false);
			Pants->CreateAnimation("BodyShirts.bmp", "RightIdle", 42, 42, 0.15f, false);
			Hair->CreateAnimation("Hair" + HairColor_ + ".bmp", "RightIdle", HairNum_ +8, HairNum_ +8, 0.15f, false);
			Shirts->CreateAnimation("BodyShirts.bmp", "RightIdle", 24, 24, 0.15f, false);//+24
		}
		{// 캐릭터 Left idle 상태
			Body->CreateAnimation("Body2.bmp", "LeftIdle", 47, 47, 0.15f, false);
			Arm->CreateAnimation("Body2Shirts.bmp", "LeftIdle", 41, 41, 0.15f, false);
			Pants->CreateAnimation("Body2Shirts.bmp", "LeftIdle", 29, 29, 0.15f, false);
			Hair->CreateAnimation("HairL" + HairColor_ + ".bmp", "LeftIdle", 7 - HairNum_ + 8, 7 - HairNum_ + 8, 0.15f, false);
			Shirts->CreateAnimation("Body2Shirts.bmp", "LeftIdle", 47, 47, 0.15f, false);
		}
		{// 캐릭터 Back idle 상태
			Body->CreateAnimation("Body.bmp", "BackIdle", 48, 48, 0.15f, false); // 24 한줄에
			Arm->CreateAnimation("BodyShirts.bmp", "BackIdle", 54, 54, 0.15f, false);
			Pants->CreateAnimation("BodyShirts.bmp", "BackIdle", 66, 66, 0.15f, false);
			Hair->CreateAnimation("Hair" + HairColor_ + ".bmp", "BackIdle", HairNum_ +16, HairNum_ +16, 0.15f, false);
			Shirts->CreateAnimation("BodyShirts.bmp", "BackIdle", 48, 48, 0.15f, false);
		}

	}
	////////////////move
	{
		{ // 캐릭터 아래로 걷는 모션
			Body->CreateAnimation("Body.bmp", "FrontWalk", 1, 2, 0.3f, true);
			Arm->CreateAnimation("BodyShirts.bmp", "FrontWalk", 7, 8, 0.3f, true);
			Pants->CreateAnimation("BodyShirts.bmp", "FrontWalk", 19, 20, 0.3f, true);
			Hair->CreateAnimation("HairDown" + HairColor_ + ".bmp", "FrontWalk", HairNum_, HairNum_, 0.3f, true);
			Shirts->CreateAnimation("BodyShirts.bmp", "FrontWalk", 1, 2, 0.3f, true);
		}
		{ // 캐릭터 오른쪽으로 걷는 모션
			Body->CreateAnimation("Body.bmp", "RightWalk", 25, 26, 0.4f, true);
			Arm->CreateAnimation("BodyShirts.bmp", "RightWalk", 31, 32, 0.4f, true);
			Pants->CreateAnimation("BodyShirts.bmp", "RightWalk", 43, 44, 0.4f, true);
			Hair->CreateAnimation("HairDown" + HairColor_ + ".bmp", "RightWalk", HairNum_ + 8, HairNum_ + 8, 0.4f, true);
			Shirts->CreateAnimation("BodyShirts.bmp", "RightWalk", 25, 26, 0.4f, true);
		}
		{ // 캐릭터 왼쪽으로 걷는 모션
			Body->CreateAnimation("Body2.bmp", "LeftWalk", 45, 46, 0.4f, true);
			Arm->CreateAnimation("Body2Shirts.bmp", "LeftWalk", 40, 41, 0.4f, true);
			Pants->CreateAnimation("Body2Shirts.bmp", "LeftWalk", 27, 28, 0.4f, true);
			Hair->CreateAnimation("HairDownL" + HairColor_ + ".bmp", "LeftWalk", 7 - HairNum_ + 8, 7 - HairNum_ + 8, 0.4f, true);
			Shirts->CreateAnimation("Body2Shirts.bmp", "LeftWalk", 45, 46, 0.4f, true);
		}
		{ // 캐릭터 위로 걷는 모션
			Body->CreateAnimation("Body.bmp", "BackWalk", 49, 50, 0.3f, true);
			Arm->CreateAnimation("BodyShirts.bmp", "BackWalk", 55, 56, 0.3f, true);
			Pants->CreateAnimation("BodyShirts.bmp", "BackWalk", 67, 68, 0.3f, true);
			Hair->CreateAnimation("HairDown" + HairColor_ + ".bmp", "BackWalk", HairNum_ + 16, HairNum_ + 16, 0.3f, true);
			Shirts->CreateAnimation("BodyShirts.bmp", "BackWalk", 49, 50, 0.3f, true);
		}
		//////////////////Wield
		//Left 수정 , 옷 수정
		{
			{ // 내려치는 방향 : 앞

				Body->CreateAnimation("Body.bmp", "FrontWield", 264, 268, 0.1f, true); // 24 한줄에
				Arm->CreateAnimation("BodyShirts.bmp", "FrontWield", 270, 274, 0.1f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "FrontWield", 282, 287, 0.1f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "FrontWield", 264, 268, 0.1f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "FrontWield", 264, 268, 0.1f, true);
			}
			{ // 내려치는 방향 : 오른쪽
				Body->CreateAnimation("Body.bmp", "RightWield", 192, 196, 0.1f, true);
				Arm->CreateAnimation("BodyShirts.bmp", "RightWield", 198, 202, 0.1f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "RightWield", 210, 214, 0.1f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "RightWield", 192, 196, 0.1f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "RightWield", 192, 196, 0.1f, true);
			}
			{ // 내려치는 방향 : 왼쪽
				Body->CreateAnimation("Body3.bmp", "LeftWield", 192, 196, 0.1f, true);
				Arm->CreateAnimation("Body3Shirts.bmp", "LeftWield", 198, 202, 0.1f, true);
				Pants->CreateAnimation("Body3Shirts.bmp", "LeftWield", 210, 214, 0.1f, true);
				Hair->CreateAnimation("HairAniL" + HairStyle_ + HairColor_ + ".bmp", "LeftWield", 192, 196, 0.1f, true);
				Shirts->CreateAnimation("Body3Shirts.bmp", "LeftWield", 192, 196, 0.1f, true);
			}
			{ // 내려치는 방향 : 뒤
				Body->CreateAnimation("Body.bmp", "BackWield", 242, 243, 0.3f, true);
				Arm->CreateAnimation("BodyShirts.bmp", "BackWield", 151, 153, 0.2f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "BackWield", 260, 261, 0.3f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "BackWield", 242, 243, 0.3f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "BackWield", 242, 243, 0.3f, true);
			}
		}
		////////////////////Hit
		// Left 수정, 옷 수정
		{
			{ // 때리는 방향 : 앞
				Body->CreateAnimation("Body.bmp", "FrontHit", 96, 101, 0.05f, true); // 24 한줄에
				Arm->CreateAnimation("BodyShirts.bmp", "FrontHit", 108, 113, 0.05f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "FrontHit", 114, 119, 0.05f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "FrontHit", 96, 101, 0.05f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "FrontHit", 96, 101, 0.05f, true);
			}
			{ // 때리는 방향  : 오른쪽
				Body->CreateAnimation("Body.bmp", "RightHit", 120, 125, 0.05f, true);
				Arm->CreateAnimation("BodyShirts.bmp", "RightHit", 132, 137, 0.05f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "RightHit", 138, 143, 0.05f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "RightHit", 120, 125, 0.05f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "RightHit", 120, 125, 0.05f, true);
			}
			{ // 때리는 방향  : 왼쪽
				Body->CreateAnimation("Body3.bmp", "LeftHit", 120, 125, 0.05f, true);
				Arm->CreateAnimation("Body3Shirts.bmp", "LeftHit", 132, 137, 0.05f, true);
				Pants->CreateAnimation("Body3Shirts.bmp", "LeftHit", 138, 143, 0.05f, true);
				Hair->CreateAnimation("HairAniL" + HairStyle_ + HairColor_ + ".bmp", "LeftHit", 120, 125, 0.05f, true);
				Shirts->CreateAnimation("Body3Shirts.bmp", "LeftHit", 120, 125, 0.05f, true);
			}
			{ // 때리는 방향  : 뒤
				Body->CreateAnimation("Body.bmp", "BackHit", 144, 149, 0.05f, true);
				Arm->CreateAnimation("BodyShirts.bmp", "BackHit", 156, 161, 0.05f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "BackHit", 162, 167, 0.05f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "BackHit", 144, 149, 0.05f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "BackHit", 144, 149, 0.05f, true);
			}
		}

		///////////////////Water
		{
			{ // 때리는 방향 : 앞
				Body->CreateAnimation("Body.bmp", "FrontWater", 216, 217, 0.1f, true); // 24 한줄에
				Arm->CreateAnimation("BodyShirts.bmp", "FrontWater", 222, 223, 0.1f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "FrontWater", 234, 235, 0.1f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "FrontWater", 216, 217, 0.1f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "FrontWater", 216, 217, 0.1f, true);
			}
			{ // 때리는 방향  : 오른쪽
				Body->CreateAnimation("Body.bmp", "RightWater", 120, 125, 0.1f, true);
				Arm->CreateAnimation("BodyShirts.bmp", "RightWater", 132, 137, 0.1f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "RightWater", 138, 143, 0.1f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "RightWater", 120, 125, 0.1f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "RightWater", 120, 125, 0.1f, true);
			}
			{ // 때리는 방향  : 왼쪽
				Body->CreateAnimation("Body3.bmp", "LeftWater", 120, 125, 0.1f, true);
				Arm->CreateAnimation("Body3Shirts.bmp", "LeftWater", 132, 137, 0.1f, true);
				Pants->CreateAnimation("Body3Shirts.bmp", "LeftWater", 138, 143, 0.1f, true);
				Hair->CreateAnimation("HairAniL" + HairStyle_ + HairColor_ + ".bmp", "LeftWater", 120, 125, 0.1f, true);
				Shirts->CreateAnimation("Body3Shirts.bmp", "LeftWater", 120, 125, 0.1f, true);
			}
			{ // 때리는 방향  : 뒤
				Body->CreateAnimation("Body.bmp", "BackWater", 144, 149, 0.1f, true);
				Arm->CreateAnimation("BodyShirts.bmp", "BackWater", 156, 161, 0.1f, true);
				Pants->CreateAnimation("BodyShirts.bmp", "BackWater", 162, 167, 0.1f, true);
				Hair->CreateAnimation("HairAni" + HairStyle_ + HairColor_ + ".bmp", "BackWater", 144, 149, 0.1f, true);
				Shirts->CreateAnimation("BodyShirts.bmp", "BackWater", 144, 149, 0.1f, true);
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

void Player::DirHoeDirtCreateTile() 
{
	TileCheckDir();
	PlayerTile* Tile = TileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "hoeDirt.bmp", 0, static_cast<int>(ORDER::GROUND));
	Tile->Dirt_ = TileType::HoeDirt;
	Tile->Seed_ = SeedType::Max;
}

void Player::DirWaterDirtCreateTile() 
{

	TileCheckDir();
	PlayerTile* Tile = TileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "hoeDirtDark.bmp", 0, static_cast<int>(ORDER::GROUND));
	Tile->Dirt_ = TileType::HoeDirt;
	Tile->Seed_ = SeedType::Max;

}
void Player::DirSeedCreateTile()
{
	
	TileCheckDir();
	PlayerTile* Tile = TileMap_->CreateTile<PlayerTile>(TileIndexX_, TileIndexY_, "Crops.bmp", 0, static_cast<int>(ORDER::GROUND));
	Tile->Dirt_ = TileType::HoeDirt;
	Tile->Seed_ = SeedType::Max;

}
void Player::TileCheckDir() 
{
	if (CurDir_ == PlayerDir::Front) {
		TileIndexX_ = static_cast<int>(GetPosition().x / 64);
		TileIndexY_ = static_cast<int>((GetPosition().y + 32.0f) / 64) + 1;
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
bool Player::IsHoeTileCreate()
{
	TileCheckDir();
	
	PlayerTile* Tile = TileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);

	if (nullptr == Tile && PlayerItem::HoeItem == CurItem_) // 맨땅이라면
	{
		return true;
	}

	return false;
}

bool Player::IsWaterTileCreate()
{
	TileCheckDir();
	PlayerTile* Tile = TileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);
	if (nullptr == Tile)
	{
		return false;
	}
	else 
	{
		if (CurItem_ == PlayerItem::WateringItem && TileType::HoeDirt == Tile->Dirt_) // 씨앗상태와 관계없이 물은 준다.
		{
			return true;
		}
		return false;
	}

}
bool Player::IsSeedTileCreate()
{
	TileCheckDir();

	PlayerTile* Tile = TileMap_->GetTile<PlayerTile>(TileIndexX_, TileIndexY_);
	if (nullptr == Tile)
	{
		return false;
	}
	if (CurItemKind_ == PlayerItemKind::SeedItem && SeedType::Max == Tile->Seed_) // Nothing 만아니면 씨앗심을 수 있음
	{
		return true;
	}
	return false;
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