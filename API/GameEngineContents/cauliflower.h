#pragma once

// Ό³Έν :
class cauliflower
{
public:
	// constrcuter destructer
	cauliflower();
	~cauliflower();

	// delete Function
	cauliflower(const cauliflower& _Other) = delete;
	cauliflower(cauliflower&& _Other) noexcept = delete;
	cauliflower& operator=(const cauliflower& _Other) = delete;
	cauliflower& operator=(cauliflower&& _Other) noexcept = delete;

protected:

private:

};

