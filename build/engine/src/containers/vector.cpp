#include"vector.hpp"

namespace Yazh::Containers {
	template<class T>
	Vector<T>::Vector()
			: CAPACITY(DEFAULT_CAPACITY),
			  DATA(new T[DEFAULT_CAPACITY]),
			  SIZE(0) {
	}
	template<class T>
	Vector<T>::Vector(T* data)
			: SIZE(sizeof(data) / sizeof(T)) {
		CAPACITY = DEFAULT_CAPACITY;
		while (CAPACITY < SIZE) CAPACITY *= RESIZE_FACTOR;
		DATA = new T[CAPACITY];
		for (auto i = 0; i < SIZE; i++) DATA[i] = data[i];
	}
	template<class T>
	Vector<T>::Vector(Vector<T>& other);
			: DATA(other.data()),
			  SIZE(other.size()),
			  CAPACITY(other.capacity()) {
	}
	template<class T>
	Vector<T>::Vector(u64 capacity)
			: DATA(new T[capacity]),
			  SIZE(0),
			  CAPACITY(capacity) {
	}
	template<class T>
	Vector<T>::~Vector() { delete[] data; }
	
	template<class T>
	T& Vector<T>::operator[](u64 pos) {
		return &DATA[pos];
	}
	template<class T>
	T& Vector<T>::at(u64 pos) {
		if (pos < SIZE) 
			return &DATA[pos];
		else 
			YERROR("[ Yazh::Containers::Vector ]: Argument `pos` (Type = `u64`) passed to `Yazh::Containers::Vector::at()` is out of bounds!");
	}
	
	template<class T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* temp = DATA;
		DATA = new T[CAPACITY];
		for (auto i = 0; i < SIZE; i++) DATA[i] = temp[i];
	}

	template<class T>
	u64 Vector<T>::push(T val, u64 pos = SIZE) {
		if(SIZE == CAPACITY) *this.resize();
		for (auto i = SIZE; i > pos; i--) 
			DATA[i+1] = DATA[i];
		DATA[pos] = val;
		SIZE += 1;
		return SIZE;
	}
	template<class T>
	T Vector<T>::pop(u64 pos = SIZE - 1) {
		T val = DATA[pos];
		for (auto i = pos; i < SIZE-1; i++)
			DATA[i] = DATA[i+1];
		return val;
	}
	
	template<class T>
	void Vector<T>::clear() { SIZE = 0; }
	template<class T>
	u64 Vector<T>::size() { return SIZE; }
	template<class T>
	u64 Vector<T>::capacity() { return CAPACITY; }
	template<class T>
	T* Vector<T>::data() { return DATA; }
	
	template<class T>
	Yazh::Types::Iterator<T> Vector<T>::begin() { return DATA; }
	template<class T>
	Yazh::Types::Iterator<T> Vector<T>::end() { return DATA + SIZE; }
} // namespace Yazh::Containers