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
	iterator _begin = nullptr; // 起始位置
	iterator _end = nullptr; // 元素的末位置
	iterator _endOfStorage = nullptr; // 分配到的最后的空间

public:
	MyVector() {} // 默认构造
	MyVector(size_t n, const T& value = T()) { resize(n, value); } // 构造2
	MyVector(MyVector<int>& vec) // 拷贝构造
	{
		_begin = _end = _endOfStorage = nullptr;
		reserve(vec.capacity());
		iterator it1 = begin();
		iterator it2 = vec.begin();
		while (it2 != vec.end()) *it1++ = *it2++;
		_end = _begin + vec.size();
		_endOfStorage = _begin + vec.capacity();
	}
	MyVector(iterator Begin, iterator End) // 构造4
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
	size_t capacity() const { return _endOfStorage - _begin; } // 容量
	size_t size() const { return _end - _begin;} // 长度
	bool empty() { return _begin == _end; } // 是否为空
	
	T& at(size_t pos) // 用成员函数访问某一元素的引用
	{
		assert(pos < size());
		return _begin[pos];
	}

	T& operator [](size_t pos) // 用数组的方式访问某一元素的引用
	{
		assert(pos < size());
		return _begin[pos];
	}

	T& front() // 第一个元素的引用
	{
		assert(_end > _begin);
		return at(0);
	}

	T& back() // 最后一个元素的引用
	{
		assert(_end > _begin);
		return at(size() - 1);
	}
	
	void reserve(size_t n) // 修改容量
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

	void resize(size_t n, const T& value = T())  // 修改长度
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

	void clear() { _end = _begin; } // 清空向量

	~MyVector() //析构
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

	void swap(MyVector<T>& vec) // 交换
	{
		std::swap(_begin, vec._begin);
		std::swap(_end, vec._end);
		std::swap(_endOfStorage, vec._endOfStorage);
	}

	void insert(iterator pos, const T& x) // 在某一位置插入
	{
		size_t wh = pos - _begin; // 保存位置
		if (_end == _endOfStorage) // 容量不够则扩容
		{
			reserve(capacity() * 2 + 2); 
			pos = _begin + wh;
		}
		for (iterator end = _end; end > pos; --end) *end = *(end - 1);
		*pos = x;
		++_end;
	}

	void push_back(const T& x) { insert(end(), x);} // 在最后面插入

	void pop_back() // 弹出最后面的元素
	{
		assert(size() > 0); // 如果size = 0 则错误
		--_end;
	}

	iterator erase(iterator pos) // 删除某一元素
	{
		iterator begin = pos;
		for(; pos != _end; ++pos) *pos = *(pos + 1);
		--_end;
		return begin;
	}
};
