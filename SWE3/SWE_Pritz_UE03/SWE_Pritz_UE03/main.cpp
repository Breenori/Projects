#include "rational_type.h"

void main()
{
	rational_t rat1(1, 2);
	rational_t rat2(1, 2);
	rat1.print();
	rat1 *= rat2;
	rat1.print();
}