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