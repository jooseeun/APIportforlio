#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class Mine1Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Mine1Level();
	~Mine1Level();

	// delete Function
	Mine1Level(const Mine1Level& _Other) = delete;
	Mine1Level(Mine1Level&& _Other) noexcept = delete;
	Mine1Level& operator=(const Mine1Level& _Other) = delete;
	Mine1Level& operator=(Mine1Level&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

