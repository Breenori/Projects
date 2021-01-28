#include "dynamic_test.h"
#include<cassert>

void simple_usage_test()
{
	dynamic_array dyn;
	dyn.initialize(100);
	dyn.set("MBI", 5);
	dyn.at(53) = "Genkopplung";
	dyn.at(99) = "Regression";
	dyn.print();
}

void clear_test()
{
	dynamic_array dyn;
	dyn.clear();
	assert(dyn.get_max_size() == 0 && dyn.empty());
}

void initialize_test(size_t size)
{
	dynamic_array dyn;
	dyn.initialize(size);

	if (size == 0)
	{
		assert(dyn.empty());
	}
	else
	{
		// this test relies on the functionality of "dynamic_array.set()"
		for (int index(0); index < size; index++)
		{
			assert(dyn.set("test", index) == true);
		}

		assert(dyn.set("test", size) == false);
	}
}

void get_max_size_test(size_t size)
{
	dynamic_array dyn(size);
	assert(dyn.get_max_size() == size);
	// For simplicity, we only test the last accessable and the next inaccessible values.
	if (!dyn.empty())
	{
		assert(dyn.set("test", size - 1) == true);
		assert(dyn.set("test", size) == false);
	}
}

// It's difficult to test these functions separately, since they rely heavily on each other when testing since we can't access the private variables from outside.
void at_test()
{
	dynamic_array dyn(10);
	dyn.at(5) = "atFive";
	assert(dyn.get(5) == "atFive");
	dyn.at(15) = "atFiveModulo";
	assert(dyn.get(5) == "atFiveModulo");

	assert(dyn.get(5) == dyn.at(5));
}
void get_test()
{
	dynamic_array dyn(10);
	dyn.at(5) = "atFive";
	assert(dyn.get(5) == "atFive");

	assert(dyn.get(10) == data_type());
}
void set_test()
{
	dynamic_array dyn(10);
	dyn.set("atSix", 6);
	assert(dyn.get(6) == "atSix");
	dyn.set("atSixMod", 16);
	// Set doesnt change the value if its out of bounds. No modulo is being applied.
	assert(dyn.get(6) == "atSix");
}

/*void test_with_int()
{
	dynamic_array dyn;
	dyn.set(5, 5);
	dyn.at(555) = 3;
	dyn.print();
}*/