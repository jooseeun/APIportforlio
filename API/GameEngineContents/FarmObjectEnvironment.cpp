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
	CheckMake_ = false;
}

void FarmObjectEnvironment::Update()
{
	if (CheckMake_ == false)
	{
		MakeTree(55, 18, 0);
		MakeTree(58, 21, 0);
		MakeTree(67, 24, 1);
		MakeTree(64, 28, 0);
		MakeTree(51, 25, 1);
		MakeTree(48, 22, 0);
		MakeTree(73, 23, 1);
		MakeTree(59, 29, 1);
		CheckMake_ = true;
	}

}

void FarmObjectEnvironment::MakeTree(int _Posx,int _Posy,int _index)
{
	EnvironmentTile* TreeBot_ = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "TreeBot.bmp", _index, static_cast<int>(ORDER::GROUND));
	
	GameEngineRenderer* TreeTop = CreateRenderer("TreeTop.bmp");
	TreeTop->SetIndex(_index);
	TreeTop->SetPivotType(RenderPivot::BOT);
	TreeTop->SetPivot({ ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) - 20});
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