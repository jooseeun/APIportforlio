#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class Town2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Town2Level();
	~Town2Level();

	// delete Function
	Town2Level(const Town2Level& _Other) = delete;
	Town2Level(Town2Level&& _Other) noexcept = delete;
	Town2Level& operator=(const Town2Level& _Other) = delete;
	Town2Level& operator=(Town2Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

