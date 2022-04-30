#pragma once
#include "PlayerEnum.h"
#include <GameEngine/GameEngineRendererTileMap.h>

// Ό³Έν :
class GameEngineCollision;
class GameEngineRenderer;
class Bug : public GameEngineActor
{
public:
	// constrcuter destructer
	Bug();
	~Bug();

	// delete Function
	Bug(const Bug& _Other) = delete;
	Bug(Bug&& _Other) noexcept = delete;
	Bug& operator=(const Bug& _Other) = delete;
	Bug& operator=(Bug&& _Other) noexcept = delete;
	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		MineTileMap_ = _TileMap;
	}
protected:

private:
	bool IsDeath_;
	bool Hit_;
	bool Start_;
	float4 InitPos_;
	float4 Move_;
	float4 MoveSet_;
	MonsterDir CurDir_;
	MonsterDir PreDir_;
	int Hp_;

	GameEngineRendererTileMap* MineTileMap_;
	GameEngineRenderer* BugRender_;
	GameEngineCollision* BugCol_;

	void MoveUpdate();
	void CurAniUpdate();
	void DeathCheck();

	void Start() override;
	void Update() override;
};

