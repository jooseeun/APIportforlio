#include "PlayerCreate.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>


PlayerCreate::PlayerCreate()
	:CurHairColor_(PlayerHairColor::Black),
	CurHairStyle_(PlayerHairStyle::First),
	CurPants_(PlayerPants::First),
	CurShirts_(PlayerShirts::First)
{
}

PlayerCreate::~PlayerCreate() 
{
}

void PlayerCreate::Start()
{
	SetPosition({ 640,360 });
	CreateRenderer("PlayerCreateBack.bmp");
	GameEngineRenderer* Left1 = CreateRenderer("LeftButton.bmp");
	Left1->SetPivot({ -90,0 });
	GameEngineRenderer* Right1 = CreateRenderer("RightButton.bmp");
	Right1->SetPivot({ 90,0 });

	GameEngineRenderer* Left2 = CreateRenderer("LeftButton.bmp");
	Left2->SetPivot({ -90,68 });
	GameEngineRenderer* Right2 = CreateRenderer("RightButton.bmp");
	Right2->SetPivot({ 90,68 });

	GameEngineRenderer* Left3 = CreateRenderer("LeftButton.bmp");
	Left3->SetPivot({ -90,136 });
	GameEngineRenderer* Right3 = CreateRenderer("RightButton.bmp");
	Right3->SetPivot({ 90,136 });

	GameEngineRenderer* Left4 = CreateRenderer("LeftButton.bmp");
	Left4->SetPivot({ -90,204 });
	GameEngineRenderer* Right4 = CreateRenderer("RightButton.bmp");
	Right4->SetPivot({ 90,204 });

	LeftCol1 = CreateCollision("LeftCol1",{44,40},{-90,0});
	LeftCol2= CreateCollision("LeftCol2", { 44,40 }, { -90,68 });
	LeftCol3= CreateCollision("LeftCol3", { 44,40 }, { -90,136 });
	LeftCol4= CreateCollision("LeftCol4", { 44,40 }, { -90,204 });

	RightCol1= CreateCollision("RightCol1", { 44,40 }, { 90,0 });
	RightCol2= CreateCollision("RightCol2", { 44,40 }, { 90,68 });
	RightCol3= CreateCollision("RightCol3", { 44,40 }, { 90,136 });
	RightCol4= CreateCollision("RightCol4", { 44,40 }, { 90,204 });

	Ok_= CreateCollision("StartCol", { 64,64 }, { 275,280 });
	std::string HairColor_ = GetHairColorString();
	std::string HairStyle_ = GetHairStyleString();
	std::string ShirtsStyle_ = GetShirtsStyleString();
	std::string PantsStyle_ = GetPantsStyleString();
	Body_ = CreateRenderer("BodyShirts" + ShirtsStyle_ + ".bmp"); // 24 한줄에
	Arm_ = CreateRenderer("BodyShirts" + ShirtsStyle_ + ".bmp");
	Pants_ = CreateRenderer("Pants" + PantsStyle_ + ".bmp");
	Hair_ = CreateRenderer("Hair" + HairStyle_ + HairColor_ + ".bmp");
	Shirts_ = CreateRenderer("Shirts" + ShirtsStyle_ + ".bmp");
	PlayerUpdate();

}
void PlayerCreate::PlayerUpdate()
{

	std::string HairColor_ = GetHairColorString();
	std::string HairStyle_ = GetHairStyleString();
	std::string ShirtsStyle_ = GetShirtsStyleString();
	std::string PantsStyle_ = GetPantsStyleString();



	Body_ ->SetImage("BodyShirts" + ShirtsStyle_ + ".bmp"); // 24 한줄에
	Arm_ -> SetImage("BodyShirts" + ShirtsStyle_ + ".bmp");
	Pants_->SetImage("Pants" + PantsStyle_ + ".bmp");
	Hair_->SetImage("Hair" + HairStyle_ + HairColor_ + ".bmp");
	Shirts_->SetImage("Shirts" + ShirtsStyle_ + ".bmp");

	Body_->SetIndex(0);
	Arm_->SetIndex(6);
	Pants_->SetIndex(0);
	Hair_->SetIndex(0);
	Shirts_->SetIndex(0);

	Body_->SetPivot({ 0,-180 });
	Arm_->SetPivot({ 0,-180 });
	Pants_->SetPivot({ 0,-180 });
	Hair_->SetPivot({ 0,-180 });
	Shirts_->SetPivot({ 0,-180 });

}
void PlayerCreate::Update()
{
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		if (true == RightCol1->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerHairColor::Black == CurHairColor_)
			{
				CurHairColor_ = PlayerHairColor::Blue;
				PlayerUpdate();
			}
			else if (PlayerHairColor::Blue == CurHairColor_)
			{
				CurHairColor_ = PlayerHairColor::Red;
				PlayerUpdate();
			}
			else if (PlayerHairColor::Red == CurHairColor_)
			{
				CurHairColor_ = PlayerHairColor::Black;
				PlayerUpdate();
			}
		}

		else if (true == LeftCol2->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerHairColor::Red == CurHairColor_)
			{
				CurHairColor_ = PlayerHairColor::Blue;
				PlayerUpdate();
			}
			else if (PlayerHairColor::Blue == CurHairColor_)
			{
				CurHairColor_ = PlayerHairColor::Black;
				PlayerUpdate();
			}
			else if (PlayerHairColor::Black == CurHairColor_)
			{
				CurHairColor_ = PlayerHairColor::Red;
				PlayerUpdate();
			}
		}

		if (true == RightCol2->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerHairStyle::First == CurHairStyle_)
			{
				CurHairStyle_ = PlayerHairStyle::Second;
				PlayerUpdate();
			}
			else if (PlayerHairStyle::Second == CurHairStyle_)
			{
				CurHairStyle_ = PlayerHairStyle::First;
				PlayerUpdate();
			}
		}

		else if (true == LeftCol2->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerHairStyle::First == CurHairStyle_)
			{
				CurHairStyle_ = PlayerHairStyle::Second;
				PlayerUpdate();
			}
			else if (PlayerHairStyle::Second == CurHairStyle_)
			{
				CurHairStyle_ = PlayerHairStyle::First;
				PlayerUpdate();
			}

		}

		if (true == RightCol3->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerShirts::First == CurShirts_)
			{
				CurShirts_ = PlayerShirts::Second;
				PlayerUpdate();
			}
			else if (PlayerShirts::Second == CurShirts_)
			{
				CurShirts_ = PlayerShirts::Third;
				PlayerUpdate();
			}
			else if (PlayerShirts::Third == CurShirts_)
			{
				CurShirts_ = PlayerShirts::First;
				PlayerUpdate();
			}
		}

		else if (true == LeftCol3->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerShirts::Third == CurShirts_)
			{
				CurShirts_ = PlayerShirts::Second;
				PlayerUpdate();
			}
			else if (PlayerShirts::Second == CurShirts_)
			{
				CurShirts_ = PlayerShirts::First;
				PlayerUpdate();
			}
			else if (PlayerShirts::First == CurShirts_)
			{
				CurShirts_ = PlayerShirts::Third;
				PlayerUpdate();
			}

		}
		if (true == RightCol4->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerPants::First == CurPants_)
			{
				CurPants_ = PlayerPants::Second;
				PlayerUpdate();
			}
			else if (PlayerPants::Second == CurPants_)
			{
				CurPants_ = PlayerPants::First;
				PlayerUpdate();
			}

		}

		else if (true == LeftCol4->CollisionCheck("MouseCol"))
		{
			GameEngineSound::SoundPlayOneShot("Bigselect.wav");
			if (PlayerPants::First == CurPants_)
			{
				CurPants_ = PlayerPants::Second;
				PlayerUpdate();
			}
			else if (PlayerPants::Second == CurPants_)
			{
				CurPants_ = PlayerPants::First;
				PlayerUpdate();
			}

		}

		if (true == Ok_->CollisionCheck("MouseCol", CollisionType::Rect, CollisionType::Rect))
		{
			Player::MainPlayer->CurHairColor_ = CurHairColor_;
			Player::MainPlayer->CurHairStyle_ = CurHairStyle_;
			Player::MainPlayer->CurPants_ = CurPants_;
			Player::MainPlayer->CurShirts_ = CurShirts_;
			GameEngine::GetInst().ChangeLevel("FarmHouseLevel");
			GameEngineSound::SoundPlayOneShot("select.wav");
		}
	}
	


	if (true == GameEngineInput::GetInst()->IsDown("DebugONOFF"))
	{
		GetLevel()->IsDebugModeSwitch();
	}


}



std::string PlayerCreate::GetHairColorString()
{
	if (CurHairColor_ == PlayerHairColor::Black)
	{
		return "Black";
	}
	else if (CurHairColor_ == PlayerHairColor::Blue)
	{
		return "Blue";
	}
	else if (CurHairColor_ == PlayerHairColor::Red)
	{
		return "Red";
	}

	return "";
}
std::string PlayerCreate::GetHairStyleString()
{

	if (CurHairStyle_ == PlayerHairStyle::First)
	{
		return "1";
	}
	else if (CurHairStyle_ == PlayerHairStyle::Second)
	{
		return "2";
	}
	return "";
}
std::string PlayerCreate::GetShirtsStyleString()
{

	if (CurShirts_ == PlayerShirts::First)
	{
		return "1";
	}
	else if (CurShirts_ == PlayerShirts::Second)
	{
		return "2";
	}
	else if (CurShirts_ == PlayerShirts::Third)
	{
		return "3";
	}
	return "";
}
std::string PlayerCreate::GetPantsStyleString()
{

	if (CurPants_ == PlayerPants::First)
	{
		return "1";
	}
	else if (CurPants_ == PlayerPants::Second)
	{
		return "2";
	}
	return "";
}