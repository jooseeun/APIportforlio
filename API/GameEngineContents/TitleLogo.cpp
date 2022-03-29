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

	//나뭇잎 애니메이션은 마우스 클릭했을때 흔들린다. 수정하기
	GameEngineRenderer* BigLeaf = CreateRenderer(RenderPivot::CENTER,{283,46}); // 890 280
	BigLeaf->CreateAnimation("BigLeaf.bmp", "BigLeaf", 0, 2, 0.15f, true);
	BigLeaf->ChangeAnimation("BigLeaf");
	GameEngineRenderer* SmallLeaf = CreateRenderer(RenderPivot::CENTER, { -345,-138 }); // 890 280
	SmallLeaf->CreateAnimation("SmallLeaf.bmp", "SmallLeaf", 0, 2, 0.15f, true);
	SmallLeaf->ChangeAnimation("SmallLeaf");

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