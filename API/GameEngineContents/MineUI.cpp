#include "MineUI.h"
#include "Time.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>


MineUI::MineUI() 
{

}

MineUI::~MineUI()
{
}


void MineUI::Start()
{
	SetPosition({ 35,45 });
	MineRender = CreateRenderer();
}


void MineUI::Update()
{
	
}