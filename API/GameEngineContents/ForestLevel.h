#pragma once

// Ό³Έν :
class ForestLevel
{
public:
	// constrcuter destructer
	ForestLevel();
	~ForestLevel();

	// delete Function
	ForestLevel(const ForestLevel& _Other) = delete;
	ForestLevel(ForestLevel&& _Other) noexcept = delete;
	ForestLevel& operator=(const ForestLevel& _Other) = delete;
	ForestLevel& operator=(ForestLevel&& _Other) noexcept = delete;

protected:

private:

};

