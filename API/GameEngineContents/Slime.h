#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineSound.h>

// ???? :
class GameEngineCollision;
class GameEngineRenderer;
class Slime : public GameEngineActor
{
public:
	// constrcuter destructer
	Slime();
	~Slime();

	// delete Function
	Slime(const Slime& _Other) = delete;
	Slime(Slime&& _Other) noexcept = delete;
	Slime& operator=(const Slime& _Other) = delete;
	Slime& operator=(Slime&& _Other) noexcept = delete;
	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		MineTileMap_ = _TileMap;
	}
protected:

private:
	GameEngineSoundPlayer Sound_;

	bool IsDeath_;
	bool Hit_;
	bool Start_;
	float4 InitPos_;
	float4 Move_;
	MonsterDir CurDir_;
	MonsterDir PreDir_;
	int Hp_;

	GameEngineRendererTileMap* MineTileMap_;
	GameEngineRenderer* SlimeRender_;
	GameEngineCollision* SlimeCol_;

	void MoveUpdate(); 
	void CurAniUpdate();
	void DeathCheck();

	void Start() override;
	void Update() override;
};

