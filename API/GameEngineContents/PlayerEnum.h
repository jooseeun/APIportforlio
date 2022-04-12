#pragma once

enum class PlayerState
{
	Idle,
	Wield,
	Hit,
	Eat,
	Hold,
	Walk,
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

enum class PlayerHave
{
	HitItem,
	WieldItem,
	EatItem,
	ElseItem,
	NoItem
};

enum class PlayerItem
{
	Nothing,
	AxItem,
	HoeItem,
	PickItem,
	SickleItem
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