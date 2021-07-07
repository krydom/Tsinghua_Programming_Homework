#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

template <class T>
class MyVector
{
public:
	typedef T* iterator;

private:
	iterator _begin = nullptr; // ��ʼλ��
	iterator _end = nullptr; // Ԫ�ص�ĩλ��
	iterator _endOfStorage = nullptr; // ���䵽�����Ŀռ�

public:
	MyVector() {} // Ĭ�Ϲ���
	MyVector(size_t n, const T& value = T()) { resize(n, value); } // ����2
	MyVector(MyVector<int>& vec) // ��������
	{
		_begin = _end = _endOfStorage = nullptr;
		reserve(vec.capacity());
		iterator it1 = begin();
		iterator it2 = vec.begin();
		while (it2 != vec.end()) *it1++ = *it2++;
		_end = _begin + vec.size();
		_endOfStorage = _begin + vec.capacity();
	}
	MyVector(iterator Begin, iterator End) // ����4
	{
		_begin = _end = _endOfStorage = nullptr;
		reserve(End - Begin);
		_end = _begin + (End - Begin);
		_endOfStorage = _begin + (End - Begin);
		iterator it = begin();
		while (Begin != End) *it++ = *Begin++;
	}

	iterator begin() { return _begin; }
	iterator end() { return _end; }
	size_t capacity() const { return _endOfStorage - _begin; } // ����
	size_t size() const { return _end - _begin;} // ����
	bool empty() { return _begin == _end; } // �Ƿ�Ϊ��
	
	T& at(size_t pos) // �ó�Ա��������ĳһԪ�ص�����
	{
		assert(pos < size());
		return _begin[pos];
	}

	T& operator [](size_t pos) // ������ķ�ʽ����ĳһԪ�ص�����
	{
		assert(pos < size());
		return _begin[pos];
	}

	T& front() // ��һ��Ԫ�ص�����
	{
		assert(_end > _begin);
		return at(0);
	}

	T& back() // ���һ��Ԫ�ص�����
	{
		assert(_end > _begin);
		return at(size() - 1);
	}
	
	void reserve(size_t n) // �޸�����
	{
		if (n > capacity())
		{
			size_t Size = size();
			T* cap = new T[n];
			if (_begin) for (size_t i = 0; i < Size; ++i) cap[i] = _begin[i];
			_begin = cap;
			_end = _begin + Size, _endOfStorage = _begin + n;
		}
	}

	void resize(size_t n, const T& value = T())  // �޸ĳ���
	{
		if (n <= size())_end = _begin + n;
		else
		{
			if (n > capacity()) reserve(n);
			while (_end - _begin != n)
			{
				*_end = value;
				++_end;
			}
		}
	}

	void clear() { _end = _begin; } // �������

	~MyVector() //����
	{
		if (_begin)
		{
			delete[] _begin;
			_begin = _end = _endOfStorage = nullptr;
		}
	}

	MyVector<T>& operator=(const MyVector<T>& vec) // =
	{
		if (this != &vec)
		{
			delete[] _begin;
			_begin = new T[sizeof(T) * vec.size()];
			memcpy(_begin, vec._begin, sizeof(T) * vec.size());
			_end = _begin + vec.size();
			_endOfStorage = _begin + vec.capacity();
		}
		return *this;
	}

	void swap(MyVector<T>& vec) // ����
	{
		std::swap(_begin, vec._begin);
		std::swap(_end, vec._end);
		std::swap(_endOfStorage, vec._endOfStorage);
	}

	void insert(iterator pos, const T& x) // ��ĳһλ�ò���
	{
		size_t wh = pos - _begin; // ����λ��
		if (_end == _endOfStorage) // ��������������
		{
			reserve(capacity() * 2 + 2); 
			pos = _begin + wh;
		}
		for (iterator end = _end; end > pos; --end) *end = *(end - 1);
		*pos = x;
		++_end;
	}

	void push_back(const T& x) { insert(end(), x);} // ����������

	void pop_back() // ����������Ԫ��
	{
		assert(size() > 0); // ���size = 0 �����
		--_end;
	}

	iterator erase(iterator pos) // ɾ��ĳһԪ��
	{
		iterator begin = pos;
		for(; pos != _end; ++pos) *pos = *(pos + 1);
		--_end;
		return begin;
	}
};
