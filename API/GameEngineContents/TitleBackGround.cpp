#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleBackGround::TitleBackGround()
{
	// Level_ = nullptr;
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	SetPosition({ 640, 600});
	SetScale({1280,1440});

	CreateRendererToScale("TitleBackground.bmp", float4(1280.0f, 1440.0f));
}

void TitleBackGround::Render()
{
	//DebugRectRender();
}