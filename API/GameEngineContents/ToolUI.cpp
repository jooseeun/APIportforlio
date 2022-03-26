#include "ToolUI.h"

ToolUI::ToolUI() 
{
}

ToolUI::~ToolUI() 
{
}

void ToolUI::Start()
{
	SetPosition({ 640,664 });
	SetScale({ 800,96 });
}





void ToolUI::Render()
{
	DebugRectRender();
}