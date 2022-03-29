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

TitleLogo::TitleLogo()
	:hide_(false),
	show_(false)
{
}

TitleLogo::~TitleLogo()
{
}



void TitleLogo::Start()
{
	SetPosition({ 640,258 });
	CreateRenderer("TitleLogo.bmp");


	GameEngineRenderer* StartButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 }, RenderPivot::CENTER,
		{ -369,359 });//246
	StartButton->SetIndex(0);

	GameEngineRenderer* LoadButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 }, RenderPivot::CENTER,
		{ -123,359 });
	LoadButton->SetIndex(1);
	GameEngineRenderer* MultyButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 }, RenderPivot::CENTER,
		{ 123,359 });
	MultyButton->SetIndex(2);
	GameEngineRenderer* ExitButton = CreateRendererToScale("TitleButton.bmp", { 222, 174 }, RenderPivot::CENTER,
		{ 369,359 });
	ExitButton->SetIndex(3);


}
void TitleLogo::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("PlayerCreate"))
	{
		hide_ = true;

	}

	if (hide_ == true)
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 900.0f);
		float4 GetPos_ = GetPosition();
		if (1800 <= GetPos_.x)
		{
			PlayerCreate* Ptr = GetLevel()->CreateActor<PlayerCreate>();
			Ptr->SetPosition(GameEngineWindow::GetScale().Half());
			hide_==false;
		}
	}
	
	
}