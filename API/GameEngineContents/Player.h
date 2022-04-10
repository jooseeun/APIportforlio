#pragma once
#include <GameEngine/GameEngineActor.h>
enum PlayerState
{
	Idle,
	Wield,
	Hit,
	Move
};

enum PlayerDir
{
	Front,
	Back,
	Left,
	Right
};

enum PlayerHave
{
	HitItem,
	WieldItem,
	EatItem,
	ElseItem,
	NoItem
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

	GameEngineImage* MapColImage_;
	void SetMapScale(float _X,float _Y);
	void SetColMapName(const std::string& _Name);
	void CameraCheck();
	void ChangeAni(std::string _Name);
	void SetSideLevel(std::string _Pre, std::string _Next, std::string _Entry);
protected:

private:
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

	GameEngineRenderer* Body;
	GameEngineRenderer* Hair;
	GameEngineRenderer* Shirts;
	GameEngineRenderer* Pants;
	GameEngineRenderer* Arm;
	
private:
	PlayerState CurState_;
	PlayerDir CurDir_;
	PlayerHave CurItem_;
	
	bool IsMoveKey();
	void KeyMove();

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();

private:
	void IdleUpdate();
	void WieldUpdate();
	void HitUpdate();
	void MoveUpdate();

	void HitStart();
	void IdleStart();
	void WieldStart();
	void MoveStart();

};

