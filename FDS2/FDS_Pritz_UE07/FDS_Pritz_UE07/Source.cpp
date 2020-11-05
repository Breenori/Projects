#include<iostream>
#include "bmp.h"
#include<time.h>

void main()
{
	srand(time(0));
	graphics::bitmap_type bmp;
	graphics::read_from(bmp, "image/stars.bmp");
	size_t n(graphics::detect_objects(bmp, 150, graphics::background_type::BG_DARK));
	std::cout << "In this image there are " << n << " objects.\n";
}