#include <iostream>
#include <assert.h>
#include <string>
#include <cstring>
using namespace std;
const int default_capacity = 4;
template<class T>
class vector{
public:
	using size_type = size_t;
	using value_type = T;
	using reference = T&;
	using iterator = value_type*;
	using pointer = T*;
	using const_iterator = const value_type;

	vector()
	{
		this -> _start = new T[default_capacity];
		this -> _finish = this -> _start + 1;
		this -> capa = default_capacity;
		this -> _size = 0;
		this -> _endofstorage = this -> _start + default_capacity;
	}	

	vector(size_type _capacity){
		this -> _start = new T [_capacity];
		this -> _finish = _start + 1;
		this -> capa = _capacity;
		this -> _size = 0;
		this -> _endofstorage = this -> _start + _capacity;
	}

	//copy
	vector(vector &copy)
	{
		this -> _start = new value_type[copy.capacity()];
		this -> _finish = _start + copy.size();
		this -> capa = copy.capacity();
		this -> _size = copy.size();
		this -> _endofstorage = this -> _start + capa;
		for(size_type i = 0;i < _size;i++)
		{
			_start[i] = copy._start[i];
		}
	}

	~vector()
	{
		delete [] _start;
	}
	void push_back(const value_type &x)
	{
		check_capacity();
		*_finish = x;
		++_finish;
		_size++;
	}

	void pop_back()
	{
		if(!empty())
		{
			--_finish;
			_size--;
		}
	}

	void insert(iterator pos , const value_type &x)
	{
		assert(pos <= _finish+1);

		if(pos == _finish+1)
		{
			push_back(x);
		}
		check_capacity();
		iterator cur = _finish;
		iterator prev = _finish-1;
		while(cur != pos)
		{
			*cur = *prev;
			cur--;
			prev--;
		}
		*cur = x;
		_finish++;
		_size++;
	}

	iterator erase(size_type pos)
	{
		assert(pos < _size);

		if(_start + pos == _finish-1)
		{
			pop_back();
			return _finish;
		}

		else
		{
			iterator cur = _start;
			while(cur != _start + pos)
			{
				cur++;
			}
			iterator next = cur+1;
			iterator tmp = next;
			while(next != _finish)
			{
				*cur = *next;
				cur++;
				next++;
			}
			_finish--;
			_size--;
			return tmp;
		}
	}


	iterator begin()
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	iterator rbegin()
	{
		return _finish-1;
	}

	iterator rend()
	{
		return _start-1;
	}

	const_iterator cbegin() const
	{
		return _start;
	}

	const_iterator cend() const
	{
		return _finish;
	}

	const_iterator crbegin() const 
	{
		return _finish-1;
	}

	const_iterator crend() const
	{
		return _start-1;
	}

	size_type size()
	{
		return _size;
	}

	size_type capacity()
	{
		return capa;
	}

	reference front()
	{
		return *_start;
	}

	reference back()
	{
		return *(_finish-1);
	}

	void clear()
	{ 
		while(size()) 
			pop_back(); 
	}

	pointer data()
	{
		return _start;
	}

	bool empty()
	{
		return !size();
	}

	reference at(size_type pos)
	{
		assert(-1 < pos);
		assert(pos < size());
		return _start[pos];
	}

	reference operator [](size_type index)
	{
		assert(-1 < index);
		assert(index < size());
		return _start[index];
	}

	void resize(size_type new_size, const T & x)
	{
			pointer new_space;
			if(new_size != capa)
			{
				new_space = new value_type[new_size];
				memmove(new_space, _start, sizeof(T) * new_size);
			} 
			delete _start;
			_start = new_space;
			pointer tmp = _start + (_size < new_size ? _size : new_size);
			_size = new_size;
			capa = new_size;
			_endofstorage = _finish = _start + _size;
			while(tmp != _finish)
			{
				*tmp = x;
				++tmp;
			}
		}

	void swap(vector& other)
	{
		iterator sttmp = other._start;other._start = this -> _start;this -> _start = sttmp;
		iterator fitmp = other._finish;other._finish = this -> _finish;this -> _finish = fitmp;
		iterator stotmp = other._endofstorage;other._endofstorage = this -> _endofstorage;this -> _endofstorage = stotmp;
		size_type sizetmp = other._size;other._size = this -> _size;this -> _size = sizetmp;
		size_type captmp = other.capa;other.capa = this -> capa;this -> capa = captmp;
	}

protected:
	void check_capacity()
	{
		if(_finish == _endofstorage)
		{
			size_type oldstorage = _endofstorage - _start;
			size_type storage = oldstorage*2;

			value_type* tmp = new value_type[storage];
			for(size_type i = 0;i < oldstorage;i++)
			{
				tmp[i] = _start[i];
			}
			delete [] _start;
			_start = tmp;
			_finish = tmp + oldstorage;
			_endofstorage = tmp + storage;
			capa = storage;
		}
	}

	iterator _start;
	iterator _finish;
	iterator _endofstorage;
	size_type _size;
	size_type capa;
};

