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
#include <GameEngineBase/GameEngineSound.h>



TitleLogo::TitleLogo()
	:hide_(false),
	show_(false),
	Count_(0),
	Time_(0.1f ),
	SoundOn_(false)
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
	StartCol_ = CreateCollision("PlayerCreate", { 222, 174 }, { -369,359 });
	ExitCol_ = CreateCollision("ExitCol", { 222, 174 }, { 369,359 });
	MultyCol_= CreateCollision("MultyCol", { 222, 174 }, { 123,359 });
	LoadCol_ = CreateCollision("LoadCol", { 222, 174 }, { -123,359 });

	StartButton->Off();
	LoadButton->Off();
	MultyButton->Off();
	ExitButton->Off();
	ButtonOn[0] = false;
	ButtonOn[1] = false;
	ButtonOn[2] = false;
	ButtonOn[3] = false;
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
	if ("TitleLevel" == GetLevel()->GetNameCopy() && true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		if (true == StartCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
		{
			hide_ = true;
		}

	}

	if (hide_ == true)
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 900.0f);
		float4 GetPos_ = GetPosition();
		if (1800 <= GetPos_.x)
		{
			PlayerCreate* Ptr = GetLevel()->CreateActor<PlayerCreate>();
			Ptr->SetPosition(GameEngineWindow::GetScale().Half());
			hide_ = false;
		}
	}
}

void TitleLogo::IsButtonColUpdate()
{
	if (ButtonOn[0] == true|| ButtonOn[1] == true
		|| ButtonOn[2] == true|| ButtonOn[3] == true)
	{
		if (SoundOn_ == true)
		{
			GameEngineSound::SoundPlayOneShot("Cowboy_Footstep.wav");
			SoundOn_=false;
			return;
		}
	}

	if (true == StartCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
	{
		if (ButtonOn[0] == false)
		{
			ButtonOn[0] = true;
			SoundOn_ = true;
		}
		StartButton->SetIndex(4);
	}
	else
	{
		StartButton->SetIndex(0);
		ButtonOn[0] = false;
	}

	if (true ==LoadCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
	{
		if (ButtonOn[1] == false)
		{
			ButtonOn[1] = true;
			SoundOn_ = true;
		}
		LoadButton->SetIndex(5);
	}
	else
	{
		ButtonOn[1] = false;
		LoadButton->SetIndex(1);
	}

	if (true == MultyCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
	{
		if (ButtonOn[2] == false)
		{
			ButtonOn[2] = true;
			SoundOn_ = true;
		}
		MultyButton->SetIndex(6);
	}
	else
	{
		MultyButton->SetIndex(2);
		ButtonOn[2] = false;
	}

	if (true == ExitCol_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
	{
		if (ButtonOn[3] == false)
		{
			ButtonOn[3] = true;
			SoundOn_ = true;
		}
		ExitButton->SetIndex(7);
	}
	else
	{
		ExitButton->SetIndex(3);
		ButtonOn[3] = false;
	}

}
