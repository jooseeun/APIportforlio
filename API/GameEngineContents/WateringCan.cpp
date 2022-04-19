#include "WateringCan.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

WateringCan* WateringCan::WateringCanSet = nullptr;

WateringCan::WateringCan()
	:ItemKind_(PlayerItemKind::WaterItem),
	InvenPos_(5),
	ItemName_(PlayerItem::WateringCanItem)
{
}

WateringCan::~WateringCan()
{
}

void WateringCan::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	WateringCanSet = this;
}

void WateringCan::Start()
{

	GameEngineRenderer* WateringCanRender = CreateRenderer("Tools.bmp");
	WateringCanRender->SetIndex(149);
	WateringCanRender->CameraEffectOff();

}
void WateringCan::Update()
{
	float NumOne = 288.0;
	float Num = 64.0;
	float WeaponHight = 680;
	{
		if (1 == InvenPos_)
		{
			SetPosition({ NumOne,WeaponHight });
		}
		else if (2 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 1,WeaponHight });
		}
		else if (3 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 2,WeaponHight });
		}
		else if (4 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 3, WeaponHight });
		}
		else if (5 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 4, WeaponHight });
		}
		else if (6 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 5, WeaponHight });
		}
		else if (7 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 6,WeaponHight });
		}
		else if (8 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 7,WeaponHight });
		}
		else if (9 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 8,WeaponHight });
		}
		else if (10 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 9, WeaponHight });
		}
		else if (11 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 10,WeaponHight });
		}
		else if (12 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 11, WeaponHight });
		}
	}
}