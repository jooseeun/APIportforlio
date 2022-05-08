#include "EnergyUI.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

EnergyUI* EnergyUI::EnergyUISet = nullptr;

EnergyUI::EnergyUI()
	:EnergyValue_(224.0f)
{
}

EnergyUI::~EnergyUI() 
{
}

void EnergyUI::Start()
{
	SetPosition({1247,593+112});
	GameEngineRenderer* Renderer = CreateRendererToScale("EnergyUI.bmp", { 52,224 }, static_cast<int>(ORDER::UI), RenderPivot::BOT);
	Renderer->CameraEffectOff();
	EnergyUIBar = CreateRendererToScale("EnergyUIBar.bmp",{52,224}, static_cast<int>(ORDER::UI),RenderPivot::BOT);
	EnergyUIBar->CameraEffectOff();
}

void EnergyUI::Update()
{
	UpdateEnergyValue();
}
void EnergyUI::UpdateEnergyValue()
{
	EnergyUIBar->SetScale({ 52, EnergyValue_ });
	EnergyUIBar->CameraEffectOff();
	// 만약 0이 되면 탈진
	if (EnergyValue_ <= 0)
	{
		Sound_ = GameEngineSound::SoundPlayControl("death.wav");
		Sound_.Volume(0.8f);
		EnergyValue_ = 50;
		GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
	}
}
void EnergyUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	EnergyUISet = this;
}