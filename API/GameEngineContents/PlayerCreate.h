#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class GameEngineCollision;
class PlayerCreate : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerCreate();
	~PlayerCreate();

	// delete Function
	PlayerCreate(const PlayerCreate& _Other) = delete;
	PlayerCreate(PlayerCreate&& _Other) noexcept = delete;
	PlayerCreate& operator=(const PlayerCreate& _Other) = delete;
	PlayerCreate& operator=(PlayerCreate&& _Other) noexcept = delete;

protected:


private:
	PlayerHairColor CurHairColor_;
	PlayerHairStyle CurHairStyle_;
	PlayerShirts CurShirts_;
	PlayerPants CurPants_;
	GameEngineSoundPlayer Sound_;

	void Start() override;
	void Update() override;
	GameEngineCollision* LeftCol1;
	GameEngineCollision* LeftCol2;
	GameEngineCollision* LeftCol3;
	GameEngineCollision* LeftCol4;
	GameEngineCollision* RightCol1;
	GameEngineCollision* RightCol2;
	GameEngineCollision* RightCol3;
	GameEngineCollision* RightCol4;
	GameEngineCollision* Ok_;
	void PlayerUpdate();
	std::string GetPantsStyleString();
	std::string GetShirtsStyleString();
	std::string GetHairColorString();
	std::string GetHairStyleString();

	GameEngineRenderer* Body_;
	GameEngineRenderer* Hair_;
	GameEngineRenderer* Shirts_;
	GameEngineRenderer* Pants_;
	GameEngineRenderer* Arm_;
};

