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
	{ 
		std::list<ItemData*>::iterator StartIter = Tool::ToolSet->ItemList_.begin();
		std::list<ItemData*>::iterator EndIter = Tool::ToolSet->ItemList_.end();

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
	{ // 기본아이템 렌더링

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

		ItemData* PhotatoSeed_ = new ItemData();
		PhotatoSeed_->InvenPivot_ = 5;
		PhotatoSeed_->ItemKind_ = PlayerItemKind::SeedItem;
		PhotatoSeed_->ItemName_ = PlayerItem::PhatatoSeedItem;
		PhotatoSeed_->Render = CreateRenderer("Objects.bmp");
		PhotatoSeed_->Render->SetIndex(475);
		PhotatoSeed_->Render->CameraEffectOff();
		PhotatoSeed_->InvenFloor_ = InvenFloor::First;
		PhotatoSeed_->Click_ = false;
		PhotatoSeed_->ItemCount_ = 1;
		ItemList_.push_back(PhotatoSeed_);

		ItemData* KaleSeed_ = new ItemData();
		KaleSeed_->InvenPivot_ = 6;
		KaleSeed_->ItemKind_ = PlayerItemKind::SeedItem;
		KaleSeed_->ItemName_ = PlayerItem::KaleSeedItem;
		KaleSeed_->Render = CreateRenderer("Objects.bmp");
		KaleSeed_->Render->SetIndex(477);
		KaleSeed_->Render->CameraEffectOff();
		KaleSeed_->InvenFloor_ = InvenFloor::First;
		KaleSeed_->Click_ = false;
		KaleSeed_->ItemCount_ = 4;
		ItemList_.push_back(KaleSeed_);

		ItemData* LongSword_ = new ItemData();
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

	{
		{
			float InvenFirstXPivot_ = -336.0f + 480.0f;
			float InvenFirstYPivot_ = -484.0f+340.0f;
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

			
			for (int i = 0 ; i<ShopColl_.size(); i++)
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
	if (IsShop_ == false) // 상점있을때는 전환 x되도록
	{
		IsInvenToryMode = ToolUI::ToolUISet->GetIsInventory();
	}

}

void Tool::SetInventoryModePivot()
{
	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();

	if (true == IsInvenToryMode)
	{
		InventoryModeXPivot_ = 18.0f;
		InventoryModeYPivot_ = -484.0f;
		NumPivot_ = 61.0f;

		for (; StartIter != EndIter; ++StartIter)
		{
			if (*StartIter == nullptr)
			{
				continue;
			}
			if (InvenFloor::Second == (*StartIter)->InvenFloor_)
			{
				(*StartIter)->Render->On(); // 가방안에 있으면 Render꺼버림
				if ((*StartIter)->NumRender != nullptr)
				{
					(*StartIter)->NumRender->On();
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
			for (; StartIter != EndIter; ++StartIter)
			{
				if (*StartIter == nullptr)
				{
					continue;
				}
				if (InvenFloor::Second == (*StartIter)->InvenFloor_)
				{
					(*StartIter)->Render->Off(); // 가방안에 있으면 Render꺼버림
					if ((*StartIter)->NumRender != nullptr)
					{
						(*StartIter)->NumRender->Off();
					}
				}
			}
		}
	}

}
void Tool::UpdateInvenPos() // 위치 항상 업데이트하는 기능
{
	SetInventoryModePivot();
	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}

		if((*StartIter)->IsInven == true)
		{
			if (0 == (*StartIter)->ItemCount_ )
			{
				(*StartIter)->Render->Off();
				(*StartIter)->NumRender->Off();
				(*StartIter)->InvenPivot_=100;
				(*StartIter)->IsInven = false;
			}
			else if (PlayerItemKind::WieldItem == (*StartIter)->ItemKind_ || PlayerItemKind::WaterItem == (*StartIter)->ItemKind_)
			{
				(*StartIter)->Render->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_)+ InventoryModeXPivot_ - 12* (NumPivot_)* static_cast<float>((*StartIter)->InvenFloor_),
					28+ InventoryModeYPivot_+(InvenFloorYPivot_ * static_cast<float>((*StartIter)->InvenFloor_))});
			}
			else
			{
				(*StartIter)->Render->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>((*StartIter)->InvenFloor_),
					0+ InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>((*StartIter)->InvenFloor_)) });
				ItemCountRenderUpdate();
			}

			if (true == (*StartIter)->Click_)
			{
				(*StartIter)->Render->SetPivot({MouseX_ - FirstPivot_+32 , MouseY_ - 664+32});
			}
		}
	}
}
void Tool::UpdateShopInvenPos()
{
	SetInventoryModePivot();
	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}

		if ((*StartIter)->IsInven == true)
		{
			if (0 == (*StartIter)->ItemCount_) 
			{
				(*StartIter)->Render->Off();
				(*StartIter)->NumRender->Off();
				(*StartIter)->InvenPivot_ = 100;
				(*StartIter)->IsInven = false;

			}
			else if (true == (*StartIter)->Click_ && (*StartIter)->IsSell_ == true ) // 판매기능
			{
				Money::MoneySet->SetMoney(Money::MoneySet->GetMoney() + (*StartIter)->SellValue_* (*StartIter)->ItemCount_);
				(*StartIter)->ItemCount_ = 0;
				(*StartIter)->Click_ = false;
			}

			else if (PlayerItemKind::WieldItem == (*StartIter)->ItemKind_ || PlayerItemKind::WaterItem == (*StartIter)->ItemKind_)
			{
				(*StartIter)->Render->On();
				(*StartIter)->Render->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>((*StartIter)->InvenFloor_) + 148 ,
					28 + InventoryModeYPivot_ + (InvenFloorShopYPivot_ * static_cast<float>((*StartIter)->InvenFloor_))  -145});
			}
			else
			{
				(*StartIter)->Render->On(); //2번째줄아이들 상점에 렌더링하기위해서
				(*StartIter)->Render->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>((*StartIter)->InvenFloor_) + 148,
					0 + InventoryModeYPivot_ + (InvenFloorShopYPivot_ * static_cast<float>((*StartIter)->InvenFloor_)) - 145 });
				ItemCountRenderUpdate();
			}
			
			
		}
	}
}
void Tool::ItemCountRender()
{
	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}

		if ((*StartIter)->NumRender == nullptr)
		{
			(*StartIter)->NumRender = CreateRenderer("ItemCountNum.bmp");
			(*StartIter)->NumRender->SetIndex(10);
		}
	}
}
void Tool::ItemCountRenderUpdate()
{
	ItemCountRender();

	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}

		if ((*StartIter)->ItemCount_ > 1)
		{

			(*StartIter)->NumRender->SetIndex((*StartIter)->ItemCount_);
		}

		if (IsShop_ == true)//렌더링
		{
			(*StartIter)->NumRender->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>((*StartIter)->InvenFloor_) + 24 + 148,
				0 + InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>((*StartIter)->InvenFloor_)) + 24 - 145 });
		}
		else
		{
			(*StartIter)->NumRender->SetPivot({ (NumPivot_ * (*StartIter)->InvenPivot_) + InventoryModeXPivot_ - 12 * (NumPivot_) * static_cast<float>((*StartIter)->InvenFloor_) + 24,
				0 + InventoryModeYPivot_ + (InvenFloorYPivot_ * static_cast<float>((*StartIter)->InvenFloor_)) + 24 });

		}
		(*StartIter)->NumRender->CameraEffectOff();
		
	}
	
}
void Tool::CreateItem(PlayerItem _ItemName, PlayerItemKind _ItemKind, std::string _RenderFileName, int _RenderIndex , size_t _SellValue)
{
	ItemData* _CreateItem = new ItemData();
	_CreateItem->ItemKind_ = _ItemKind;
	_CreateItem->ItemName_ = _ItemName;

	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}

		if (_CreateItem->ItemName_ == (*StartIter)->ItemName_ && (*StartIter)->ItemCount_ != 0) // 이미 아이템이 존재한다면 숫자 up
		{
			if ((*StartIter)->ItemCount_ + 1 < 10)
			{
				(*StartIter)->ItemCount_ += 1;


				delete _CreateItem;
				_CreateItem = nullptr;
				return;
			}
		}
	}


	for (int i = 0; i < 24; i++) // 인벤토리에 없는 아이템이면 인벤토리 빈자리 찾아서 넣어주는 함수
	{

		if (PlayerItem::Nothing == ItemPos_[i])
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
		_ItemKind == PlayerItemKind::ObjectItem||
		_ItemKind == PlayerItemKind::SeedItem)
	{
		_CreateItem->IsSell_ = true;
		_CreateItem->SellValue_ = _SellValue;
	}

	
	ToolSet->ItemList_.push_back(_CreateItem);
}

void Tool::SetClickItem(int _Pivot)
{
	// 클릭된 아이템 피봇을 받아 그 피폿을 true로 바꿈 -> 그러면 마우스 옆에 붙음

	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}
		if (IsShop_ == false)
		{
			if (true == (*StartIter)->Click_)
			{
				(*StartIter)->InvenPivot_ = _Pivot;
				if (_Pivot < 12)
				{
					(*StartIter)->InvenFloor_ = InvenFloor::First;
				}
				else if (_Pivot > 12 || _Pivot == 12)
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

		else if (_Pivot == (*StartIter)->InvenPivot_)
		{
			(*StartIter)->Click_ = true;

		}
		
	}

}
void Tool::GetToolUINum()
{
	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();
	
	for (int i = 0; i < 24; i++)
	{
		ItemPos_[i]=PlayerItem::Nothing;
		ItemCount_[i] = 0;
	}

	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}
		ItemPos_[(*StartIter)->InvenPivot_] = (*StartIter)->ItemName_;
		ItemCount_[(*StartIter)->InvenPivot_] = (*StartIter)->ItemCount_;
	}

}
void Tool::ItemUse(PlayerItem _Item)
{
	std::list<ItemData*>::iterator StartIter = ItemList_.begin();
	std::list<ItemData*>::iterator EndIter = ItemList_.end();
	

	for (; StartIter != EndIter; ++StartIter)
	{
		if (*StartIter == nullptr)
		{
			continue;
		}
		if (_Item == (*StartIter)->ItemName_)
		{
			(*StartIter)->ItemCount_ -= 1;
			return; 
		}
	}

}
