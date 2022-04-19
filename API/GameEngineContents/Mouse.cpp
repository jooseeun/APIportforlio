#include "Mouse.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

Mouse* Mouse::MouseSet = nullptr;

Mouse::Mouse() 
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	ShowCursor(false);
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	GameEngineRenderer* Renderer = CreateRenderer("Mouse.bmp");
	Renderer->CameraEffectOff();
	MouseCol_ = CreateCollision("MouseCol", { 16,20 }, { -8,-10 });
}

void Mouse::Update()
{
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	
}

void Mouse::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MouseSet = this;
}