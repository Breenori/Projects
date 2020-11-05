#include "bstree.h"
#include<vld.h>
#include<cassert>

void multiply_by_2(bstree::value_t& value);
void test_empty()
{
	bstree bs;
	bs.remove(0);
	bs.apply(multiply_by_2);
	bs.contains(3);
	bs.count(1);
	bs.print();
	assert(bs.empty());
	assert(bs.size() == 0);
	bs.print_2d();
	bs.print_2d_upright();
}
void test_insert()
{
	bstree bs;
	bs.insert(4);
	bs.insert(10);
	bs.insert(9);
	bs.insert(20);
	bs.insert(1);
	bs.insert(3);
	bs.insert(3);
	bs.insert(0);
	bs.insert(26);
	bs.insert(25);
	bs.insert(27);
	bs.insert(28);
	bs.print();
	bs.print_2d();
	// Remove the root node. LEft subtree becomes new root, right subtree is reinserted.

	assert(bs.size() == 12);
	assert(bs.count(3) == 2);
	assert(bs.contains(25));
	bstree::value_t v1;
	assert(bs.at(0, v1) && v1 == 0);

	bstree bs2(bs);
	assert(bs.equals(bs2));
	bs2.apply(multiply_by_2);

	bstree::value_t v2;
	assert(bs.at(3, v1) && bs2.at(3, v2) && v1 * 2 == v2);
	bs.print();
	bs2.print();
}
void test_remove()
{
	bstree bs;
	bs.insert(3);
	bs.insert(2);
	bs.insert(0);
	bs.insert(1);
	bs.insert(25);
	// Insert two children for 25
	bs.insert(24);
	bs.insert(26);
	bs.print_2d();
	bs.remove(25);
	std::cout << "\nAfter removing 25:\n";
	bs.print_2d();
	bs.remove(3);
	std::cout << "\nAfter removing root:\n";
	bs.print_2d();
	assert(!bs.contains(25));

	bs.remove(24);
	bs.remove(26);
	bs.remove(2);
	bs.remove(1);
	bs.remove(0);
	std::cout << "\nAfter removing everything else:\n";
	bs.print();
	assert(bs.empty());
	assert(bs.size() == 0);

	bs.insert(25);
	bs.insert(24);
	bs.insert(26);
	bs.clear();
	assert(bs.empty() && bs.size() == 0);
	
	bs.insert(3);
	bs.insert(3);
	bs.insert(3);
	assert(bs.remove_all(3) == 3 && bs.empty() && bs.size() == 0);
}
void test_prints()
{
	bstree bs;
	bs.insert(4);
	bs.insert(10);
	bs.insert(9);
	bs.insert(20);
	bs.insert(1);
	bs.insert(3);
	bs.insert(3);
	bs.insert(0);
	bs.insert(26);
	bs.insert(25);
	bs.insert(27);
	bs.insert(28);

	std::cout << "Normal:\n";
	bs.print();
	std::cout << "\n2D sideways:\n";
	bs.print_2d();
	std::cout << "\n2D upright:\n";
	bs.print_2d_upright();
}

void main()
{
	test_empty();
	test_insert();
	test_remove();
	test_prints();
}

void multiply_by_2(bstree::value_t& value)
{
	value *= 2;
}
