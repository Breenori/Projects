#include<iostream>
using namespace std;

void take_carray(int const* a, size_t n1, int b[], size_t n2)
{
	for (size_t i(0); i < n1; ++i)
	{
		std::cout << a[i];
	}
	for (size_t i(0); i < n2; ++i)
	{
		std::cout << *b << " ";
		b++;
	}
}

void print_cstring(char const* d)
{
	while (d != nullptr && *d != '\0')
	{
		std::cout << *d << " ";
		++d;
	}
}

size_t cstr_len(char const source[])
{
	size_t len(0);
	while (source != nullptr && *source != 0)
	{
		++source;
		len++;
	}
	return len;
}

void cstr_copy_1(char dest[], char const src[])
{
	for (size_t i(0); i <= cstr_len(src); i++)
	{
		dest[i] = src[i];
	}
}

void cstr_copy_2(char *dest, char const *source)
{
	while (*source != 0)
	{
		*dest++ = *source++;
	}
}

char* cstr_dup(char const* p)
{
	if (p != nullptr)
	{
		char* dst = new char[cstr_len(p)];
		cstr_copy_2(dst, p);
		return dst;
	}
	else
	{
		return nullptr;
	}
}



void main()
{
	cout << "hello, world!";
	int a[10];
	a[3] = 9;
	take_carray(a, 10, a, 10);

	char const* c("hello!");
	cout << c << endl;

	char d[] = { 'h', 'e', '\0' };
	cout << std::endl;
	print_cstring(d);

	char dst[256];
	cstr_copy_1(dst, c);
	cout << endl << dst << c;

	char* dupl = cstr_dup(c);
	std::cout << dupl;
	delete[] dupl;
	dupl = nullptr;
}