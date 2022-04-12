#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

class PlayerTile : public Tile
{
public:
	
	TileType Type;
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
	
protected:
private:
	GameEngineRendererTileMap* TileMap_;
	
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
	
	void UpdateTileMap();
	void DirCreateTile();
	
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

