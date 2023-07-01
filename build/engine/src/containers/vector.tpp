
#include"core/logger.hpp"

namespace Yazh::Containers {
	template<typename T>
	Vector<T>::Vector()
		: CAPACITY(DEFAULT_CAPACITY),
		  DATA(new T[DEFAULT_CAPACITY]),
		  SIZE(0) {
	}
	template<typename T>
	Vector<T>::Vector(Vector<T>& other)
		: DATA(other.data()),
		  SIZE(other.size()),
		  CAPACITY(other.capacity()) {
	}
	template<typename T>
	Vector<T>::Vector(u64 capacity)
		: DATA(new T[capacity]),
		  SIZE(0),
		  CAPACITY(capacity) {
	}
	template<typename T>
	Vector<T>::~Vector() { delete[] DATA; }
	
	template<typename T>
	T& Vector<T>::operator[](u64 pos) { return DATA[pos]; }
	
	template<typename T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* temp = DATA;
		DATA = new T[CAPACITY];
		DATA = temp;
		delete [] temp;
	}

	template<typename T>
	u64 Vector<T>::push(T val) {
		if(SIZE == CAPACITY) this->resize();
		DATA[SIZE] = val;
		return SIZE++;
	}

	template<typename T>
	T Vector<T>::pop() { return DATA[--SIZE]; }
	
	template<typename T>
	void Vector<T>::clear() { SIZE = 0; }
	template<typename T>
	u64 Vector<T>::size() const { return SIZE; }
	template<typename T>
	u64 Vector<T>::capacity() const { return CAPACITY; }
	template<typename T>
	T* Vector<T>::data() const { return DATA; }
} // namespace Yazh::Containers