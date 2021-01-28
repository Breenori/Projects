#include "bmp.h"
#include<cassert>
#include<fstream>

// This is the slightly adjusted version of the function inside the exercises pdf.
// Since my detect_edges function converts to gray inside, i instead put the to_gray down. This way every file should differ.
void referencetest();
// This testfunction is responsible for testing all the functions related to accessing pointers
void testfunction1(graphics::bitmap_type const& bmp);
// This testfunction is responsible for all the other functions that haven't yet been tested
void testfunction2();

void main() 
{
	referencetest();
	graphics::bitmap_type bmp = graphics::generate_bitmap("./data/stemcells.bmp");
	testfunction1(bmp);
	testfunction2();
}

void referencetest()
{
	graphics::bitmap_type b0 = graphics::generate_bitmap(300, 100);
	graphics::bitmap_type b1 = graphics::generate_bitmap(300, 100, graphics::red);
	graphics::bitmap_type b2;
	graphics::bitmap_type b3;
	b2 = b1; assert(graphics::equals(b2, b1));
	graphics::read_from(b3, "./data/stemcells.bmp");
	graphics::detect_edges(b3);
	graphics::invert(b3);
	graphics::swap(b2, b3);
	graphics::write_to(b1, "./data/output-1.bmp");
	graphics::write_to(b2, "./data/output-2.bmp");
	graphics::to_gray(b3);
	graphics::write_to(b3, "./data/output-3.bmp");
}
void testfunction1(graphics::bitmap_type const& bmp)
{
	// Testing read_from (inside generate_bitmap) using a valid cstring
	// Also getting a non constant bitmap to differentiate between functions!
	char const* p_name("./data/stemcells.bmp");
	graphics::bitmap_type bmp1 = graphics::generate_bitmap(p_name);
	graphics::detect_edges(bmp1);

	// When copying bitmap_types its important to create a new pointer for the data.
	// Else, all the data would be changed in the source bitmap as well!
	// Since in the edge graphics 0,0 is always black, we set it to red in the copied bitmap and check that the source hasn't been affected.
	graphics::bitmap_type bmp2 = graphics::generate_bitmap(bmp1);
	graphics::at(bmp2, 0, 0).red = 255;
	assert(graphics::at(bmp1, 0, 0).red != 255);

	// In this specific case, the scanline width is already divideable by 4.
	// Thats why we can simply check if the functions work, by looking at the upper right corner.
	// We first set the pixel to purple and then set the last byte (red portion of that pixel) to zero. Purple - red = blue.
	graphics::pixel_type* p = graphics::get_pixels(bmp1);
	size_t n1 = graphics::get_num_pixels(bmp1);
	p[n1 - 1] = graphics::purple;
	graphics::byte_type* b = graphics::get_image(bmp1);
	size_t n2 = graphics::get_image_size(bmp1);
	b[n2 - 1] = 0;

	// Checking that the const versions also work!
	graphics::pixel_type const pixel = graphics::at(bmp, 0, 0);
	graphics::pixel_type p_confirm = *(reinterpret_cast<graphics::pixel_type*>(bmp.m_p_data));
	assert(
		pixel.red == p_confirm.red && pixel.green == p_confirm.green && pixel.blue == p_confirm.blue
	);
	graphics::pixel_type const* pointer = graphics::get_pixels(bmp);
	if (bmp.m_p_data != nullptr)
	{
		assert(pointer != nullptr);
	}
	graphics::byte_type const* byte = graphics::get_image(bmp);
	if (bmp.m_p_data != nullptr)
	{
		assert(byte != nullptr);
	}

	// Testing write_out (inside generate_bitmap) using a valid cstring
	char const* p_outputname("./data/output-test1.bmp");
	graphics::write_to(bmp1, p_outputname);
}
void testfunction2()
{
	char const* filename("./data/cells.bmp");
	// Since generate_bitmap(char const*) converts to string and then creates an ifstream based on that, this is the only function we have to call in order to test functionality. (because of delegation)
	graphics::bitmap_type bmp = graphics::generate_bitmap(filename);
	graphics::bitmap_type bmp_copy = graphics::generate_bitmap(bmp);
	assert(graphics::equals(bmp, bmp_copy));
	
	graphics::clear(bmp);
	assert(
		bmp.m_p_data == nullptr					&& bmp.m_size_scan_line == 0				&& bmp.m_size_pixel == 3 &&
		bmp.m_file_header.signature[0] == 'B'	&& bmp.m_file_header.signature[1] == 'M'	&& bmp.m_file_header.size == 0 &&
		bmp.m_file_header.offset == 0			&& bmp.m_file_header.reserved_1 == 0		&& bmp.m_file_header.reserved_2 == 0 &&
		bmp.m_info_header.size == 0				&& bmp.m_info_header.width == 0				&& bmp.m_info_header.height == 0 &&
		bmp.m_info_header.planes == 1			&& bmp.m_info_header.bit_count == 24		&& bmp.m_info_header.compression == 0 &&
		bmp.m_info_header.size_image == 0		&& bmp.m_info_header.x_pels_pm == 0			&& bmp.m_info_header.y_pels_pm == 0 &&
		bmp.m_info_header.clr_used == 0			&& bmp.m_info_header.clr_important == 0
	);
			
	resize(bmp, 500, 100, graphics::red);	
	
	graphics::write_to(bmp, "./data/output-test2.bmp");
}
