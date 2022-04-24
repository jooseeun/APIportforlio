#pragma once

// Ό³Έν :
class Tree
{
public:
	// constrcuter destructer
	Tree();
	~Tree();

	// delete Function
	Tree(const Tree& _Other) = delete;
	Tree(Tree&& _Other) noexcept = delete;
	Tree& operator=(const Tree& _Other) = delete;
	Tree& operator=(Tree&& _Other) noexcept = delete;

protected:

private:

};

