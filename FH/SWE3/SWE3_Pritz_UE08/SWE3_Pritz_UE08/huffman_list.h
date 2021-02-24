#ifndef HUFFMAN_LIST_H
#define HUFFMAN_LIST_H
#include<map>
#include<algorithm>
using std::map;
using std::pair;

class HuffmanTreeNode {
private:
	pair<char, double> entry;
	HuffmanTreeNode* left;
	HuffmanTreeNode* right;
public:
	HuffmanTreeNode() : entry({ ' ', 0 }), left(nullptr), right(nullptr) {}
	HuffmanTreeNode(pair<const char, double> const& value) : entry(value) {};

	HuffmanTreeNode* get_left() const {
		return left;
	}
	HuffmanTreeNode* get_right() const {
		return right;
	};

	void set_left(HuffmanTreeNode* left)
	{
		this->left = left;
	}
	void set_right(HuffmanTreeNode* right)
	{
		this->right = right;
	}

	pair<char const, double> get_entry() const
	{
		return entry;
	}
};

class HuffmanTree {
private:
	HuffmanTreeNode* root;
public:
	HuffmanTree() : root(nullptr) {}
	HuffmanTree(pair<const char, double> const& value)
	{
		root = new HuffmanTreeNode(value);
	}

	HuffmanTree* combine(HuffmanTree* t1, HuffmanTree* t2)
	{
		double sum = t1->root->get_entry().second + t2->root->get_entry().second;
		HuffmanTree* newHT = new HuffmanTree({ '-',  sum });
		newHT->root->set_left(t1->root);
		newHT->root->set_right(t2->root);
	}

	HuffmanTreeNode* get_root()
	{
		return root;
	}
};

class HuffmanListNode {
private:
	HuffmanListNode* next;
	HuffmanTree* ht;

public:
	HuffmanListNode()
	{
		next = nullptr;
		ht = nullptr;
	}
	HuffmanListNode(pair<const char, double> const& value) : HuffmanListNode()
	{
		ht = new HuffmanTree(value);
	}

	HuffmanListNode* get_next()
	{
		return next;
	}
	void set_next(HuffmanListNode* next)
	{
		this->next = next;
	}
	HuffmanTree* get_tree()
	{
		return ht;
	}
	double get_total_value() const
	{
		return this->ht->get_root()->get_entry().second;
	}
};

class HuffmanList {
private:
	HuffmanListNode* root;
	size_t size;

	void insert(pair<const char, double> const& value)
	{
		HuffmanListNode* newNode = new HuffmanListNode(value);
		if (root == nullptr)
		{
			root = newNode;
			size = 0;
		}
		else
		{
			HuffmanListNode* ref = root;
			// If root is bigger than new value --> become new root
			if (ref == root && ref->get_total_value() > value.second)
			{
				root = newNode;
				root->set_next(ref);
			}
			else
			{
				while (ref->get_next() != nullptr && ref->get_next()->get_total_value() < value.second)
				{
					ref = ref->get_next();
				}

				if (ref->get_next() == nullptr)
				{
					ref->set_next(newNode);
				}
				else
				{
					newNode->set_next(ref->get_next());
					ref->set_next(newNode);
				}
			}
		}
	}
	void create_tree()
	{
		HuffmanListNode* n1 = root;
		root = root->get_next();
		HuffmanListNode* n2 = root;
		root = root->get_next();

		HuffmanTree t1;
	}

public:
	HuffmanList() : root(nullptr) {}
	HuffmanList(map<char, double> const& frequencies) : HuffmanList()
	{
		std::for_each(frequencies.begin(), frequencies.end(), [this](pair<const char, double> const& entry) {insert(entry); });
	}
};


#endif