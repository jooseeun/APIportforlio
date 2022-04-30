#include "Num4.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
Num4::Num4() 
	:Time_(1.0f)
{
}

Num4::~Num4() 
{
}

void Num4::Start()
{
	GameEngineRenderer* Render = CreateRenderer("Num4.bmp");
	
}
void Num4::Update()
{
	SetMove(float4{0,-1} *GameEngineTime::GetDeltaTime() * 10.0f);
	Time_ -= GameEngineTime::GetDeltaTime();
	if (Time_ <= 0)
	{
		Death();
	}
}
