#include "TitleLogo.h"
#include "PlayerCreate.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>

TitleLogo::TitleLogo()
	:hide_(false),
	show_(false),
	Count_(0),
	Time_(0.1f )
{
}

TitleLogo::~TitleLogo()
{
}



void TitleLogo::Start()
{
	SetPosition({ 640,258 });
	CreateRenderer("TitleLogo.bmp");

	
	GameEngineRenderer* BigLeaf = CreateRenderer(2, RenderPivot::CENTER, { 283,46 }); // 890 280
	BigLeaf->CreateAnimation("BigLeaf.bmp", "BigLeaf", 0, 2, 0.15f, true);
	BigLeaf->ChangeAnimation("BigLeaf");
	GameEngineRenderer* SmallLeaf = CreateRenderer(2, RenderPivot::CENTER, { -345,-138 }); // 890 280
	SmallLeaf->CreateAnimation("SmallLeaf.bmp", "SmallLeaf", 0, 2, 0.15f, true);
	SmallLeaf->ChangeAnimation("SmallLeaf");

	StartButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 }, 2, RenderPivot::CENTER,
		{ -369,359 });//246
	StartButton->SetIndex(0);
	LoadButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 },2, RenderPivot::CENTER,
		{ -123,359 });
	LoadButton->SetIndex(1);
	MultyButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 },2, RenderPivot::CENTER,
		{ 123,359 });
	MultyButton->SetIndex(2);

	ExitButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 },2, RenderPivot::CENTER,
		{ 369,359 });
	ExitButton->SetIndex(3);
	StartCol_ = CreateCollision("StartCol", { 222, 174 }, { -369,359 });
	ExitCol_ = CreateCollision("ExitCol", { 222, 174 }, { 369,359 });
	MultyCol_= CreateCollision("MultyCol", { 222, 174 }, { 123,359 });
	LoadCol_ = CreateCollision("LoadCol", { 222, 174 }, { -123,359 });

	StartButton->Off();
	LoadButton->Off();
	MultyButton->Off();
	ExitButton->Off();
}
void TitleLogo::Update()
{
	if (Time_ >= 0.0f)
	{
		Time_ -= 0.3f * GameEngineTime::GetDeltaTime();
	}
	else
	{
		if (Count_ == 0)
		{
			StartButton->On();
			Time_ = 0.1f;
			Count_++;
		}
		else if (Count_ == 1)
		{
			LoadButton->On();
			Time_ = 0.1f;
			Count_++;
		}
		else if (Count_ == 2)
		{
			MultyButton->On();
			Time_ = 0.1f;
			Count_++;
		}
		else if (Count_ == 3)
		{
			ExitButton->On();
			Time_ = 0.1f;
			Count_++;
		}
	}
	IsButtonColUpdate();

}
void TitleLogo::IsButtonColUpdate()
{
	if (true == StartCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
	{
		StartButton->SetIndex(4);
	}
	else
	{
		StartButton->SetIndex(0);
	}


	if (true == ExitCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
	{
		ExitButton->SetIndex(7);
	}
	else
	{
		ExitButton->SetIndex(3);
	}
}
