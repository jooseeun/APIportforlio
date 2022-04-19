#include "Sickle.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

Sickle* Sickle::SickleSet = nullptr;

Sickle::Sickle() 
	:ItemKind_(PlayerItemKind::HitItem),
	InvenPos_(4),
	ItemName_(PlayerItem::SickleItem)
{
}

Sickle::~Sickle() 
{
}
void Sickle::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SickleSet = this;
}
void Sickle::Start()
{

	GameEngineRenderer* SickleRender = CreateRenderer("Weapons.bmp");
	SickleRender->SetIndex(47);
	SickleRender->CameraEffectOff();

}
void Sickle::Update()
{
	float NumOne = 288.0;
	float Num = 64.0;
	float WeaponHight = 665;
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