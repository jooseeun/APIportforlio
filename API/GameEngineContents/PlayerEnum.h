#pragma once

enum class EnvironmentTileType
{
	Stone=100,
	Tree,
	Grass,
	Branch,
	Max
};

enum class TileType
{
	HoeDirt=50,
	SeedTile,
	WaterDirt,
	Max,
};
enum class SeedType
{
	Photato,
	Cauliflower,
	Kale,
	Max,
};
enum class PlayerState 
{
	Idle,
	Wield,
	Hit,
	Water,
	Hold,
	Walk,
	Seed,
	Harvest,
	Max,
};

enum class PlayerDir
{
	Front,
	Back,
	Left,
	Right,
	Max
};

enum class PlayerItemKind
{
	HitItem,
	WieldItem,
	WaterItem,
	SeedItem,
	CropsItem,
	ObjectItem,
	NoItem
};

enum class PlayerItem
{
	Nothing,
	WieldItem=10,
	AxItem,
	HoeItem,
	PickItem,
	WaterItem=20,
	WateringCanItem,
	HitItem=30,
	SickleItem,
	LongSwordItem,
	SeedItem=40,
	PhatatoSeedItem,
	KaleSeedItem,
	CauliFlowerSeedItem,
	ParsnipSeedItem,
	BeanSeedItem,
	BlueberrieSeedItem,
	MelonSeedItem,
	PepperSeedItem,
	CropsItem=50,
	PhotatoItem,
	KaleItem,
	CauliFlowerItem,
	ObjectItem=60,
	StoneItem,
	BranchItem,
	TreeItem,
	GrassItem,
	Max

	
};

enum class PlayerHairColor
{
	Black,
	Red,
	Grey,
	Blue,
	Max
};
enum class PlayerHairStyle
{
	First=5,
	Second=2
};
enum class PlayerShirts
{
	First=0,
	Second,
	Third,
	Fourth,
	Fifth,
	Sixth,
	Secenth,
	Eighth,
	Ninth,
	Tenth

};

enum class InvenFloor
{
	First,
	Second,
	Max
};