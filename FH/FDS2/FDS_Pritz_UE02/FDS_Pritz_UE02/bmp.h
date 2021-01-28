#if !defined BMP_H
#define BMP_H
#include "bmp_structures.h"
#include<string>
#include<vector>

namespace graphics {
	struct bitmap_type {
		file_header_type m_file_header;
		info_header_type m_info_header;

		graphics::byte_type* m_p_data = nullptr;

		size_t m_size_scan_line;
		size_t m_size_pixel;
	};

	// Returns a reference to a new, 0 * 0 bitmap_type.
	graphics::bitmap_type& generate_bitmap();
	// Returns a reference to a new bitmap_type initialized with w * x pixels of color c.
	graphics::bitmap_type& generate_bitmap(std::size_t const w, std::size_t const h, graphics::pixel_type const c = graphics::white);
	// Returns a reference to a new bitmap_type initialized by reading from a file using given cstring.
	graphics::bitmap_type& generate_bitmap(char const* const p_name);
	// Returns a reference to a new bitmap_type initialized by reading from a file using given string.
	graphics::bitmap_type& generate_bitmap(std::string const& name);
	// Returns a reference to a new bitmap_type initialized by reading from a file using given inputstream.
	graphics::bitmap_type& generate_bitmap(std::istream& in);
	// Returns a reference to a new bitmap_type which is a copy from src.
	graphics::bitmap_type& generate_bitmap(bitmap_type const& src);

	// Resets a bitmap by removing data and setting it to default values.
	void clear(graphics::bitmap_type& bmp);
	// Sets the dimensions of a given bitmap. The pixels, even if previously present, are all colored in color c.
	void resize(graphics::bitmap_type& bmp, std::size_t const w, std::size_t const h, graphics::pixel_type const c = graphics::white);

	// Compares if two bitmap_types are equal.
	bool equals(graphics::bitmap_type const& lhs, graphics::bitmap_type const& rhs);
	// Swaps two bitmap_types
	void swap(graphics::bitmap_type& lhs, graphics::bitmap_type& rhs);
	// Returns a reference to a pixel at position x y in given bitmap.
	graphics::pixel_type& at(graphics::bitmap_type& bmp, size_t const x, size_t const y);
	// Returns a reference to a constant pixel at position x y in given bitmap.
	graphics::pixel_type const& at(graphics::bitmap_type const& bmp, size_t const x, size_t const y);
	// Returns the height of the bitmap image.
	std::size_t get_height(graphics::bitmap_type const& bmp);
	// Returns the width of the bitmap image.
	std::size_t get_width(graphics::bitmap_type const& bmp);
	// Returns the amount of pixels in the given bitmap.
	// NOTE: This does include pixels which are stored after the end of the scanline and might not be seen.
	std::size_t get_image_size(graphics::bitmap_type const& bmp);
	// Returns the actual amount of pixels that are visible upon opening the bitmap.
	std::size_t get_num_pixels(graphics::bitmap_type const& bmp);
	// Returns a pointer to a byte_type (8 bit unsigned int).
	// This pointer can be used to iterate over the image.
	// One entry corresponds to either the red, blue or green portion of the color.
	graphics::byte_type* get_image(graphics::bitmap_type& bmp);
	// Returns a pointer to a constant byte_type (8 bit unsigned int).
	// This pointer can be used to iterate over the image.
	// One entry corresponds to either the red, blue or green part of the color.
	graphics::byte_type const* get_image(graphics::bitmap_type const& bmp);
	// Returns a pointer to a pixel_type.
	// This pointer can be used to iterate over the image.
	// One entry corresponds to a pixel, which contains the 3 color parts.
	graphics::pixel_type* get_pixels(graphics::bitmap_type& bmp);
	// Returns a pointer to a constant pixel_type.
	// This pointer can be used to iterate over the image.
	// One entry corresponds to a pixel, which contains the 3 color parts.
	graphics::pixel_type const* get_pixels(graphics::bitmap_type const& bmp);

	// Reads a bitmap_type from a file using the given cstring and returns if it was successful.
	bool read_from(graphics::bitmap_type& bmp, char const* const file_name);
	// Reads a bitmap_type from a file using the given string and returns if it was successful.
	bool read_from(graphics::bitmap_type& bmp, std::string const& file_name);
	// Reads a bitmap_type from a file using the given inputfilestream and returns if it was successful.
	bool read_from(graphics::bitmap_type& bmp, std::istream& in);

	// Writes the given bitmap to a file using the given cstring and returns if it was successful.
	bool write_to(graphics::bitmap_type const& bmp, char const* const file_name);
	// Writes the given bitmap to a file using the given string and returns if it was successful.
	bool write_to(graphics::bitmap_type const& bmp, std::string const& file_name);
	// Writes the given bitmap to a file using the given outputstream and returns if it was successful.
	bool write_to(graphics::bitmap_type const& bmp, std::ostream& out);

	// Detect edges in the given bitmap_type.
	// WARNING: Overwrites the file.
	void detect_edges(graphics::bitmap_type& bmp);
	// Sets each pixel in the given bitmap_type to the specified color.
	void fill(graphics::bitmap_type& bmp, pixel_type const color = graphics::white);
	// Inverts each pixel in the given bitmap_type by setting its subcolors to 255 minus their value.
	void invert(graphics::bitmap_type& bmp);
	// Sets each pixel in the given bitmap_type to the corresponding gray value by setting its subcolors to the average of subcolor amounts.
	void to_gray(graphics::bitmap_type& bmp);

	// Initializes a bitmap_type struct using given parameters.
	// NOTE: Dear tutors, we programmed this function together with our professors, which is why this function might seem similiar to others work.
	// It just seemed covenient to reuse it, since it perfectly fits what is required in this exercise.
	void create(graphics::bitmap_type& bmp, graphics::long_type const width, graphics::long_type const height, bool const random = false);
	// Returns the x- and y-Sobel values for the given coordinates in the given bitmap.
	// NOTE: I didn't separate sobel values for x and y because it's way more efficient to calculate them at the same time (else, i'd need to iterate over the whole image TWICE).
	void get_sobel(graphics::bitmap_type const& bmp, size_t const x, size_t const y, int& sx, int& sy, std::vector<std::vector<int>> const& xmask, std::vector<std::vector<int>> const& ymask);
	// Returns the corresponding gray value for a pixel.
	int get_gray_value(graphics::pixel_type const& pixel);
}

#endif