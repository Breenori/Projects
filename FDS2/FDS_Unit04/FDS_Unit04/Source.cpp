#include "bmp.h"

void main() {
	graphics::bitmap_type bmp;
	bmp.m_p_data = nullptr;
	graphics::create(bmp, 5, 5);
	graphics::pixel_type p;
	graphics::load_from_file(bmp, "02.bmp");

	for (size_t x(0); x < bmp.m_info_header.width; x++)
	{
		for (size_t y(0); y < bmp.m_info_header.height; y++)
		{
			graphics::pixel_type p = graphics::at(bmp, x, y);
			p.red = 255 - p.red;
			p.green = 255 - p.green;
			p.blue = 255 - p.blue;
			graphics::at(bmp, x, y) = p;
		}
	}

	graphics::write_to_file(bmp, "test.bmp");
}