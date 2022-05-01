#include "Mine1Object.h"
#include "ContentsEnums.h"


Mine1Object* Mine1Object::MainMine1Tile=nullptr;

Mine1Object::Mine1Object() 
	:CheckMake_(false)
{
}

Mine1Object::~Mine1Object() 
{
}

void Mine1Object::Start()
{
	SetPosition({ 0,0 });

}

void Mine1Object::Update()
{
	RenderObject();
}
void Mine1Object::MakeObject(int _Posx, int _Posy, int _index, MineTileType _TileType)
{
	MineTile* Stone = MineTileMap_->CreateTile<MineTile>(_Posx, _Posy, "MineObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Stone->TileType_ = _TileType;
	Stone->TileCol_ = CreateCollision("Object", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

}

void Mine1Object::RenderObject()
{
	if (CheckMake_ == false)
	{
		MakeObject(5, 6, 3, MineTileType::Stone);
		MakeObject(12, 5, 7, MineTileType::Stone);
		MakeObject(16, 6, 3, MineTileType::Stone);
		MakeObject(8, 8, 7, MineTileType::Stone);
		MakeObject(7, 11, 3, MineTileType::Stone);
		MakeObject(14, 16, 7, MineTileType::Stone);
		MakeObject(15, 16, 3, MineTileType::Stone);

		MakeObject(13, 12, 5, MineTileType::Ruby);
		MakeObject(7, 15, 5, MineTileType::Ruby);

		MakeObject(6, 12, 4, MineTileType::Emerald);
		MakeObject(13, 11, 4, MineTileType::Emerald);

		MakeObject(4, 9, 0, MineTileType::Coal);
		MakeObject(14, 11, 0, MineTileType::Coal);
		MakeObject(13, 13, 0, MineTileType::Coal);

		MakeObject(11, 10, 6, MineTileType::Copper);
		MakeObject(15, 8, 6, MineTileType::Copper);
		MakeObject(4, 14, 6, MineTileType::Copper);
		MakeObject(10, 14, 6, MineTileType::Copper);

		MakeObject(6, 6, 2, MineTileType::amethyst);
		MakeObject(11, 7, 2, MineTileType::amethyst);
		MakeObject(7, 12, 2, MineTileType::amethyst);

		MakeObject(14, 8, 1, MineTileType::Diamond);
		MakeObject(15, 13, 1, MineTileType::Diamond);
		MakeObject(4, 8, 1, MineTileType::Diamond);
		GameEngineCollision* Exit = CreateCollision("GoMineEntry", { 75,131 }, { 672,180 });

		CheckMake_ = true;
	}
}