#include "Hoe.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
Hoe::Hoe() 
	:ItemKind_(PlayerItemKind::WieldItem),
	InvenPos_(1),
	ItemName_(PlayerItem::HoeItem)
{
}

Hoe::~Hoe() 
{
}


void Hoe::Start()
{

	GameEngineRenderer* HoeRender = CreateRenderer("Tools.bmp");
	HoeRender->SetIndex(26);
	HoeRender->CameraEffectOff();

}
void Hoe::Update()
{
	float NumOne = 288.0;
	float Num = 64.0;
	{
		if (1 == InvenPos_)
		{
			SetPosition({ NumOne, 692 });
		}
		else if (2 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 1, 692 });
		}
		else if (3 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 2,692 });
		}
		else if (4 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 3, 692 });
		}
		else if (5 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 4, 692 });
		}
		else if (6 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 5, 692 });
		}
		else if (7 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 6,692 });
		}
		else if (8 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 7, 692 });
		}
		else if (9 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 8, 692 });
		}
		else if (10 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 9, 692 });
		}
		else if (11 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 10, 692 });
		}
		else if (12 == InvenPos_)
		{
			SetPosition({ NumOne + Num * 11, 692 });
		}
	}
}