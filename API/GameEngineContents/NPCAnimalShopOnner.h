#pragma once

// Ό³Έν :
class NPCAnimalShopOnner
{
public:
	// constrcuter destructer
	NPCAnimalShopOnner();
	~NPCAnimalShopOnner();

	// delete Function
	NPCAnimalShopOnner(const NPCAnimalShopOnner& _Other) = delete;
	NPCAnimalShopOnner(NPCAnimalShopOnner&& _Other) noexcept = delete;
	NPCAnimalShopOnner& operator=(const NPCAnimalShopOnner& _Other) = delete;
	NPCAnimalShopOnner& operator=(NPCAnimalShopOnner&& _Other) noexcept = delete;

protected:

private:

};

