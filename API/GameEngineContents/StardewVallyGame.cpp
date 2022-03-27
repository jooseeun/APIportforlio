#include "StardewVallyGame.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
StardewVallyGame::StardewVallyGame() 
{
}

StardewVallyGame::~StardewVallyGame() 
{
}

void StardewVallyGame::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	

	// 현재 디렉토리
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("FarmerHouse");
	CreateLevel<EndingLevel>("Ending");
	//ChangeLevel("Title");
	ChangeLevel("FarmerHouse");
}

void StardewVallyGame::GameLoop()
{

}

void StardewVallyGame::GameEnd()
{

}