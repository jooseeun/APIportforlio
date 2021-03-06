#include <Windows.h>

#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/StardewVallyGame.h>

StardewVallyGame MyGame;

void GameInit()
{
    MyGame.GameInit();
}
void GameLoop()
{
    MyGame.GameLoop();
}

int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char* lpCmdLine,
    _In_ int       nCmdShow)
{

    GameEngine::Start<StardewVallyGame>();
}