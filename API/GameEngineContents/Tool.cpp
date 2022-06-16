#include "Tool.h"
#include "ToolUI.h"
#include "ContentsEnums.h"
#include "Money.h"
#include <GameEngine/GameEngineFont.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>


Tool* Tool::ToolSet = nullptr;

Tool::Tool()
	:InventoryModeXPivot_(0),
	InventoryModeYPivot_(0),
	IsClickON_(false),
	IsShop_(false)
{
	FirstPivot_ = 288.0;
	NumPivot_ = 64.0;
	InvenFloorYPivot_ = 78;
	InvenFloorShopYPivot_ = 70;
}

Tool::~Tool()
{


}
void Tool::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ToolSet = this;
}
void Tool::Start()
{
	{ // �⺻������ ������

		SetPosition({ FirstPivot_, 664 });
		ItemData* Hoe_ = new ItemData();
		Hoe_->InvenPivot_ = 0;
		Hoe_->ItemKind_ = PlayerItemKind::WieldItem;
		Hoe_->ItemName_ = PlayerItem::HoeItem;
		Hoe_->Render = CreateRenderer("Tools.bmp");
		Hoe_->Render->SetIndex(26);
		Hoe_->Render->CameraEffectOff();
		Hoe_->InvenFloor_ = InvenFloor::First;
		Hoe_->Click_ = false;
		ItemList_.push_back(Hoe_);

		ItemData* Ax_ = new ItemData();
		Ax_->InvenPivot_ = 1;
		Ax_->ItemKind_ = PlayerItemKind::WieldItem;
		Ax_->ItemName_ = PlayerItem::AxItem;
		Ax_->Render = CreateRenderer("Tools.bmp");
		Ax_->Render->SetIndex(110);
		Ax_->Render->CameraEffectOff();
		Ax_->InvenFloor_ = InvenFloor::First;
		Ax_->Click_ = false;
		ItemList_.push_back(Ax_);

		ItemData* Pick_ = new ItemData();
		Pick_->InvenPivot_ = 2;
		Pick_->ItemKind_ = PlayerItemKind::WieldItem;
		Pick_->ItemName_ = PlayerItem::PickItem;
		Pick_->Render = CreateRenderer("Tools.bmp");
		Pick_->Render->SetIndex(68);
		Pick_->Render->CameraEffectOff();
		Pick_->InvenFloor_ = InvenFloor::First;
		Pick_->Click_ = false;
		ItemList_.push_back(Pick_);

		ItemData* Sickle_ = new ItemData();
		Sickle_->InvenPivot_ = 3;
		Sickle_->ItemKind_ = PlayerItemKind::HitItem;
		Sickle_->ItemName_ = PlayerItem::SickleItem;
		Sickle_->Render = CreateRenderer("Weapons.bmp");
		Sickle_->Render->SetIndex(47);
		Sickle_->Render->CameraEffectOff();
		Sickle_->InvenFloor_ = InvenFloor::First;
		Sickle_->Click_ = false;
		ItemList_.push_back(Sickle_);

		ItemData* WateringCan_ = new ItemData();
		WateringCan_->InvenPivot_ = 4;
		WateringCan_->ItemKind_ = PlayerItemKind::WaterItem;
		WateringCan_->ItemName_ = PlayerItem::WateringCanItem;
		WateringCan_->Render = CreateRenderer("Tools.bmp");
		WateringCan_->Render->SetIndex(149);
		WateringCan_->Render->CameraEffectOff();
		WateringCan_->InvenFloor_ = InvenFloor::First;
		WateringCan_->Click_ = false;
		ItemList_.push_back(WateringCan_);

		ItemData* LongSword_ = new ItemData();
		LongSword_->InvenPivot_ = 5;
		LongSword_->ItemKind_ = PlayerItemKind::HitItem;
		LongSword_->ItemName_ = PlayerItem::LongSwordItem;
		LongSword_->Render = CreateRenderer("Weapons.bmp");
		LongSword_->Render->SetIndex(0);
		LongSword_->Render->CameraEffectOff();
		LongSword_->InvenFloor_ = InvenFloor::First;
		LongSword_->Click_ = false;
		ItemList_.push_back(LongSword_);



	}


	{
		float InvenFirstXPivot_ = -336.0f + 480.0f;
		float InvenFirstYPivot_ = -484.0f + 340.0f;
		float InvenNumPivot_ = 64.0f;
		float InvenFloorPivot_ = 72.0f;
		ShopColl_.push_back(CreateCollision("Inven1Col", { 64,64 }, { InvenFirstXPivot_ ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven2Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 1 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven3Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 2 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven4Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 3 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven5Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 4 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven6Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 5 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven7Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 6 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven8Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 7 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven9Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 8 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven10Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 9 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven11Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 10 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven12Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 11 ,InvenFirstYPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven13Col", { 64,64 }, { InvenFirstXPivot_ ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven14Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 1 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven15Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 2 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven16Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 3 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven17Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 4 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven18Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 5 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven19Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 6 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven20Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 7 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven21Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 8 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven22Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 9 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven23Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 10 ,InvenFirstYPivot_ + InvenFloorPivot_ }));
		ShopColl_.push_back(CreateCollision("Inven24Col", { 64,64 }, { InvenFirstXPivot_ + InvenNumPivot_ * 11 ,InvenFirstYPivot_ + InvenFloorPivot_ }));


		for (int i = 0; i < ShopColl_.size(); i++)
		{
			if (nullptr == ShopColl_[i])
			{
				continue;
			}
			ShopColl_[i]->CameraEffectOff();
		}

		for (int i = 0; i < ShopColl_.size(); i++)
		{
			if (nullptr == ShopColl_[i])
			{
				continue;
			}
			ShopColl_[i]->Off();
		}

	}

}
void Tool::ShopUpdate()
{
	if (IsShop_ == true)
	{
		UpdateShopInvenPos();
		for (int i = 0; i < ShopColl_.size(); i++)
		{
			if (nullptr == ShopColl_[i])
			{
				continue;
			}
			ShopColl_[i]->On();
		}
	}
	else
	{
		UpdateInvenPos();
		for (int i = 0; i < ShopColl_.size(); i++)
		{
			if (nullptr == ShopColl_[i])
			{
				continue;
			}
			ShopColl_[i]->Off();
		}
	}

}
void Tool::Update()
{
	GetCurMousePos();
	CheckInventoryMode();
	ShopUpdate();
	GetToolUINum();

}
void Tool::CheckInventoryMode()
{
	if (IsShop_ == false) // ������������ ��ȯ x�ǵ���
	{
		IsInvenToryMode = ToolUI::ToolUISet->GetIsInventory();
	}

}

void Tool::SetInventoryModePivot()
{

	if (true == IsInvenToryMode)
	{
		InventoryModeXPivot_ = 18.0f;
		InventoryModeYPivot_ = -484.0f;
		NumPivot_ = 61.0f;

		for (int i = 0; i < ItemList_.size(); i++)
		{
			if (ItemList_[i] == nullptr)
			{
				continue;
			}
			if (InvenFloor::Second == ItemList_[i]->InvenFloor_)
			{
				ItemList_[i]->Render->On(); // ����ȿ� ������ Render������
				if (ItemList_[i]->NumRender != nullptr)
				{
					ItemList_[i]->NumRender->On();
				}
			}
		}
	}
	else
	{
		InventoryModeXPivot_ = 0;
		InventoryModeYPivot_ = 0;
		NumPivot_ = 64.0f;

		{
			for (int i = 0; i < ItemList_.size(); i++)
			{
				if (ItemList_[i] == nullptr)
				{
					continue;
				}
				if (InvenFloor::Second == ItemList_[i]->InvenFloor_)
				{
					ItemList_[i]->Render->Off(); // ����ȿ� ������ Render������
					if (ItemList_[i]->NumRender != nullptr)
					{
						ItemList_[i]->NumRender->Off();
					}
				}
			}
		}
	}

}
void Tool::UpdateInvenPos() // ��ġ �׻� ������Ʈ�ϴ� ���
{
	SetInventoryModePivot();


	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}

		if (ItemList_[i] ->IsInven == true)
		{
			if (0 >= ItemList_[i]->ItemCount_)
			{
				ItemList_[i]->Render->Off();
				ItemList_[i]->InvenPivot_ = 100;
				ItemList_[i]->IsInven = false;
			}
			else if (PlayerItemKind::WieldItem == ItemList_[i]->ItemKind_ || PlayerItemKind::WaterItem == ItemList_[i]->ItemKind_)
			{
				ItemList_[i]->Render->SetPivot({ (NumPivot_ * ItemList_[i]->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>(ItemList_[i]->InvenFloor_),
					28 + InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>(ItemList_[i]->InvenFloor_)) });
			}
			else
			{
				ItemList_[i]->Render->SetPivot({ (NumPivot_ * ItemList_[i]->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>(ItemList_[i]->InvenFloor_),
					0 + InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>(ItemList_[i]->InvenFloor_)) });
				ItemCountRenderUpdate();
			}

			if (true == ItemList_[i]->Click_)
			{
				ItemList_[i]->Render->SetPivot({ MouseX_ - FirstPivot_ + 32 , MouseY_ - 664 + 32 });
			}
		}
	}
}
void Tool::UpdateShopInvenPos()
{
	SetInventoryModePivot();


	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}
		if (ItemList_[i]->IsInven == false)
		{
			ItemList_[i]->Render->Off();
			ItemList_[i]->NumRender->Off();
		}

		if (ItemList_[i]->IsInven == true)
		{
			if (0 >= ItemList_[i]->ItemCount_)
			{
				ItemList_[i]->Render->Off();
				ItemList_[i]->InvenPivot_ = 100;
				ItemList_[i]->IsInven = false;

			}
			else if (true == ItemList_[i]->Click_ && ItemList_[i]->IsSell_ == true) // �Ǹű��
			{
				Sound_ = GameEngineSound::SoundPlayControl("purchaseClick.wav");
				Sound_.Volume(0.8f);
				Money::MoneySet->SetMoney(Money::MoneySet->GetMoney() + ItemList_[i]->SellValue_);
				ItemList_[i]->ItemCount_ -= 1;
				ItemList_[i]->Click_ = false;
			}

			else if (PlayerItemKind::WieldItem == ItemList_[i]->ItemKind_ || PlayerItemKind::WaterItem == ItemList_[i]->ItemKind_)
			{
				ItemList_[i]->Render->On();
				ItemList_[i]->Render->SetPivot({ (NumPivot_ * ItemList_[i]->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>(ItemList_[i]->InvenFloor_) + 148 ,
					28 + InventoryModeYPivot_ + (InvenFloorShopYPivot_ * static_cast<float>(ItemList_[i]->InvenFloor_)) - 145 });
			}
			else
			{
				ItemList_[i]->Render->On(); //2��°�پ��̵� ������ �������ϱ����ؼ�
				ItemList_[i]->Render->SetPivot({ (NumPivot_ * ItemList_[i]->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>(ItemList_[i]->InvenFloor_) + 148,
					0 + InventoryModeYPivot_ + (InvenFloorShopYPivot_ * static_cast<float>(ItemList_[i]->InvenFloor_)) - 145 });
				ItemCountRenderUpdate();
			}


		}
	}
}
void Tool::ItemCountRender()
{

	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}

		if (ItemList_[i]->NumRender == nullptr)
		{
			ItemList_[i]->NumRender = CreateRenderer("ItemCountNum.bmp");
			ItemList_[i]->NumRender->SetIndex(10);
		}
	}
}
void Tool::ItemCountRenderUpdate()
{
	ItemCountRender();

	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}

		if (ItemList_[i]->ItemCount_ > 1)
		{

			ItemList_[i]->NumRender->SetIndex(ItemList_[i]->ItemCount_);
		}

		if (IsShop_ == true)//������
		{
			ItemList_[i]->NumRender->SetPivot({ (NumPivot_ * ItemList_[i]->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>(ItemList_[i]->InvenFloor_) + 24 + 148,
				0 + InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>(ItemList_[i]->InvenFloor_)) + 24 - 145 });
		}
		else
		{
			ItemList_[i]->NumRender->SetPivot({ (NumPivot_ * ItemList_[i]->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>(ItemList_[i]->InvenFloor_) + 24,
				0 + InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>(ItemList_[i]->InvenFloor_)) + 24 });

		}
		ItemList_[i]->NumRender->CameraEffectOff();

	}

}
void Tool::CreateItem(PlayerItem _ItemName, PlayerItemKind _ItemKind, std::string _RenderFileName, int _RenderIndex, size_t _SellValue)
{
	ItemData* _CreateItem = new ItemData();
	_CreateItem->ItemKind_ = _ItemKind;
	_CreateItem->ItemName_ = _ItemName;


	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}

		if (_CreateItem->ItemName_ == ItemList_[i]->ItemName_ && ItemList_[i]->ItemCount_ != 0) // �̹� �������� �����Ѵٸ� ���� up
		{
			if (ItemList_[i]->ItemCount_ + 1 < 10)
			{
				ItemList_[i]->ItemCount_ += 1;


				delete _CreateItem;
				_CreateItem = nullptr;
				return;
			}
		}
	}


	for (int i = 0; i < 24; i++) // �κ��丮�� ���� �������̸� �κ��丮 ���ڸ� ã�Ƽ� �־��ִ� �Լ�
	{

		if (PlayerItem::Max == ItemPos_[i])
		{
			_CreateItem->InvenPivot_ = i;
			if (i < 12)
			{
				_CreateItem->InvenFloor_ = InvenFloor::First;
			}
			else if (i > 12 || i == 12)
			{
				_CreateItem->InvenFloor_ = InvenFloor::Second;
			}
			i = 24;
		}

	}
	_CreateItem->Render = CreateRenderer(_RenderFileName);
	_CreateItem->Render->SetIndex(_RenderIndex);
	_CreateItem->Render->CameraEffectOff();
	if (_ItemKind == PlayerItemKind::CropsItem ||
		_ItemKind == PlayerItemKind::ObjectItem ||
		_ItemKind == PlayerItemKind::SeedItem)
	{
		_CreateItem->IsSell_ = true;
		_CreateItem->SellValue_ = _SellValue;
	}


	ToolSet->ItemList_.push_back(_CreateItem);
}

void Tool::SetClickItem(int _Pivot)
{
	// Ŭ���� ������ �Ǻ��� �޾� �� ������ true�� �ٲ� -> �׷��� ���콺 ���� ����


	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}
		if (IsShop_ == false)
		{
			if (true == ItemList_[i]->Click_)
			{
				ItemList_[i]->InvenPivot_ = _Pivot;
				if (_Pivot < 12)
				{
					ItemList_[i]->InvenFloor_ = InvenFloor::First;
				}
				else if (_Pivot > 12 || _Pivot == 12)
				{
					ItemList_[i]->InvenFloor_ = InvenFloor::Second;
				}
				ItemList_[i]->Click_ = false;
			}

			else if (_Pivot == ItemList_[i]->InvenPivot_)
			{
				ItemList_[i]->Click_ = true;
				Sound_ = GameEngineSound::SoundPlayControl("pickUpItem.wav");

			}
		}

		else if (_Pivot == ItemList_[i]->InvenPivot_)
		{
			ItemList_[i]->Click_ = true;
			Sound_ = GameEngineSound::SoundPlayControl("pickUpItem.wav");
		}

	}

}
void Tool::GetToolUINum()
{


	for (int i = 0; i < 24; i++)
	{
		ItemPos_[i] = PlayerItem::Max;
		ItemCount_[i] = 0;
	}

	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}
		ItemPos_[ItemList_[i]->InvenPivot_] = ItemList_[i]->ItemName_;
		ItemCount_[ItemList_[i]->InvenPivot_] = ItemList_[i]->ItemCount_;
	}

}
void Tool::ItemUse(PlayerItem _Item)
{

	for (int i = 0; i < ItemList_.size(); i++)
	{
		if (ItemList_[i] == nullptr)
		{
			continue;
		}
		if (_Item == ItemList_[i]->ItemName_)
		{
			ItemList_[i]->ItemCount_ -= 1;
			if (ItemList_[i]->ItemCount_ == 1)
			{
				ItemList_[i]->NumRender->Off();
			}
			return;
		}
	}

}
