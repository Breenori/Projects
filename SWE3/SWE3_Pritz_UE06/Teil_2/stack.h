#ifndef STACK_H
#define STACK_H
#include<vector>
using std::vector;

template<typename T>
class Stack
{
	typedef T data_type;
private:
	size_t capacity;
	vector<data_type> buffer;

	bool empty()
	{
		return buffer.size() < capacity;
	}
	bool full()
	{
		return buffer.size() == capacity;
	}
public:
	Stack(size_t const capacity)
	{
		this.capacity = capacity;
		this.buffer = vector<data_type>();
	}
	//~Stack();
	
	bool push(data_type const& value)
	{
		if(full())
		{
			return false;
		}

		buffer.push_back(value);
		return true;
	}
	bool pop(data_type& value)
	{
		if(empty())
		{
			return false;
		}

		data_type tmp = buffer[buffer.size() - 1];
		buffer.erase(buffer.end() - 1);
		return tmp;
	}
	bool top(data_type& value)
	{
		if (empty())
		{
			return false;
		}

		data_type tmp = buffer[buffer.size() - 1];
		return tmp;
	}
};

#endif