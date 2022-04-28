#include "MineObject.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

MineObject::MineObject() 
	:CheckMake_(false)
{
}

MineObject::~MineObject() 
{
}

void MineObject::Start()
{
	SetPosition({ 0,0 });

}
void MineObject::Update()
{
	if (CheckMake_ == false)
	{
		if (GetLevel()->GetNameCopy() == "Mine1Level")
		{
			MakeObject(5, 6, 3, MineTileType::Stone);
			MakeObject(12, 5, 7, MineTileType::Stone);
			MakeObject(16, 6, 7, MineTileType::Stone);
			MakeObject(8, 8, 3, MineTileType::Stone);
			MakeObject(7, 11, 3, MineTileType::Stone);
			MakeObject(6, 12, 7, MineTileType::Stone);
			MakeObject(13, 12, 7, MineTileType::Stone);
			MakeObject(7, 15, 3, MineTileType::Stone);
			CheckMake_ = true;
		}
		else if (GetLevel()->GetNameCopy() == "Mine2Level")
		{
			CheckMake_ = true;
		}
	}
}
void MineObject::MakeObject(int _Posx, int _Posy, int _index, MineTileType _TileType)
{
	MineTile* Stone = MineTileMap_->CreateTile<MineTile>(_Posx, _Posy, "MineObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Stone->TileType_ = _TileType;
	Stone->TileCol_ = CreateCollision("MineStone", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}
void MineObject::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


}