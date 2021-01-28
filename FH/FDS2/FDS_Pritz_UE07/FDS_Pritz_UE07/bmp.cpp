#include "bmp.h"
#include "pfc-mini.hpp"
#include <fstream>

graphics::bitmap_type& graphics::generate_bitmap()
{
// Since we are returning a reference, we need to dynamically allocate storage, or else the variable won't live after the function.
bitmap_type* bmp = new bitmap_type;
(*bmp).m_p_data = nullptr;
graphics::clear(*bmp);
return *bmp;
}
graphics::bitmap_type& graphics::generate_bitmap(std::size_t const w, std::size_t const h, graphics::pixel_type const c)
{
	// Create a basic bitmap by delegating to standard-function.
	bitmap_type bmp = generate_bitmap();

	// Initialize it by delegating to create. Then fill up all the pixels with the desired color.
	if (w > 0 && h > 0 && w < 8192 && h < 8192)
	{
		graphics::create(bmp, w, h);
		graphics::fill(bmp, c);
	}
	else
	{
		std::cout << "Invalid dimensions! Can't create bitmap with size " << w << " * " << h << "!" << std::endl;
	}

	return bmp;
}
graphics::bitmap_type& graphics::generate_bitmap(char const* const p_name)
{
	bitmap_type bmp = generate_bitmap();
	graphics::read_from(bmp, p_name);
	return bmp;
}
graphics::bitmap_type& graphics::generate_bitmap(std::string const& name)
{
	bitmap_type bmp = generate_bitmap();
	graphics::read_from(bmp, name);
	return bmp;
}
graphics::bitmap_type& graphics::generate_bitmap(std::istream& in)
{
	bitmap_type bmp = generate_bitmap();
	graphics::read_from(bmp, in);
	return bmp;
}
graphics::bitmap_type& graphics::generate_bitmap(bitmap_type const& src)
{
	bitmap_type* dest = new bitmap_type;
	*dest = src;
	(*dest).m_p_data = new byte_type[src.m_info_header.size_image];
	for (uint32_type i(0); i < src.m_info_header.size_image; i++)
	{
		dest->m_p_data[i] = src.m_p_data[i];
	}
	return *dest;
}

void graphics::clear(graphics::bitmap_type& bmp)
{
	bmp.m_file_header.signature[0] = 'B';
	bmp.m_file_header.signature[1] = 'M';
	bmp.m_file_header.size = 0;
	bmp.m_file_header.reserved_1 = 0;
	bmp.m_file_header.reserved_2 = 0;
	bmp.m_file_header.offset = 0;

	bmp.m_info_header.size = 0;
	bmp.m_info_header.width = 0;
	bmp.m_info_header.height = 0;
	bmp.m_info_header.planes = 1;
	bmp.m_info_header.bit_count = 24;
	bmp.m_info_header.compression = 0;
	bmp.m_info_header.size_image = 0;
	bmp.m_info_header.x_pels_pm = 0;
	bmp.m_info_header.y_pels_pm = 0;
	bmp.m_info_header.clr_used = 0;
	bmp.m_info_header.clr_important = 0;

	if (bmp.m_p_data != nullptr)
	{
		delete[] bmp.m_p_data;
		bmp.m_p_data = nullptr;
	}

	bmp.m_size_scan_line = 0;
	bmp.m_size_pixel = 3;
}
void graphics::resize(graphics::bitmap_type& bmp, std::size_t const w, std::size_t const h, graphics::pixel_type const c)
{
	if (w > 0 && h > 0)
	{
		bmp = generate_bitmap(w, h, c);
	}
	else
	{
		clear(bmp);
	}
}

bool graphics::equals(graphics::bitmap_type const& lhs, graphics::bitmap_type const& rhs)
{
	if (lhs.m_p_data != nullptr && rhs.m_p_data != nullptr)
	{
		// If size is different
		if (lhs.m_info_header.width != rhs.m_info_header.width || lhs.m_info_header.height != rhs.m_info_header.height)
		{
			return false;
		}

		bool equal(true);

		// Checks all VISIBLE pixels for similarity
		for (size_t x(0); x < get_width(lhs); x++)
		{
			for (size_t y(0); y < get_height(lhs); y++)
			{
				if (at(lhs, x, y).red != at(rhs, x, y).red || at(lhs, x, y).red != at(rhs, x, y).red || at(lhs, x, y).red != at(rhs, x, y).red)
				{
					equal = false;
				}
			}
		}

		return equal;
	}
	// Return if both are nullpointer
	return lhs.m_p_data == rhs.m_p_data;
}
void graphics::swap(graphics::bitmap_type& lhs, graphics::bitmap_type& rhs)
{
	std::swap(lhs, rhs);
}
graphics::pixel_type& graphics::at(graphics::bitmap_type& bmp, size_t const x, size_t const y)
{
	// wäre eigentlich ein byte_t pointer, wird aber händisch gezwungen auf pixel_type zu casten.
	return *(reinterpret_cast <graphics::pixel_type*>(bmp.m_p_data + y * bmp.m_size_scan_line + bmp.m_size_pixel * x));
}
graphics::pixel_type const& graphics::at(graphics::bitmap_type const& bmp, size_t const x, size_t const y)
{
	// wäre eigentlich ein byte_t pointer, wird aber händisch gezwungen auf pixel_type zu casten.
	return *(reinterpret_cast <graphics::pixel_type*>(bmp.m_p_data + y * bmp.m_size_scan_line + bmp.m_size_pixel * x));
}
std::size_t graphics::get_height(graphics::bitmap_type const& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		return bmp.m_info_header.height;
	}
	else
	{
		std::cout << "Unable to get 'height'. Please first initialize the file!\n";
		return 0;
	}
}
std::size_t graphics::get_width(graphics::bitmap_type const& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		return bmp.m_info_header.width;
	}
	else
	{
		std::cout << "Unable to get 'width'. Please first initialize the file!\n";
		return 0;
	}
}
std::size_t graphics::get_image_size(graphics::bitmap_type const& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		// Returning bmp.m_info_header.m_size_image is NOT sufficient!
		// The value is being calculated correctly if we make our own bitmap with dimensions, but NOT if using pfc.read!
		// To further illustrate, In this specific case the dimensions of this bitmap are 500 x 336 = 168.000 pixel.
		// Multiplied by 3 = 504.000 byte. But pfc returns 504.002 byte (but the right amount of pixels) and therefor returns (in our case) the wrong value.
		// This is especially weird, since the scanline doesn't contain additional data, because it was already divideable by 4.
		return bmp.m_size_scan_line * get_height(bmp);
	}
	else
	{
		std::cout << "Unable to get 'image size'. Please first initialize the file!\n";
		return 0;
	}
}
std::size_t graphics::get_num_pixels(graphics::bitmap_type const& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		return get_height(bmp) * get_width(bmp);
	}
	else
	{
		std::cout << "Unable to get 'number of pixels'. Please first initialize the file!\n";
		return 0;
	}
}
graphics::byte_type* graphics::get_image(graphics::bitmap_type& bmp)
{
	return bmp.m_p_data;
}
graphics::byte_type const* graphics::get_image(graphics::bitmap_type const& bmp)
{
	return bmp.m_p_data;
}
graphics::pixel_type* graphics::get_pixels(graphics::bitmap_type& bmp)
{
	// forcing conversion from byte_type to pixel_type
	return reinterpret_cast<graphics::pixel_type*>(bmp.m_p_data);
}
graphics::pixel_type const* graphics::get_pixels(graphics::bitmap_type const& bmp)
{
	// forcing conversion from byte_type to pixel_type
	return reinterpret_cast<graphics::pixel_type*>(bmp.m_p_data);
}

bool graphics::read_from(graphics::bitmap_type& bmp, char const* const file_name)
{
	// convert cstring to string and delegate to read_from(bitmap_type, string)
	std::string const name_as_string(file_name);
	return read_from(bmp, name_as_string);
}
bool graphics::read_from(graphics::bitmap_type& bmp, std::string const& file_name)
{
	// Create an ifstream using the filename and open it in binary mode.
	std::ifstream in(file_name, std::ios_base::binary);

	bool ok(false);

	// if the file couldnt be opened, close the stream and print an error.
	if (!in)
	{
		in.close();
		std::cout << "ERROR: Error opening file '" << file_name << "'.\n";
	}
	else
	{
		// In order to close the file properly, we need to save the returnvalue of the next delegate function instead of immediately returning it.
		ok = read_from(bmp, in);
		in.close();
	}

	return ok;
}
bool graphics::read_from(graphics::bitmap_type& bmp, std::istream& in)
{
	clear(bmp);
	// Read the file header using the pfc function.
	// If the file header doesn't meet the requirements, an error message is displayed.
	pfc::read(in, bmp.m_file_header);
	if (bmp.m_file_header.signature[0] != 'B' || bmp.m_file_header.signature[1] != 'M' || bmp.m_file_header.reserved_1 != 0 ||
		bmp.m_file_header.reserved_2 != 0 || bmp.m_file_header.offset != (sizeof(file_header_type) + sizeof(info_header_type)))
	{
		std::cout << "ERROR: Corrupt file header.\n";
		return false;
	}

	// Read the info header using the pfc function.
	// If the info header doesn't meet the requirements, an error message is displayed.
	// NOTE: 16bit and 32 bit bitmap files do exist, but for the sake of simplicity we exclude them.
	pfc::read(in, bmp.m_info_header);
	if (bmp.m_info_header.bit_count != 24 || bmp.m_info_header.planes != 1	)
	{
		std::cout << "ERROR: Corrupt info header.\n";
		std::cout << "NOTE: Only 24bit bitmaps are allowed!\n";
		return false;
	}

	// Initialize the m_p_data pointer by dynamically allocating the needed space and fill it using the pfc function.
	bmp.m_p_data = new byte_type[bmp.m_info_header.size_image];
	in.seekg(bmp.m_file_header.offset); // jumps to specific point in stream
	pfc::read_ptr(in, bmp.m_p_data, bmp.m_info_header.size_image);

	bmp.m_size_scan_line = (int)ceil(bmp.m_size_pixel * bmp.m_info_header.width * 0.25) * 4;

	return true;
}

bool graphics::write_to(graphics::bitmap_type const& bmp, char const* const file_name)
{
	// convert cstring to string and delegate
	std::string const name_as_string(file_name);
	return write_to(bmp, name_as_string);
}
bool graphics::write_to(bitmap_type const& bmp, std::string const& file_name)
{
	std::ofstream out(file_name, std::ios_base::binary);
	// again, save intermediate output of delegate function to properly close the output stream before returning.
	bool ok(false);
	if (out)
	{
		ok = write_to(bmp, out);
	}
	else
	{
		std::cout << "File " << file_name << " couldn't be opened for writing!\n";
	}
	out.close();
	return ok;
}
bool graphics::write_to(graphics::bitmap_type const& bmp, std::ostream& out)
{
	bool ok(true);

	if (out)
	{
		// If one of the pfc functions returns false, print an error.
		if (
			!(pfc::write(out, bmp.m_file_header) &&
			pfc::write(out, bmp.m_info_header) &&
			pfc::write_ptr(out, bmp.m_p_data, bmp.m_info_header.size_image))
			)
		{
			std::cout << "ERROR: File couldn't be written to disk." << std::endl;
			ok = false;
		}
	}

	return ok;
}

void graphics::detect_edges(graphics::bitmap_type& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		// Define the sobel filter matrices.
		std::vector<std::vector<int>> xmask;
		xmask.push_back({ -1,0,1 });
		xmask.push_back({ -2,0,2 });
		xmask.push_back({ -1,0,1 });

		std::vector<std::vector<int>> ymask;
		ymask.push_back({ -1,-2,-1 });
		ymask.push_back({ 0, 0, 0 });
		ymask.push_back({ 1, 2, 1 });

		// Create a separate c array to hold all the values for magnitude
		// At the same time find out the maximum magnitude.
		int* values = new int[bmp.m_info_header.size_image];
		int maxmag = 0;

		for (size_t x(1); x < bmp.m_info_header.width - 1; x++)
		{
			for (size_t y(1); y < bmp.m_info_header.height - 1; y++)
			{
				int sx(0);
				int sy(0);
				get_sobel(bmp, x, y, sx, sy, xmask, ymask);
				int magnitude = sqrt(sx * sx + sy * sy);
				values[y * bmp.m_info_header.width + x] = magnitude;
				if (magnitude > maxmag)
				{
					maxmag = magnitude;
				}
			}
		}


		// After calculating all magnitudes and the maximum magnitude, we set all image pixels by normalizing the values to achieve values between 0 and 255.
		// The edges of the image need to be set separately, because for these pixels not all elements exist for the filtermask.
		for (size_t x(0); x < bmp.m_info_header.width; x++)
		{
			for (size_t y(0); y < bmp.m_info_header.height; y++)
			{
				if (x == 0 || x == bmp.m_info_header.width - 1 || y == 0 || y == bmp.m_info_header.height - 1)
				{
					at(bmp, x, y) = { 0,0,0 };
				}
				else
				{
					byte_type norm_mag = (values[y * bmp.m_info_header.width + x] * 1.0f / maxmag) * 255;
					at(bmp, x, y) = { norm_mag,norm_mag,norm_mag };
				}
			}
		}

		delete[] values;
		values = nullptr;
	}
	else
	{
		std::cout << "Unable to detect edges. Please first initialize the file!\n";
	}
}
void graphics::fill(bitmap_type& bmp, pixel_type const color)
{
	if (bmp.m_p_data != nullptr)
	{
		// Set the color for each pixel.
		for (size_t x(0); x < bmp.m_info_header.width; x++)
		{
			for (size_t y(0); y < bmp.m_info_header.height; y++)
			{
				graphics::at(bmp, x, y) = color;
			}
		}
	}
	else
	{
		std::cout << "Unable to fill bitmap with desired color. Please first initialize the file!\n";
	}
}
void graphics::invert(graphics::bitmap_type& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		// Invert each pixel by setting the color-subparts to 255 minus the current value.
		for (size_t x(0); x < bmp.m_info_header.width; x++)
		{
			for (size_t y(0); y < bmp.m_info_header.height; y++)
			{
				pixel_type p = at(bmp, x, y);
				at(bmp, x, y).red = 255 - p.red;
				at(bmp, x, y).green = 255 - p.green;
				at(bmp, x, y).blue = 255 - p.blue;
			}
		}
	}
	else
	{
		std::cout << "Unable to invert colors. Please first initialize the file!\n";
	}
}
void graphics::to_gray(graphics::bitmap_type& bmp)
{
	if (bmp.m_p_data != nullptr)
	{
		// Set every pixel to gray by calculating the average of the subcolors.
		for (size_t x(0); x < bmp.m_info_header.width; x++)
		{
			for (size_t y(0); y < bmp.m_info_header.height; y++)
			{
				byte_type g = get_gray_value(at(bmp, x, y));
				pixel_type new_pixel = { g,g,g };
				at(bmp, x, y) = new_pixel;
			}
		}
	}
	else
	{
		std::cout << "Unable to create grayscale image. Please first initialize the file!\n";
	}
}


void graphics::create(graphics::bitmap_type& bmp, long_type const width, long_type const height, bool const random)
{
	// Before creating a new bitmap_type, we clear all old data.
	clear(bmp);

	// Calculates the scanline size. The width must be divideable by 4, so occasionally we have to round up.
	bmp.m_size_scan_line = (int)ceil(bmp.m_size_pixel * width * 0.25) * 4;

	// Set all values related to image dimensions.
	bmp.m_info_header.size = sizeof(info_header_type);
	bmp.m_info_header.width = width;
	bmp.m_info_header.height = height;
	bmp.m_info_header.size_image = bmp.m_size_scan_line * height;

	// Set all values related to data access.
	bmp.m_file_header.offset = sizeof(file_header_type) + sizeof(info_header_type);
	bmp.m_file_header.size = bmp.m_file_header.offset + bmp.m_info_header.size_image;

	// Dynamically allocate the needed space.
	bmp.m_p_data = new byte_type[bmp.m_info_header.size_image];

	// Either create a white or randomly colored picture.
	if (random)
	{
		for (uint32_type i(0); i < bmp.m_info_header.size_image; i++)
		{
			bmp.m_p_data[i] = pfc::get_random_uniform(0x00, 0xff);
		}
	}
	else
	{
		for (uint32_type i(0); i < bmp.m_info_header.size_image; i++)
		{
			bmp.m_p_data[i] = 255;
		}
	}
}
void graphics::get_sobel(graphics::bitmap_type const& bmp, size_t const x, size_t const y, int& sx, int& sy, std::vector<std::vector<int>> const& xmask, std::vector<std::vector<int>> const& ymask)
{
	// Multiply each value in the matrix with the corresponding grey pixel.
	if (bmp.m_p_data != nullptr)
	{
		for (size_t cx(0); cx < 3; cx++)
		{
				
			for (size_t cy(0); cy < 3; cy++)
			{
				pixel_type p = at(bmp, x + cx - 1, y + cy - 1);
				sx += get_gray_value(p) * xmask[cx][cy];
				sy += get_gray_value(p) * ymask[cx][cy] * -1;
			}
		}
		
	}
}
int graphics::get_gray_value(graphics::pixel_type const& pixel)
{
	return (pixel.blue + pixel.green + pixel.red) / 3;
}

size_t graphics::detect_objects(graphics::bitmap_type const& bmp, size_t const threshold, graphics::background_type const type)
{
	size_t counter(0);
	// Only start the function if the bitmap isnt null.
	if (bmp.m_p_data != nullptr)
	{
		// Copy the bitmap to avoid changing it and transform it to grayscale values.
		graphics::bitmap_type copy(bmp);
		graphics::to_gray(copy);

		//Iterate over all pixels and classify them as background and foreground(Objects)
		for (size_t x(0); x < copy.m_info_header.width; x++)
		{
			for (size_t y(0); y < copy.m_info_header.height; y++)
			{
				graphics::pixel_type pixel(at(bmp, x, y));

				if (pixel.red > threshold && type == background_type::BG_DARK || pixel.red < threshold && type == background_type::BG_LIGHT)
				{
					at(copy, x, y) = { 0,0,0 };
				}
				else
				{
					at(copy, x, y) = { 255,255,255 };
				}
				
			}
		}

		// Search for objects and color them.
		for (size_t x(0); x < copy.m_info_header.width; x++)
		{
			for (size_t y(0); y < copy.m_info_header.height; y++)
			{
				pixel_type p(graphics::at(copy, x, y));
				// If theres a black pixel, generate a random color, start the floodfill algorithm and increase object count.
				if (p.red == 0)
				{
						pixel_type color({ (graphics::byte_type)(rand() % 254 + 1), (graphics::byte_type)(rand() % 254 + 1) , (graphics::byte_type)(rand() % 254 + 1) });
						floodfill(copy, threshold, x, y, color);
						counter++;
				}
			}
		}
		
		// Write out the file.
		write_to(copy, "out.bmp");
	}
	// If its null theres nothing we can do.
	else
	{
		std::cout << "Unable to detect objects!\n";
	}

	return counter;
}

void graphics::floodfill(graphics::bitmap_type& bmp, size_t const threshold,  int const x, int const y, graphics::pixel_type const& color)
{
	// Call the worker function with depth 0.
	floodfill_worker(bmp, threshold, x, y, color, 0);
}
void graphics::floodfill_worker(graphics::bitmap_type& bmp, size_t const threshold, int const x, int const y, graphics::pixel_type const& color, size_t const depth)
{
	// stop at depth 4150 to avoid stackoverflow.
		if (depth < 4150)
		{
			// Check if pixel is in bounds.
			if (x >= 0 && x < bmp.m_info_header.width && y >= 0 && y < bmp.m_info_header.height)
			{
				// Get the pixel and check if its part of an object (black)
				graphics::pixel_type pixel(at(bmp, x, y));
				if (pixel.red == 0)
				{
					// Change its color and recursively check all other pixels around it.
					at(bmp, x, y) = color;
					
					floodfill_worker(bmp, threshold, x - 1, y, color, depth + 1);
					floodfill_worker(bmp, threshold, x + 1, y, color, depth + 1);
					floodfill_worker(bmp, threshold, x, y - 1, color, depth + 1);
					floodfill_worker(bmp, threshold, x, y + 1, color, depth + 1);
				}
			}
		}
}
