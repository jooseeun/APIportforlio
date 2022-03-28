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

	CreateRenderer("TitleBackground.bmp");
}

void TitleBackGround::Render()
{
	//DebugRectRender();
}