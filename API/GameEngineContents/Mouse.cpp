#include "Mouse.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

Mouse::Mouse() 
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
	GameEngineRenderer* Renderer = CreateRenderer("Mouse.bmp");
	Renderer->CameraEffectOff();
}

void Mouse::Update()
{
	GetCurPos();
	SetPosition({ CurPos_.x,CurPos_.y });
}

