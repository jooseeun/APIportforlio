#include "TopUI.h"

TopUI::TopUI() 
{
}

TopUI::~TopUI() 
{
}


void TopUI::Start()
{
	SetPosition({ 1107,131.5 });
	SetScale({ 284,235 });

	CreateRendererToScale("TopUI.bmp",{284,235});
}





void TopUI::Render()
{
	//DebugRectRender();
}