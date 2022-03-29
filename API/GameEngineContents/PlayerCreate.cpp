#include "PlayerCreate.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayerCreate::PlayerCreate() 
{
}

PlayerCreate::~PlayerCreate() 
{
}

void PlayerCreate::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("PlayerCreateBackGround.bmp");
}

void PlayerCreate::Render()
{
	DebugRectRender();
}