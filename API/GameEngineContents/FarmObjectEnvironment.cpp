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
		MakeTree(67, 24, 0);
		MakeTree(64, 28, 0);
		MakeTree(51, 25, 0);
		MakeTree(48, 22, 0);
		MakeTree(70, 19, 0);
		MakeTree(73, 23, 0);
		MakeTree(59, 29, 0);

		MakeStone(50, 23, 3);
		MakeStone(52, 26, 3);
		MakeStone(54, 24, 3);
		MakeStone(58, 18, 4);
		MakeStone(57, 17, 4);
		MakeStone(65, 19, 4);
		MakeStone(66, 19, 3);
		MakeStone(40, 30, 3);
		MakeStone(57, 25, 4);
		MakeStone(56, 25, 3);
		MakeStone(74, 27, 4);
		MakeStone(75, 27, 4);
		MakeStone(74, 19, 3);
		MakeStone(60, 19, 3);
		MakeStone(72, 22, 4);

		MakeGrass(50, 24, 0);
		MakeGrass(52, 20, 0);
		MakeGrass(54, 21, 0);
		MakeGrass(54, 25, 0);
		MakeGrass(63, 23, 0);
		MakeGrass(64, 23, 0);
		MakeGrass(62, 24, 0);
		MakeGrass(63, 24, 0);
		MakeGrass(73, 21, 0);
		MakeGrass(73, 21, 0);
		MakeGrass(59, 34, 0);
		MakeGrass(59, 25, 0);
		MakeGrass(60, 21, 0);
		MakeGrass(59, 23, 0);
		MakeGrass(71, 21, 0);

		MakeBranch(60, 26, 6);
		MakeBranch(63, 22, 5);
		MakeBranch(57, 29, 6);
		MakeBranch(57, 25, 5);
		MakeBranch(51, 28, 5);
		MakeBranch(52, 22, 6);
		MakeBranch(53, 23, 6);
		MakeBranch(75, 22, 6);
		MakeBranch(60, 20, 5);
		MakeBranch(61, 21, 6);
		MakeBranch(70, 21, 6);
		CheckMake_ = true;
	}

	CheckTreeAnimation();
	CheckTreeAlpha();
}

void FarmObjectEnvironment::MakeTree(int _Posx,int _Posy,int _index)
{
	EnvironmentTile* TreeBot_ = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "CutTree.bmp", _index, static_cast<int>(ORDER::GROUND));
	TreeBot_->EnvironmentType_ = EnvironmentTileType::Tree;
	TreeBot_->DeathCount_ = 6;
	TreeBot_->TileCol_ = CreateCollision("Object", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });


	TreeBot_->TreeTop_ = CreateRenderer("TreeTop.bmp");
	TreeBot_->TreeTop_->SetOrder(static_cast<int>(ORDER::PLAYER));
	TreeBot_->TreeTop_->SetIndex(_index);
	TreeBot_->TreeTop_->SetPivotType(RenderPivot::BOT);
	TreeBot_->TreeTop_->SetPivot({ ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) - 12});
	TreeBot_->TreeTopX_ = ((float)_Posx + 0.5f) * (5120.0f / 80);
	TreeBot_->TreeTopY_ = ((float)_Posy + 0.5f) * (4160.0f / 65) - 12;

	TreeBot_->TreeAni_ = CreateRenderer("TreeAni.bmp");
	TreeBot_->TreeAni_->SetPivotType(RenderPivot::BOT);
	TreeBot_->TreeAni_->SetPivot({ ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) - 12 });
	TreeBot_->TreeAni_->CreateAnimation("TreeAni.bmp", "ShakeTree", _index , _index  + 5, 0.06f, true);
	TreeBot_->TreeAni_->CreateAnimation("TreeAni.bmp", "ShakeTree2", _index , _index + 5, 0.06f, true);
	TreeBot_->TreeAni_->SetOrder(static_cast<int>(ORDER::TREETOP));
	TreeBot_->TreeAni_->Off();

	TreeBot_->TreeTopCol_ = CreateCollision("TreeCol", { 192,300 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) - 180 });
	Tree.push_back(TreeBot_);
}
void FarmObjectEnvironment::TreeAni(GameEngineRenderer* _TreeTop)
{
	_TreeTop->SetPivot({ _TreeTop->GetImagePivot().x - 10, _TreeTop->GetImagePivot().y });
}
void FarmObjectEnvironment::CheckTreeAnimation()
{
	for (int i = 0;i< Tree.size(); i++)
	{
		if (nullptr == Tree[i] )
		{
			continue;
		}
		
		if (true == Tree[i]->IsShake_)
		{
			Tree[i]->TreeTop_->Off();
			Tree[i]->TreeAni_->On();
			Tree[i]->TreeAni_->ChangeAnimation("ShakeTree");
			if (true == Tree[i]->TreeAni_->IsEndAnimation())
			{
				Tree[i]->TreeAni_->ChangeAnimation("ShakeTree2");
				Tree[i]->TreeAni_->Off();
				Tree[i]->TreeTop_->On();
				Tree[i]->IsShake_ = false;
			}
		}
	}
}
void FarmObjectEnvironment::CheckTreeAlpha()
{
	for (int i = 0; i < Tree.size(); i++)
	{
		if (nullptr == Tree[i])
		{
			continue;
		}
		else if (Tree[i]->IsDestroy_ == true)
		{
			Tree.erase(Tree.begin() + i);
			continue;
		}

		if (true == Tree[i]->TreeTopCol_->CollisionCheck("Player", CollisionType::Rect, CollisionType::Rect))
		{
			Tree[i]->TreeTop_->SetAlpha(80);
			return;
		}

		else
		{
			Tree[i]->TreeTop_->SetAlpha(255);
		}
	}
}

void FarmObjectEnvironment::MakeGrass(int _Posx, int _Posy, int _index) // 698~ ?????? 31
{
	EnvironmentTile* Grass = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "FarmObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Grass->EnvironmentType_ = EnvironmentTileType::Grass;
	Grass->TileCol_ = CreateCollision("Object", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void FarmObjectEnvironment::MakeStone(int _Posx, int _Posy, int _index)// 693~
{
	EnvironmentTile* Stone = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "FarmObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Stone->EnvironmentType_ = EnvironmentTileType::Stone;
	Stone->TileCol_ = CreateCollision("Object", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void FarmObjectEnvironment::MakeBranch(int _Posx, int _Posy, int _index)// 693~
{
	EnvironmentTile* Branch = FarmTileMap_->CreateTile<EnvironmentTile>(_Posx, _Posy, "FarmObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Branch->EnvironmentType_ = EnvironmentTileType::Branch;
	Branch->TileCol_ = CreateCollision("Object", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void FarmObjectEnvironment::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainFarmObject = this;
}