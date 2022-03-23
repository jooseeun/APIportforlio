#pragma once
#include <GameEngine/GameEngineLevel.h>
// Ό³Έν :
class Mine2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine2Level();
	~Mine2Level();

	// delete Function
	Mine2Level(const Mine2Level& _Other) = delete;
	Mine2Level(Mine2Level&& _Other) noexcept = delete;
	Mine2Level& operator=(const Mine2Level& _Other) = delete;
	Mine2Level& operator=(Mine2Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

