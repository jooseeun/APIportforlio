#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

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


protected:
private:
	GameEngineRendererTileMap* TileMap_;
	
	
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
	void EatUpdate();

	void HitStart();
	void IdleStart();
	void WieldStart();
	void WalkStart();
	void EatStart();

};

