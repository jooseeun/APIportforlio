#pragma once

enum PlayerState
{
	Idle,
	Wield,
	Hit,
	Eat,
	Hold,
	Move
};

enum PlayerDir
{
	Front,
	Back,
	Left,
	Right
};

enum PlayerHave
{
	HitItem,
	WieldItem,
	EatItem,
	ElseItem,
	NoItem
};

enum PlayerItem
{
	Nothing,
	AxItem,
	HoeItem,
	PickItem,
	SickleItem
};