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

	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		TileMap_ = _TileMap;
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
	inline void GetSelectItem(PlayerItem _Item)
	{
		//item kind 자동 설정해주는 함수 만들어야됨!
		CurItem_ = _Item;

	}
	
protected:
private:
	
	PlayerHairColor CurHairColor_;
	PlayerHairStyle CurHairStyle_;
	PlayerShirts CurShirts_;

	std::string GetHairColorString();
	std::string GetHairStyleString();
	GameEngineRenderer* Body;
	GameEngineRenderer* Hair;
	GameEngineRenderer* Shirts;
	GameEngineRenderer* Pants;
	GameEngineRenderer* Arm;
	GameEngineRenderer* Tool;
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

	PlayerHave CurItemKind_;
	PlayerItem CurItem_;

	void DirAnimationChange();

	bool DirKeyCheck();
	bool IsMoveKey();
	void KeyMove();
	std::string GetDirString();

private:
	GameEngineRendererTileMap* TileMap_;

	void CurTileIndexCheck();
	bool IsHeoTileCreate();
	bool IsWaterTileCreate();
	void DirGroundCreateTile();
	bool IsSeedTileCreate();

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();

private:
	void IdleUpdate();
	void WieldUpdate();
	void HitUpdate();
	void WalkUpdate();
	void WaterUpdate();

	void HitStart();
	void IdleStart();
	void WieldStart();
	void WalkStart();
	void WaterStart();

};

