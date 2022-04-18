#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

class PlayerTile : public Tile
{
public:
	PlayerTile():
	Dirt_(TileType::Max),
	Seed_(SeedType::Max),
	IsSeed_(false)
	{

	}

	TileType Dirt_;
	SeedType Seed_;
	bool IsSeed_;
	

};

class GameEngineImage;
class GameEngineCollision;
class Player:public GameEngineActor
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetMapScale(float _X,float _Y);
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
		else
		{
			CurItemKind_ = PlayerItemKind::NoItem;
		}

	}
	
protected:
private:
	
	PlayerHairColor CurHairColor_;
	PlayerHairStyle CurHairStyle_;
	PlayerShirts CurShirts_;

	std::string GetHairColorString();
	std::string GetHairStyleString();
	std::string GetItemString();
	 GameEngineRenderer* Body;
	GameEngineRenderer* Hair;
	GameEngineRenderer* Shirts;
	GameEngineRenderer* Pants;
	GameEngineRenderer* Arm;
	GameEngineRenderer* WieldItem;
	GameEngineRenderer* HitItem;
	GameEngineImage* MapColImage_;

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
	void ChangeAni(std::string _Name);
	void CameraCheck();

	
private:


	const char* ArrAnimationName[static_cast<int>(PlayerState::Max)];
	float4 ArrCheckDir[static_cast<int>(PlayerDir::Max)];
	int TileCheckDirX[static_cast<int>(PlayerDir::Max)];
	int TileCheckDirY[static_cast<int>(PlayerDir::Max)];

	PlayerState CurState_;
	PlayerDir CurDir_;
	PlayerDir PrevDir_;

	 PlayerItemKind CurItemKind_;
	 PlayerItem CurItem_;

	void DirAnimationChange();

	bool DirKeyCheck();
	bool IsWalkKey();
	bool IsIdleKey();
	void KeyMove();
	std::string GetDirString();

private:
	GameEngineRendererTileMap* GroundTileMap_;
	GameEngineRendererTileMap* CropsTileMap_;

	void CurTileIndexCheck();
	bool IsHoeTileCreate();
	bool IsWaterTileCreate();
	void DirHoeDirtCreateTile();
	void DirWaterDirtCreateTile();
	void DirSeedCreateTile();
	bool IsSeedTileCreate();
	void TileCheckDir();

	int TileIndexX_;
	int TileIndexY_;

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

	void HitStart();
	void IdleStart();
	void WieldStart();
	void WalkStart();
	void WaterStart();
	void SeedStart();

};

