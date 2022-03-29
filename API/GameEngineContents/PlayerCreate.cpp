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
	SetScale({ 100, 100 });
}

void PlayerCreate::Render()
{
	DebugRectRender();
}