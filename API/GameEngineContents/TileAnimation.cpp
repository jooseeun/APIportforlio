#include "TileAnimation.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
TileAnimation::TileAnimation() 
	:IsUpdate_(false)
{
}

TileAnimation::~TileAnimation() 
{
}

void TileAnimation::Start()
{
	TileAni_ = CreateRenderer();
}

void TileAnimation::Update()
{
	if (IsUpdate_ == true && TileAni_->IsEndAnimation() == true)
	{
		Death();
	}

	if (IsUpdate_ == false)
	{
		TileAni_->CreateAnimation(TileString_ + ".bmp", TileString_, 0, 9, 0.12f, false);
		TileAni_->ChangeAnimation(TileString_);
		IsUpdate_ = true;
	}

}