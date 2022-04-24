#include "FarmObjectEnvironment.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>


FarmObjectEnvironment* FarmObjectEnvironment::MainFarmObject = nullptr;

FarmObjectEnvironment::FarmObjectEnvironment() 
{
}

FarmObjectEnvironment::~FarmObjectEnvironment() 
{
}

void FarmObjectEnvironment::Start()
{
	SetPosition({0, 0});
}

void FarmObjectEnvironment::Update()
{
	MakeTree(58, 21, 0);
}

void FarmObjectEnvironment::MakeTree(int _Posx,int _Posy,int _index)
{
	EnvironmentTile* TreeBot_ = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "TreeBot.bmp", _index, static_cast<int>(ORDER::GROUND));
	GameEngineRenderer* TreeTop = CreateRenderer("TreeTop.bmp");
	TreeTop->SetIndex(_index);
	TreeTop->SetPivotType(RenderPivot::BOT);
	TreeTop->SetPivot({ ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) - 32});
}
void FarmObjectEnvironment::MakeGrass(float4 _Pos)
{

}
void FarmObjectEnvironment::MakeStone(float4 _Pos)
{

}
void FarmObjectEnvironment::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainFarmObject = this;
}