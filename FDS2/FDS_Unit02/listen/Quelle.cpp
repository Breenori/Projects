#include<iostream>
#include<vector>
#include<string>
#include<cassert>
using namespace std;

typedef vector<string const*> vector_type;

int str_cmp(string const* s1, string const* s2)
{

}

int index_of_min(vector_type* const v, int begin, int const end)
{
	assert(v != nullptr);
	assert(end > begin);
	assert(begin >= 0);
	assert(end <= v->size());
	vector_type & temp_vector = *v;

	int min(begin);

	++begin;
	while (begin < end)
	{
		if (*(temp_vector[begin]) < *temp_vector[min])
		{
			min = begin;
		}
		++begin;
	}
	return min;
}

void sort_indirect(vector_type * const v, int begin, int const end)
{
	assert(v != nullptr);
	assert(end > begin);
	assert(begin >= 0);
	assert(end <= v->size());

	while (begin < end)
	{
		int minIndex = index_of_min(v, begin, end);
		string const* tempPointer = (*v)[minIndex];
		(*v)[minIndex] = (*v)[begin];
		(*v)[begin] = tempPointer;

		begin++;
	}
}

void main() 
{
	vector_type my_vector;
	string s1("HerberT");
	string s2("Zenzi");
	string s3("Anna");
	string s4("Manfred");
	string s5("Sepp");

	my_vector.push_back(&s1);
	my_vector.push_back(&s2);
	my_vector.push_back(&s3);
	my_vector.push_back(&s4);
	my_vector.push_back(&s5);
}