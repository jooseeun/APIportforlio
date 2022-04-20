#include "Tool.h"
#include "ToolUI.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>


Tool* Tool::ToolSet = nullptr;

Tool::Tool()
	:InventoryModeXPivot_(0),
	InventoryModeYPivot_(0),
	IsClickON_(false)
{
	FirstPivot_ = 288.0;
	NumPivot_ = 64.0;
	InvenFloorYPivot_ = 78;
}

Tool::~Tool()
{
	{
		std::list<ToolData*>::iterator StartIter = ItemList_.begin();
		std::list<ToolData*>::iterator EndIter = ItemList_.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (nullptr == (*StartIter))
			{
				continue;
			}
			delete (*StartIter);
			(*StartIter) = nullptr;
		}
	}
}
void Tool::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ToolSet = this;
}
void Tool::Start()
{
	{
		SetPosition({ FirstPivot_, 664 });
		ToolData* Hoe_ = new ToolData();
		Hoe_->InvenPivot_ = 0;
		Hoe_->ItemKind_ = PlayerItemKind::WieldItem;
		Hoe_->ItemName_ = PlayerItem::HoeItem;
		Hoe_->Render = CreateRenderer("Tools.bmp");
		Hoe_->Render->SetIndex(26);
		Hoe_->Render->CameraEffectOff();
		Hoe_->InvenFloor_ = InvenFloor::First;
		Hoe_->Click_ = false;
		ItemList_.push_back(Hoe_);

		ToolData* Ax_ = new ToolData();
		Ax_->InvenPivot_ = 1;
		Ax_->ItemKind_ = PlayerItemKind::WieldItem;
		Ax_->ItemName_ = PlayerItem::AxItem;
		Ax_->Render = CreateRenderer("Tools.bmp");
		Ax_->Render->SetIndex(110);
		Ax_->Render->CameraEffectOff();
		Ax_->InvenFloor_ = InvenFloor::First;
		Ax_->Click_ = false;
		ItemList_.push_back(Ax_);

		ToolData* Pick_ = new ToolData();
		Pick_->InvenPivot_ = 2;
		Pick_->ItemKind_ = PlayerItemKind::WieldItem;
		Pick_->ItemName_ = PlayerItem::PickItem;
		Pick_->Render = CreateRenderer("Tools.bmp");
		Pick_->Render->SetIndex(68);
		Pick_->Render->CameraEffectOff();
		Pick_->InvenFloor_ = InvenFloor::First;
		Pick_->Click_ = false;
		ItemList_.push_back(Pick_);

		ToolData* Sickle_ = new ToolData();
		Sickle_->InvenPivot_ = 3;
		Sickle_->ItemKind_ = PlayerItemKind::HitItem;
		Sickle_->ItemName_ = PlayerItem::SickleItem;
		Sickle_->Render = CreateRenderer("Weapons.bmp");
		Sickle_->Render->SetIndex(47);
		Sickle_->Render->CameraEffectOff();
		Sickle_->InvenFloor_ = InvenFloor::First;
		Sickle_->Click_ = false;
		ItemList_.push_back(Sickle_);

		ToolData* WateringCan_ = new ToolData();
		WateringCan_->InvenPivot_ = 4;
		WateringCan_->ItemKind_ = PlayerItemKind::WaterItem;
		WateringCan_->ItemName_ = PlayerItem::WateringCanItem;
		WateringCan_->Render = CreateRenderer("Tools.bmp");
		WateringCan_->Render->SetIndex(149);
		WateringCan_->Render->CameraEffectOff();
		WateringCan_->InvenFloor_ = InvenFloor::First;
		WateringCan_->Click_ = false;
		ItemList_.push_back(WateringCan_);

		ToolData* PhotatoSeed_ = new ToolData();
		PhotatoSeed_->InvenPivot_ = 5;
		PhotatoSeed_->ItemKind_ = PlayerItemKind::SeedItem;
		PhotatoSeed_->ItemName_ = PlayerItem::PhatatoSeedItem;
		PhotatoSeed_->Render = CreateRenderer("Objects.bmp");
		PhotatoSeed_->Render->SetIndex(475);
		PhotatoSeed_->Render->CameraEffectOff();
		PhotatoSeed_->InvenFloor_ = InvenFloor::First;
		PhotatoSeed_->Click_ = false;
		ItemList_.push_back(PhotatoSeed_);

		ToolData* KaleSeed_ = new ToolData();
		KaleSeed_->InvenPivot_ = 6;
		KaleSeed_->ItemKind_ = PlayerItemKind::SeedItem;
		KaleSeed_->ItemName_ = PlayerItem::KaleSeedItem;
		KaleSeed_->Render = CreateRenderer("Objects.bmp");
		KaleSeed_->Render->SetIndex(477);
		KaleSeed_->Render->CameraEffectOff();
		KaleSeed_->InvenFloor_ = InvenFloor::First;
		KaleSeed_->Click_ = false;
		ItemList_.push_back(KaleSeed_);

		ToolData* LongSword_ = new ToolData();
		LongSword_->InvenPivot_ = 7;
		LongSword_->ItemKind_ = PlayerItemKind::HitItem;
		LongSword_->ItemName_ = PlayerItem::LongSwordItem;
		LongSword_->Render = CreateRenderer("Weapons.bmp");
		LongSword_->Render->SetIndex(0);
		LongSword_->Render->CameraEffectOff();
		LongSword_->InvenFloor_ = InvenFloor::First;
		LongSword_->Click_ = false;
		ItemList_.push_back(LongSword_);
	}
}


void Tool::CheckInventoryMode()
{
	IsInvenToryMode = ToolUI::ToolUISet->GetIsInventory();
}

void Tool::SetInventoryModePivot()
{
	std::list<ToolData*>::iterator StartIter = ItemList_.begin();
	std::list<ToolData*>::iterator EndIter = ItemList_.end();

	if (true == IsInvenToryMode)
	{
		InventoryModeXPivot_ = 18.0f;
		InventoryModeYPivot_ = -484.0f;
		NumPivot_ = 61.0f;

		for (; StartIter != EndIter; ++StartIter)
		{
			if (InvenFloor::Second == (*StartIter)->InvenFloor_)
			{
				(*StartIter)->Render->On(); // ����ȿ� ������ Render������
			}
		}
	}
	else
	{
		InventoryModeXPivot_ = 0;
		InventoryModeYPivot_ = 0;
		NumPivot_ = 64.0f;

		{
			for (; StartIter != EndIter; ++StartIter)
			{
				if (InvenFloor::Second == (*StartIter)->InvenFloor_)
				{
					(*StartIter)->Render->Off(); // ����ȿ� ������ Render������
				}
			}
		}
	}

}
void Tool::UpdateInvenPos() // ��ġ �׻� ������Ʈ�ϴ� ���
{
	SetInventoryModePivot();
	std::list<ToolData*>::iterator StartIter = ItemList_.begin();
	std::list<ToolData*>::iterator EndIter = ItemList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (100 == (*StartIter)->InvenPivot_)
		{
			(*StartIter)->Render->Off(); // �κ��� ������ pivot�� 100���� �������ְ� Render������
			//�ϴ� ������ x
		}

		else
		{
			if (PlayerItemKind::WieldItem == (*StartIter)->ItemKind_ || PlayerItemKind::WaterItem == (*StartIter)->ItemKind_)
			{
				(*StartIter)->Render->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_)+ InventoryModeXPivot_ - 12* (NumPivot_)* static_cast<float>((*StartIter)->InvenFloor_),
					28+ InventoryModeYPivot_+(InvenFloorYPivot_ * static_cast<float>((*StartIter)->InvenFloor_))});
			}
			else
			{
				(*StartIter)->Render->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>((*StartIter)->InvenFloor_),
					0+ InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>((*StartIter)->InvenFloor_)) });
			}
			if (true == (*StartIter)->Click_)
			{
				(*StartIter)->Render->SetPivot({MouseX_ - FirstPivot_+32 , MouseY_ - 664+32});
			}
		}
	}
}

void Tool::SetClickItem(int _Pivot)
{
	// Ŭ���� ������ �Ǻ��� �޾� �� ������ true�� �ٲ� -> �׷��� ���콺 ���� ����
	std::list<ToolData*>::iterator StartIter = ItemList_.begin();
	std::list<ToolData*>::iterator EndIter = ItemList_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (true == (*StartIter)->Click_)
		{
			(*StartIter)->InvenPivot_ = _Pivot;
			if (_Pivot < 12)
			{
				(*StartIter)->InvenFloor_ = InvenFloor::First;
			}
			else if (_Pivot > 12||_Pivot==12)
			{
				(*StartIter)->InvenFloor_ = InvenFloor::Second;
			}
			(*StartIter)->Click_ = false;
		}

		else if (_Pivot == (*StartIter)->InvenPivot_)
		{
			(*StartIter)->Click_ = true;

		}
	}

}
void Tool::GetToolUINum()
{
	std::list<ToolData*>::iterator StartIter = ItemList_.begin();
	std::list<ToolData*>::iterator EndIter = ItemList_.end();
	
	for (int i = 0; i < 24; i++)
	{
		_ItemPos[i]=PlayerItem::Nothing;
	}

	for (; StartIter != EndIter; ++StartIter)
	{
		_ItemPos[(*StartIter)->InvenPivot_] = (*StartIter)->ItemName_;

	}
}

void Tool::Update()
{
	GetCurMousePos();
	CheckInventoryMode();
	UpdateInvenPos();
	GetToolUINum();

}