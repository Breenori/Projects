#include<iostream>
#include<array>
using namespace std;

int* get_pointer();
int* get_array(size_t n);
void print_n_carray(int* a, size_t n, std::ostream& o);

void iterate(int* a, int* b, std::ostream &o)
{
	if (a == nullptr || b == nullptr)
		return;

	int* p(a);
	while (p < b)
	{
		if (p > a)
		{
			o << ", ";
		}
		*p = p - a;
		p++;
	}
}
void read_or_write(int const* p, size_t j)
{
	++p;
	p[j] = 9;
}

void main()
{
	int i(17);
	int* p(&i);

	std::cout << p << ": " << *p << endl;
	int* q = p;
	int j(i);
	int* r(&j);
	*r = *q;

	p = new int(1);	// wird nicht automatisch vom GC freigegeben. Erst bei Programmende oder bei delete
	delete p;

	p = nullptr;
	p = new int(17);

	size_t n;
	cin >> n;


	q = get_array(n);
	iterate(q, q + n, cout);
	print_n_carray(q, n, cout);
	
}


// shouldnt be used

int* get_array(size_t n)
{
	int* p = new int[n];
	return p;
}

void print_n_carray(int* a, size_t n, std::ostream &o)
{
	for (int i(0); i < n; i++)
	{
		if (i > 0)
		{
			o << ",";
		}
		cout << *(a+i);
	}
}

int* get_pointer()
{
	int x(37);
	int* p(&x);
	return p;
}