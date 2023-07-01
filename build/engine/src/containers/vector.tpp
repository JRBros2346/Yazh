
#include"core/logger.hpp"

namespace Yazh::Containers {
	template<typename T>
	Vector<T>::Vector()
		: CAPACITY(DEFAULT_CAPACITY),
		  DATA(new T[DEFAULT_CAPACITY]),
		  SIZE(0) {
	}
	template<typename T>
	Vector<T>::Vector(u64 capacity)
		: CAPACITY(capacity),
		  DATA(new T[capacity]),
		  SIZE(0) {
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
	T Vector<T>::pop(u64 pos) {
		T val = DATA[pos];
		for (u64 i = pos; i < SIZE; i++) DATA[i] = DATA[i+1];
		SIZE--;
		return val;
	}
	
	template<typename T>
	void Vector<T>::clear() { SIZE = 0; }
	template<typename T>
	u64 Vector<T>::size() const { return SIZE; }
	template<typename T>
	u64 Vector<T>::capacity() const { return CAPACITY; }
	template<typename T>
	T* Vector<T>::data() const { return DATA; }
} // namespace Yazh::Containers