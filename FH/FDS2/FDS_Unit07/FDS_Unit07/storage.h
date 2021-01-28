#if !defined STORAGE_H
#define STORAGE_H

class storage_t {
private:
	int* data;
	size_t size;

public:
	storage_t(size_t size);
	~storage_t();
	int& at(size_t pos);
	void clear();
};

#endif