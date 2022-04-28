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
		MakeTree(73, 23, 0);
		MakeTree(59, 29, 0);

		MakeStone(65, 19, 4);
		MakeStone(66, 19, 3);
		MakeGrass(63, 18, 0);

		MakeBranch(63, 22, 5);
		MakeBranch(70, 18, 6);

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
	TreeBot_->TileCol_ = CreateCollision("Tree", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });


	TreeBot_->TreeTop_ = CreateRenderer("TreeTop.bmp");
	TreeBot_->TreeTop_->SetIndex(_index);
	TreeBot_->TreeTop_->SetOrder(static_cast<int>(ORDER::TREETOP));
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