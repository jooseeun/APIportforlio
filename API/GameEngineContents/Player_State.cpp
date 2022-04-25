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
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngine/GameEngineCollision.h>


void Player::IdleUpdate()
{
	if (true == IsWalkKey())
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if (true == IsLeftMouse)
	{
		if (CurItem_ == PlayerItem::SickleItem && GetLevel()->GetNameCopy() == "FarmLevel" && true == IsCheckHarvestTile()) //낫을 들었을때 수확할수 있는 타일이면
		{
			ChangeState(PlayerState::Harvest);
			return;
		}

	}

	if (true == IsLeftMouse)
	{

		if (CurItemKind_ == PlayerItemKind::WieldItem)
		{
			ChangeState(PlayerState::Wield);
		}
		else if (CurItemKind_ == PlayerItemKind::HitItem)
		{
			ChangeState(PlayerState::Hit);
		}
		else if (CurItemKind_ == PlayerItemKind::WaterItem)
		{
			ChangeState(PlayerState::Water);
		}
		else if (CurItemKind_ == PlayerItemKind::SeedItem)
		{
			ChangeState(PlayerState::Seed);
		}
		else if (CurItemKind_ == PlayerItemKind::NoItem)
		{
			ChangeState(PlayerState::Idle);
		}
	}

}

void Player::WieldUpdate()
{
	if (true == Arm_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
	
}
void Player::HitUpdate()
{
	if (true == Arm_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
}
void Player::HarvestUpdate()
{
	if (true == Arm_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
}
void Player::WaterUpdate()
{
	if (true == Arm_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::SeedUpdate()
{
	if (true == Arm_->IsEndAnimation())
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::WalkUpdate()
{
	DirKeyCheck();

	float4 NextPos;
	float4 CheckPos = ArrCheckDir[static_cast<int>(CurDir_)];
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("BackWalk"))
	{
		Move += float4::UP;
	}

	else if (true == GameEngineInput::GetInst()->IsPress("FrontWalk"))
	{
		Move += float4::DOWN;
	}

	if (true == GameEngineInput::GetInst()->IsPress("RightWalk"))
	{
		Move += float4::RIGHT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("LeftWalk"))
	{
		Move += float4::LEFT;
	}

	
	Move.Normal2D();
	NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
	CheckPos += NextPos;


	{

		int Color = MapColImage_->GetImagePixel(CheckPos);


		if (true == PlayerCol_->NextPostCollisionCheck("Crops", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect))
		{
			Move = float4::ZERO;
		}
		else if (true == PlayerCol_->NextPostCollisionCheck("Tree", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect))
		{
			Move = float4::ZERO;
		}
		else if (true == PlayerCol_->NextPostCollisionCheck("Stone", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect))
		{
			Move = float4::ZERO;
		}
		else if (true == PlayerCol_->NextPostCollisionCheck("Branch", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect))
		{
			Move = float4::ZERO;
		}
		else if (true == PlayerCol_->NextPostCollisionCheck("Grass", Move * GameEngineTime::GetDeltaTime() * Speed_, CollisionType::Rect, CollisionType::Rect))
		{
			Move = float4::ZERO;
		}


		if (RGB(255, 0, 0) != Color)
		{
			SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);
		}
		
		if (RGB(0, 255, 255) == Color)
		{
			GameEngine::GetInst().ChangeLevel(PreLevel_);
		}
		else if (RGB(0, 0, 255) == Color)
		{
			GameEngine::GetInst().ChangeLevel(NextLevel_);
		}
		else if (RGB(255, 255, 0) == Color)
		{
			GameEngine::GetInst().ChangeLevel(EntryLevel_);
		}
		else if (RGB(25, 25, 25) == Color)
		{
			GameEngine::GetInst().ChangeLevel("ForestLevel");
		}

	
	} 

	if (true == IsIdleKey())
	{
		ChangeState(PlayerState::Idle);
	}
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	SetIsLeftMouseOFF();
}

void Player::HarvestStart()
{
	CropsHarvest();
}
void Player::HitStart()
{
	if (true == IsCheckObjectTile()) //오브젝트가 앞에 있다면 
	{
		HitObject();
	}
}

void Player::WalkStart()
{
	
}

void Player::WieldStart()
{
	if (true == IsCheckObjectTile()) //오브젝트가 앞에 있는지 확인하는 함수
	{
		WieldObject();
	}

	if (true == IsHoeTileCreate()&&"FarmLevel" == this->GetLevel()->GetNameCopy())
	{
		DirHoeDirtCreateTile();
	}
}

void Player::WaterStart()
{
	if (true == IsWaterTileCreate() && "FarmLevel" == this->GetLevel()->GetNameCopy())
	{
		DirWaterDirtCreateTile();
	}
}

void Player::SeedStart()
{
	if (true == IsSeedTileCreate() && "FarmLevel" == this->GetLevel()->GetNameCopy())
	{
		DirSeedCreateTile();
	}
}

std::string Player::GetDirString()
{
	if (CurDir_ == PlayerDir::Front)
	{
		return "Front";
	}
	else if (CurDir_ == PlayerDir::Back)
	{
		return "Back";
	}
	else if (CurDir_ == PlayerDir::Left)
	{
		return "Left";
	}
	else if (CurDir_ == PlayerDir::Right)
	{
		return "Right";
	}
	return "";
}
