#include "HealthUI.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

HealthUI* HealthUI::HealthUISet = nullptr;

HealthUI::HealthUI()
	:PlayerHp_(224.0f)
{
}

HealthUI::~HealthUI()
{
}

void HealthUI::Start()
{
	SetPosition({ 1198,593 + 112 });
	GameEngineRenderer* Renderer = CreateRendererToScale("HealthUI.bmp", { 48,224 }, static_cast<int>(ORDER::UI), RenderPivot::BOT);
	Renderer->CameraEffectOff();
	HealthBar_ = CreateRendererToScale("HealthBar.bmp", { 48,224 }, static_cast<int>(ORDER::UI), RenderPivot::BOT);
	HealthBar_->CameraEffectOff();
}

void HealthUI::Update()
{
	UpdateEnergyValue();
}
void HealthUI::UpdateEnergyValue()
{
	HealthBar_->SetScale({ 52, PlayerHp_ });
	HealthBar_->CameraEffectOff();

	if (PlayerHp_ <= 0)
	{
		PlayerHp_ = 100.0f;
		GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
		//죽으면 집으로 돌아가기
	}
	// 만약 0이 사망
}
void HealthUI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	HealthUISet = this;
}