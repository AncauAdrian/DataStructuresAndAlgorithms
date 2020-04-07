#include "SortedMap.h"
#include <iostream>

SortedMap::SortedMap(Relation r)	// complexity Theta(1)
{
	this->rel = r;
}

void SortedMap::print()				// complexity O(n)
{
	rec_print(this->root);
	std::cout << std::endl;
}

void SortedMap::rec_print(Node* root) // complexity O(n)
{
	if (root != nullptr)
	{
		rec_print(root->left);
		std::cout << root->data.first << ' ';
		rec_print(root->right);
	}
}

Node* SortedMap::initNode(TKey c, TValue v) // complexity Theta(1)
{
	Node* n = new Node;
	n->data.first = c;
	n->data.second = v;
	n->left = nullptr;
	n->right = nullptr;

	return n;
}

TValue SortedMap::add(TKey c, TValue v)
{
	return this->rec_add(this->root, nullptr, c, v);
}

TValue SortedMap::rec_add(Node*& cur, Node* parent, TKey c, TValue v)	// complexity O(n)
{
	if (cur == nullptr)
	{
		cur = initNode(c, v);
		cur->parent = parent;
		this->_size++;
		return NULL_TVALUE;
	}
	else
	{
		if (cur->data.first == c)
		{
			TValue toreturn = cur->data.second;
			cur->data.second = v;
			return toreturn;
		}

		if (this->rel(cur->data.first, c))
		{
			return this->rec_add(cur->right, cur, c, v);
		}

		return this->rec_add(cur->left, cur, c, v);
	}
}

TValue SortedMap::search(TKey c) const // complexity O(n)
{
	Node* n = this->rec_search(this->root, c);

	if (n == nullptr)
		return NULL_TVALUE;

	return n->data.second;
}

Node* SortedMap::rec_search(Node* cur, TKey c) const
{
	if (cur == nullptr)
		return nullptr;

	if (cur->data.first == c)
		return cur;

	if (this->rel(cur->data.first, c))
		return this->rec_search(cur->right, c);

	return this->rec_search(cur->left, c);
}

TValue SortedMap::remove(TKey c) // complexity O(n)
{
	Node* n = rec_search(this->root, c);	//find a reference to the the node with key c

	if (n == nullptr)						//if a reference cannot be found return
		return NULL_TVALUE;

	TValue toreturn = n->data.second;
	this->_size--;							//decrease size

	Node* parent = n->parent;				//reference to parent of the node we need to remove

	if (n->left == nullptr && n->right == nullptr)			//if the node has no children
	{
		if (parent == nullptr)								//if the root is the only node left and needs to be removed
		{
			this->root = nullptr;
		}
		else												//else if the node does have a parent
		{
			this->setParentChild(n, nullptr);				//set the corresponding child reference of the parent to nullptr
		}
	}
	else if (n->left != nullptr && n->right != nullptr)		//if the node has two children
	{
		Node* max = this->getMaximum(n->left);
		max->left = n->left;
		max->right = n->right;
		

		this->setParentChild(max, nullptr);					//delete the max node from it's place..
		this->setParentChild(n->left, max);					//and palce it instead of n
		this->setParentChild(n->right, max);				//and palce it instead of n
		if (parent != nullptr)
		{
			max->parent = parent;
		}
		else
		{
			this->root = max;
			max->parent = nullptr;
		}

	}
	else													//if the node has one child
	{
		Node* subs = n->left;								//get the correct child

		if (subs == nullptr)
		{
			subs = n->right;
			n->right = nullptr;
		}
		else
			n->left = nullptr;

		this->setParentChild(n, subs);						//set the child accordingly
		if (parent != nullptr)
		{
			subs->parent = parent;
		}
		else
		{
			this->root = subs;
			subs->parent = nullptr;
		}

	}

	delete n;								//finally delete n
	return toreturn;						//and return the deleted value
}

Node* SortedMap::getMinimum(Node* start) const // complexity O(n)
{
	if (start == nullptr)
		return nullptr;

	Node* cur = start;

	while (cur->left != nullptr)
	{
		cur = cur->left;
	}

	return cur;
}

Node* SortedMap::getMaximum(Node* start) const // complexity O(n)
{
	if (start == nullptr)
		return nullptr;

	Node* cur = start;

	while (cur->right != nullptr)
	{
		cur = cur->right;
	}

	return cur;
}

void SortedMap::setParentChild(Node* node, Node* childValue) // complexity Theta(1)
{
	if (node == nullptr)
		return;

	Node* parent = node->parent;

	if (parent == nullptr)
		return;

	if (parent->left != nullptr)
	{
		if (parent->left == node)
		{
			parent->left = childValue;
			return;
		}
	}

	if (parent->right != nullptr)
	{
		if (parent->right == node)
		{
			parent->right = childValue;
			return;
		}
	}
}

Node* SortedMap::getSuccessor(Node* node) const // complexity O(n) because we can get the parent in Theta(1) time
{
	Node* c = node;
	if (node->right != nullptr)
	{
		c = node->right;
		while (c->left != nullptr)
			c = c->left;

		return c;
	}
	else
	{
		Node* p = c->parent;
		while (p != nullptr && p->left != c)
		{
			c = p;
			p = c->parent;
		}
		return p;
	}
}

int SortedMap::size() const // complexity Theta(1)
{
	return this->_size;
}

bool SortedMap::isEmpty() const // complexity Theta(1)
{
	if (this->_size == 0)
		return true;

	return false;
}

SMIterator SortedMap::iterator() const
{
	return SMIterator(*this);
}

void SortedMap::freeTree(Node* cur) // complexity O(n)
{
	if (cur != nullptr)
	{
		freeTree(cur->left);
		freeTree(cur->right);
		delete cur;
	}
}

int SortedMap::getKeyRange() const // complexity O(n)
{
	if (this->isEmpty())
		return -1;

	if (this->_size == 1)
		return 0;

	return this->getMaximum(this->root)->data.first - this->getMinimum(this->root)->data.first;
}

SortedMap::~SortedMap()
{
	this->freeTree(this->root);
}
