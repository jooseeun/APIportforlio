#pragma once
#include "PlayerEnum.h"
#include "Time.h"
#include "Crops.h"
#include "FarmObjectEnvironment.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>


class PlayerTile : public Tile
{
public:
	PlayerTile()
		:Dirt_(TileType::Max),
		Seed_(SeedType::Max),
		IsSeed_(false),
		SeedDay_(0),
		Isharvest_(false),
		DirtTilePosX_(-1),
		DirtTilePosY_(-1)
	{

	}
	~PlayerTile()
	{
		if (CropsActor_ != nullptr)
		{
			CropsActor_->Death();
		}
	}

	TileType Dirt_;
	SeedType Seed_;
	bool IsSeed_;
	bool Isharvest_;
	int DirtTilePosX_;
	int DirtTilePosY_;
	int SeedDay_;
	Crops* CropsActor_;

};

class GameEngineImage;
class GameEngineCollision;
class Player :public GameEngineActor
{
public:
	static Player* MainPlayer;

	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetMapScale(float _X, float _Y);
	void SetColMapName(const std::string& _Name);
	void SetSideLevel(std::string _Pre, std::string _Next, std::string _Entry);

	inline void SetGroundTileMap(GameEngineRendererTileMap* _TileMap)
	{
		GroundTileMap_ = _TileMap;
	}
	inline void SetCropsTileMap(GameEngineRendererTileMap* _TileMap)
	{
		CropsTileMap_ = _TileMap;
	}
	inline void SetHairNum(PlayerHairStyle _Num)
	{
		CurHairStyle_ = _Num;
	}
	inline void SetHairColor(PlayerHairColor _Color)
	{
		CurHairColor_ = _Color;
	}
	inline void SetShirts(PlayerShirts _Shirts)
	{
		CurShirts_ = _Shirts;
	}
	inline void SetSelectItem(PlayerItem _Item)
	{
		//item kind 자동 설정해주는 함수 만들어야됨!
		CurItem_ = _Item;
		SetItemKind(_Item);

	}
	inline void SetItemKind(PlayerItem _Item)
	{
		if (10 < static_cast<int>(_Item) && static_cast<int>(_Item) < 20)
		{
			CurItemKind_ = PlayerItemKind::WieldItem;
		}
		else if (20 < static_cast<int>(_Item) && static_cast<int>(_Item) < 30)
		{
			CurItemKind_ = PlayerItemKind::WaterItem;
		}
		else if (30 < static_cast<int>(_Item) && static_cast<int>(_Item) < 40)
		{
			CurItemKind_ = PlayerItemKind::HitItem;
		}
		else if (40 < static_cast<int>(_Item) && static_cast<int>(_Item) < 50)
		{
			CurItemKind_ = PlayerItemKind::SeedItem;
		}
		else if (50 < static_cast<int>(_Item) && static_cast<int>(_Item) < 60)
		{
			CurItemKind_ = PlayerItemKind::CropsItem;
		}
		else if (60 < static_cast<int>(_Item) && static_cast<int>(_Item) < 70)
		{
			CurItemKind_ = PlayerItemKind::ObjectItem;
		}
		else
		{
			CurItemKind_ = PlayerItemKind::NoItem;
		}

	}
	inline void SetIsLeftMouseON()
	{
		IsLeftMouse = true;
	}
	inline void SetIsLeftMouseOFF()
	{
		IsLeftMouse = false;
	}
protected:
private:

	PlayerHairColor CurHairColor_;
	PlayerHairStyle CurHairStyle_;
	PlayerShirts CurShirts_;

	std::string GetHairColorString();
	std::string GetHairStyleString();
	std::string GetItemString();
	GameEngineRenderer* Body_;
	GameEngineRenderer* Hair_;
	GameEngineRenderer* Shirts_;
	GameEngineRenderer* Pants_;
	GameEngineRenderer* Arm_;
	GameEngineRenderer* WieldItem_;
	GameEngineRenderer* HitItem_;
	GameEngineRenderer* WaterItem_;
	GameEngineRenderer* BackItem_;
	GameEngineImage* MapColImage_;

	GameEngineCollision* PlayerCol_;

	std::string ColMap_;
	std::string NextLevel_;
	std::string PreLevel_;
	std::string EntryLevel_;
	float MapScaleY_;
	float MapScaleX_;
	float Speed_;

	void Update() override;
	void Start() override;
	void Render() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;


	void ChangeAni(std::string _Name);
	void CameraCheck();
	void IsDebugModeONOFF();

private:
	const char* ArrAnimationName[static_cast<int>(PlayerState::Max)];
	float4 ArrCheckDir[static_cast<int>(PlayerDir::Max)];
	int TileCheckDirX[static_cast<int>(PlayerDir::Max)];
	int TileCheckDirY[static_cast<int>(PlayerDir::Max)];

	PlayerState CurState_;
	PlayerDir CurDir_;
	PlayerDir PrevDir_;

	int CurDay_;
	int CurHour_;

	PlayerItemKind CurItemKind_;
	PlayerItem CurItem_;

	void DirAnimationChange();

	bool DirKeyCheck();
	bool IsWalkKey();
	bool IsIdleKey();
	bool IsLeftMouse;
	std::string GetDirString();


private:
	GameEngineRendererTileMap* GroundTileMap_;
	GameEngineRendererTileMap* CropsTileMap_;
	std::list< PlayerTile*> IsCropsTile_;

	float4 CreateCropPos_;
	int CropNum_;


	bool IsCheckHarvestTile();
	void CropsHarvest();
	std::string CheckSeedSting(SeedType _Type);

	void CropsGrowUpdate();
	void CropsGrowDay(PlayerTile* _Tile);
	void DayChangeSetCrops();
	void CropsHarvestSet(PlayerTile* _Tile);


	bool IsHoeTileCreate();
	bool IsWaterTileCreate();
	void DirHoeDirtCreateTile();
	void DirWaterDirtCreateTile();
	void DirSeedCreateTile();
	bool IsSeedTileCreate();
	void TileCheckDir();

	int TileIndexX_;
	int TileIndexY_;

private:
	bool IsCheckObjectTile();
	void WieldObject();
	void HitObject();

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();

private:
	void IdleUpdate();
	void WieldUpdate();
	void HitUpdate();
	void WalkUpdate();
	void WaterUpdate();
	void SeedUpdate();
	void HarvestUpdate();

	void HitStart();
	void IdleStart();
	void WieldStart();
	void WalkStart();
	void WaterStart();
	void SeedStart();
	void HarvestStart();

};

