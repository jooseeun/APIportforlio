#pragma once

// Ό³Έν :
class BabyChicken
{
public:
	// constrcuter destructer
	BabyChicken();
	~BabyChicken();

	// delete Function
	BabyChicken(const BabyChicken& _Other) = delete;
	BabyChicken(BabyChicken&& _Other) noexcept = delete;
	BabyChicken& operator=(const BabyChicken& _Other) = delete;
	BabyChicken& operator=(BabyChicken&& _Other) noexcept = delete;

protected:

private:

};

