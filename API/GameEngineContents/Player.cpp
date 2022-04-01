#include "Player.h"
#include "BackGround.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineImage.h>

Player::Player()
	:Speed_(205.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	//defalut 값
	GameEngineRenderer* Body = CreateRendererToScale("Body.bmp", { 64, 128 });
	Body->SetIndex(0);
	GameEngineRenderer* Arm = CreateRendererToScale("Body.bmp", { 64, 128 });
	Arm->SetIndex(6);
	GameEngineRenderer* Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,4 });
	Hair->SetIndex(101);
	GameEngineRenderer* Pants = CreateRendererToScale("Pants.bmp", { 64, 128 });
	Pants->SetIndex(0);
	GameEngineRenderer* Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
	Shirts->SetIndex(387);

	//{ // 캐릭터 아래로 걷는 모션
	//	GameEngineRenderer* BodyDown = CreateRenderer();
	//	BodyDown->CreateAnimation("Body.bmp", "PlayerWalkDownLag", 1, 2, 0.15f, true);
	//	BodyDown->ChangeAnimation("PlayerWalkDownLag");
	//	GameEngineRenderer* ArmDown = CreateRenderer();
	//	ArmDown->CreateAnimation("Body.bmp", "PlayerWalkDownArm", 7, 8, 0.15f, true);
	//	ArmDown->ChangeAnimation("PlayerWalkDownArm");
	//	GameEngineRenderer* Hair = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,9 });
	//	Hair->SetIndex(101);
	//	GameEngineRenderer* PantsDown = CreateRenderer();
	//	PantsDown->CreateAnimation("Pants.bmp", "PlayerWalkDownPants", 1, 2, 0.15f, true);
	//	PantsDown->ChangeAnimation("PlayerWalkDownPants");
	//	GameEngineRenderer* Shirts = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
	//	Shirts->SetIndex(387);
	//}
	// 
	//{ // 캐릭터 오른쪽으로 걷는 모션
	//	GameEngineRenderer* BodyRight = CreateRenderer();
	//	BodyRight->CreateAnimation("Body.bmp", "PlayerWalkRightLag", 19, 20, 0.15f, true);
	//	BodyRight->ChangeAnimation("PlayerWalkRightLag");
	//	GameEngineRenderer* ShirtsRight = CreateRendererToScale("Shirts.bmp", { 32, 32 }, RenderPivot::CENTER, { 0,16 });
	//	ShirtsRight->SetIndex(419);
	//	GameEngineRenderer* ArmRight = CreateRenderer();
	//	ArmRight->CreateAnimation("Body.bmp", "PlayerWalkRightArm", 25, 26, 0.15f, true);
	//	ArmRight->ChangeAnimation("PlayerWalkRightArm");
	//	GameEngineRenderer* HairRight = CreateRendererToScale("Hair.bmp", { 64, 128 }, RenderPivot::CENTER, { 0,9 });
	//	HairRight->SetIndex(109);
	//	GameEngineRenderer* PantsDown = CreateRenderer();
	//	PantsDown->CreateAnimation("Pants.bmp", "PlayerWalkDownPants", 121, 122, 0.15f, true);
	//	PantsDown->ChangeAnimation("PlayerWalkDownPants");
	//}
	
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');

	}

}

void Player::Update()
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find("FarmHouseColMap.bmp");
	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}
	
	float4 NextPos;
	float4 CheckPos;
	float4 Move = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Move = float4::RIGHT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos+float4{32.0f,0.0f};
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		Move = float4::LEFT;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ -32.0f,0.0f };
	}


	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		Move = float4::UP;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,-64.0f };
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Move = float4::DOWN;
		NextPos = GetPosition() + (Move * GameEngineTime::GetDeltaTime() * Speed_);
		CheckPos = NextPos + float4{ 0.0f,64.0f };

	}

	{

		int Color = MapColImage_->GetImagePixel(CheckPos);

		if (RGB(255, 0, 0) != Color)
		{
			SetMove(Move * GameEngineTime::GetDeltaTime() * Speed_);
		}
		if (RGB(0, 0, 255) == Color)
		{
			GameEngine::GetInst().ChangeLevel("FarmLevel");
		}
		
	} // 맵충돌
	

	// 카메라 이동

	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());
	
	//if (0 > GetLevel()->GetCameraPos().x)
	//{
	//	float4 CameraPos = GetLevel()->GetCameraPos();
	//	CameraPos.x = 0;
	//	GetLevel()->SetCameraPos(CameraPos);
	//}
	//if (0 > GetLevel()->GetCameraPos().y)
	//{
	//	float4 CameraPos = GetLevel()->GetCameraPos();
	//	CameraPos.y = 0;
	//	GetLevel()->SetCameraPos(CameraPos);
	//}


}
void Player::Render()
{

}