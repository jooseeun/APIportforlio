#include "Mine2Object.h"
#include "ContentsEnums.h"

Mine2Object* Mine2Object::MainMine2Tile = nullptr;

Mine2Object::Mine2Object()
	:CheckMake_(false)
{
}

Mine2Object::~Mine2Object()
{
}

void Mine2Object::Start()
{
	SetPosition({ 0,0 });

}

void Mine2Object::Update()
{
	RenderObject();
}
void Mine2Object::MakeObject(int _Posx, int _Posy, int _index, MineTileType _TileType)
{
	MineTile* Stone = MineTileMap_->CreateTile<MineTile>(_Posx, _Posy, "MineObject.bmp", _index, static_cast<int>(ORDER::GROUND));
	Stone->TileType_ = _TileType;
	Stone->TileCol_ = CreateCollision("Object", { 64,64 }, { ((float)_Posx + 0.5f) * (5120.0f / 80), ((float)_Posy + 0.5f) * (4160.0f / 65) });

	GameEngineCollision* Exit = CreateCollision("GoMineEntry", { 64,64 }, { (4.0f + 0.5f) * (5120.0f / 80), (4.0f + 0.5f) * (4160.0f / 65) });

}

void Mine2Object::RenderObject()
{
	if (CheckMake_ == false)
	{
			MakeObject(5, 7, 0, MineTileType::Stone);
			MakeObject(12, 8, 3, MineTileType::Stone);
			MakeObject(8, 10, 0, MineTileType::Stone);
			MakeObject(4, 11, 0, MineTileType::Stone);
			MakeObject(7, 13, 3, MineTileType::Stone);
			MakeObject(11, 14, 0, MineTileType::Stone);
			MakeObject(12, 18, 3, MineTileType::Stone);
			MakeObject(13, 24, 3, MineTileType::Stone);
			MakeObject(21, 23, 0, MineTileType::Stone);
			MakeObject(25, 17, 3, MineTileType::Stone);
			MakeObject(25, 20, 0, MineTileType::Stone);
			MakeObject(27, 28, 3, MineTileType::Stone);
			MakeObject(28, 22, 3, MineTileType::Stone);
			MakeObject(29, 25, 0, MineTileType::Stone);
			MakeObject(30, 20, 0, MineTileType::Stone);
			MakeObject(29, 17, 3, MineTileType::Stone);

			MakeObject(13, 8, 1, MineTileType::Diamond);
			MakeObject(6, 10, 1, MineTileType::Diamond);
			MakeObject(6, 13, 1, MineTileType::Diamond);
			MakeObject(23, 22, 1, MineTileType::Diamond);
			MakeObject(31, 20, 1, MineTileType::Diamond);

			MakeObject(12, 5, 4, MineTileType::Emerald);
			MakeObject(9, 7, 4, MineTileType::Emerald);
			MakeObject(24, 25, 4, MineTileType::Emerald);
			MakeObject(2, 8, 4, MineTileType::Emerald);
			MakeObject(27, 22, 4, MineTileType::Emerald);
			MakeObject(28, 29, 4, MineTileType::Emerald);

			MakeObject(11, 15, 5, MineTileType::Ruby);
			MakeObject(26, 17, 5, MineTileType::Ruby);
			MakeObject(28, 25, 5, MineTileType::Ruby);
			MakeObject(4, 11, 5, MineTileType::Ruby);

			MakeObject(11, 16, 2, MineTileType::amethyst);
			MakeObject(21, 24, 2, MineTileType::amethyst);
			GameEngineCollision* Exit = CreateCollision("GoMineEntry", { 64,64 }, { (4.0f + 0.5f) * (5120.0f / 80), (4.0f + 0.5f) * (4160.0f / 65) });
			CheckMake_ = true;

	}
}