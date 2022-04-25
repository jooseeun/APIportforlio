#include "FarmObjectEnvironment.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

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

		MakeStone(65, 19, 4);
		MakeStone(66, 19, 3);
		MakeGrass(63, 18, 0);

		MakeBranch(63, 22, 5);
		MakeBranch(70, 18, 6);

		CheckMake_ = true;
	}

}

void FarmObjectEnvironment::MakeTree(int _Posx,int _Posy,int _index)
{
	EnvironmentTile* TreeBot_ = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "TreeBot.bmp", _index, static_cast<int>(ORDER::GROUND));
	TreeBot_->EnvironmentType_ = EnvironmentTileType::Tree;
	TreeBot_->DeathCount_ = 3;
	TreeBot_->TileCol_ = CreateCollision("Tree", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });


	GameEngineRenderer* TreeTop = CreateRenderer("TreeTop.bmp");
	TreeTop->SetIndex(_index);
	TreeTop->SetOrder(static_cast<int>(ORDER::TREETOP));
	TreeTop->SetPivotType(RenderPivot::BOT);
	TreeTop->SetPivot({ ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) - 20});
}

void FarmObjectEnvironment::MakeGrass(int _Posx, int _Posy, int _index) // 698~ ºóÅ¸ÀÏ 31
{
	EnvironmentTile* Grass = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "FarmObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Grass->EnvironmentType_ = EnvironmentTileType::Grass;
	Grass->TileCol_ = CreateCollision("Grass", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void FarmObjectEnvironment::MakeStone(int _Posx, int _Posy, int _index)// 693~
{
	EnvironmentTile* Stone = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "FarmObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Stone->EnvironmentType_ = EnvironmentTileType::Stone;
	Stone->TileCol_ = CreateCollision("Stone", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void FarmObjectEnvironment::MakeBranch(int _Posx, int _Posy, int _index)// 693~
{
	EnvironmentTile* Branch = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "FarmObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Branch->EnvironmentType_ = EnvironmentTileType::Branch;
	Branch->TileCol_ = CreateCollision("Branch", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void FarmObjectEnvironment::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainFarmObject = this;
}