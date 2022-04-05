#pragma once
#include <GameEngine/GameEngineActor.h>
enum PlayerState
{
	Idle,
	Attack,
	Move
};

enum PlayerDir
{
	Left,
	Right,
	Up,
	Down
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

protected:

private:
	std::string ColMap_;
	float MapScaleY_;
	float MapScaleX_;
	float Speed_;

	void Update() override;
	void Start() override;
	void Render() override;


private:
	PlayerState CurState_;
	GameEngineRenderer* Render1;

	bool IsMoveKey();
	void KeyMove();

public:
	void ChangeState(PlayerState _State);
	void StateUpdate();

private:
	void IdleUpdate();
	void AttackUpdate();
	void MoveUpdate();

	void IdleStart();
	void AttackStart();
	void MoveStart();

};

