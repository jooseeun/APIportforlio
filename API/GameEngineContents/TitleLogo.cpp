#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

TitleLogo::TitleLogo()
{
}

TitleLogo::~TitleLogo()
{
}



void TitleLogo::Start()
{
	SetPosition({ 640,258 });
	SetScale({ 796, 366 });
	CreateRendererToScale("TitleLogo.bmp", float4(796.0f, 366.0f));

}

void TitleLogo::Render()
{
	//DebugRectRender();
}