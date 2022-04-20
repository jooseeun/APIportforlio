#include "Photato.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Photato::Photato() 
{
}

Photato::~Photato() 
{
}

void Photato::Start()
{
	GameEngineRenderer* photato_ = CreateRenderer("Crops.bmp");
	photato_->SetIndex(30);

	GameEngineCollision* photatoCol_ = CreateCollision("Photato", { 64,64 });
}
void Photato::Update()
{

}