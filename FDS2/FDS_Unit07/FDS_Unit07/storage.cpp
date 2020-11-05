#include "storage.h"

storage_t::storage_t(size_t size)
{
	this->size = size;
	this->data = new int[size];
}

void storage_t::clear()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	size = 0;
}

storage_t::~storage_t()
{
	this->clear();
}

int& storage_t::at(size_t pos)
{
	return this->data[pos % this->size];
}
