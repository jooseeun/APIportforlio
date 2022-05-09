#include "TitleBackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

TitleBackGround* TitleBackGround::TitleBackGroundSet=nullptr;

TitleBackGround::TitleBackGround()
	:Time_(5.0f),
	Check_(false),
	YPivot_(-248.0f),
	StartLogo_(false),
	IsBGM_(false),
	TreeRight_(nullptr),
	TreeLeft_(nullptr),
	TitleCloud_(nullptr)
{
	// Level_ = nullptr;
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	SetPosition({ 640,360 });
	BackGround_ = CreateRenderer("TitleStart.bmp");

	TitleFish_ = CreateRenderer("TitleStartFish.bmp");
	TitleFish_->CreateAnimation("TitleStartFish.bmp", "TitleFish", 0, 1, 0.1f, true);
	TitleFish_->ChangeAnimation("TitleFish");

	Title1_ = CreateRenderer("TitleStart1.bmp");
	Title1_->SetPivot({ -100,0 });
	Title1_->CreateAnimation("TitleStart1.bmp", "Title1", 0, 3, 0.1f, true);
	Title1_->Off();

	Title2_ = CreateRenderer("TitleStart2.bmp");
	Title2_->SetPivot({ 100,0 });
	Title2_->CreateAnimation("TitleStart2.bmp", "Title2", 0, 1, 0.1f, true);
	Title2_->Off();
}

void TitleBackGround::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Skip"))
	{
		TitleFish_->Off();
		Title1_->Off();
		Title2_->Off();		
		BackGround_ = CreateRenderer("TitleBackground.bmp");
		BackGround_->SetPivot({ 0,248 });
		IsBGM_ = true;
		Check_ = false;
		StartLogo_ = true;
		Time_ = -1;
		YPivot_ = 248;
	}
	if (Time_ > 3.0f)
	{
		Time_ -= 1.0f * GameEngineTime::GetDeltaTime();
		return;
	}
	if (Check_ == false&& Time_>0.0f)
	{
		TitleFish_->Off();
		Title1_->On();
		Title1_->ChangeAnimation("Title1");
		Title2_->On();
		Title2_->ChangeAnimation("Title2");
		sound = GameEngineSound::SoundPlayControl("mouseClick.wav");
		sound.PlaySpeed(0.8f);
		sound.Volume(1.0f);
		Check_ = true;
		return;
	}

	if (Time_ >= 0.0f )
	{
		Time_ -= 1.0f * GameEngineTime::GetDeltaTime();
		return;
	}

	if (Time_ < 0.0f && Check_ == true)
	{
		Title1_->Off();
		Title2_->Off();
		BackGround_ = CreateRenderer("TitleBackground.bmp");
		BackGround_->SetPivot({ 0,YPivot_ });
		IsBGM_ = true;
		Check_ = false;
	}

	if (Time_ < 0.0f && Check_ == false)
	{


		if (YPivot_ <= 240)
		{
			YPivot_ += 1 * GameEngineTime::GetDeltaTime() * 100.f;
			BackGround_->SetPivot({ 0,YPivot_ });
		}
		else
		{
			StartLogo_ = true;
		}
	}

}