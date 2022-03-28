#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>


TitleLogo::TitleLogo()
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
void TitleLogo::Render()
{
	//DebugRectRender();
}