#pragma once

// Ό³Έν :
class NPCShopOnner
{
public:
	// constrcuter destructer
	NPCShopOnner();
	~NPCShopOnner();

	// delete Function
	NPCShopOnner(const NPCShopOnner& _Other) = delete;
	NPCShopOnner(NPCShopOnner&& _Other) noexcept = delete;
	NPCShopOnner& operator=(const NPCShopOnner& _Other) = delete;
	NPCShopOnner& operator=(NPCShopOnner&& _Other) noexcept = delete;

protected:

private:

};

