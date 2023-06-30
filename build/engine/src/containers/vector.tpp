
#include"core/logger.hpp"

namespace Yazh::Containers {
	template<typename T>
	Vector<T>::Vector()
			: CAPACITY(DEFAULT_CAPACITY),
			  DATA(new T[DEFAULT_CAPACITY]),
			  SIZE(0) {
	}
	template<typename T>
	Vector<T>::Vector(T* data)
			: SIZE(sizeof(data) / sizeof(T)) {
		CAPACITY = DEFAULT_CAPACITY;
		while (CAPACITY < SIZE) CAPACITY *= RESIZE_FACTOR;
		DATA = new T[CAPACITY];
		for (auto i = 0; i < SIZE; i++) DATA[i] = data[i];
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
	T& Vector<T>::operator[](u64 pos) {
		return DATA[pos];
	}
	template<typename T>
	T& Vector<T>::at(u64 pos) {
		if (pos < SIZE) 
			return &DATA[pos];
		else 
			YERROR("[ Yazh::Containers::Vector ]: Argument `pos` (Type = `u64`) passed to `Yazh::Containers::Vector::at()` is out of bounds!");
	}
	
	template<typename T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* temp = DATA;
		DATA = new T[CAPACITY];
		for (u64 i = 0; i < SIZE; i++) DATA[i] = temp[i];
	}

	template<typename T>
	u64 Vector<T>::push(T val, u64 pos) {
		if(SIZE == CAPACITY) this->resize();
		for (auto i = SIZE; i > pos; i--) 
			DATA[i+1] = DATA[i];
		DATA[pos] = val;
		return SIZE++;
	}
	template<typename T>
	u64 Vector<T>::push(T val) {
		if(SIZE == CAPACITY) this->resize();
		DATA[SIZE] = val;
		return SIZE++;
	}

	template<typename T>
	T Vector<T>::pop(u64 pos) {
		T val = DATA[pos];
		for (auto i = pos; i < SIZE-1; i++)
			DATA[i] = DATA[i+1];
		SIZE--;
		return val;
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
	
	template<typename T>
	Yazh::Types::Iterator<T> Vector<T>::begin() const { return Yazh::Types::Iterator<T>(DATA); }
	template<typename T>
	Yazh::Types::Iterator<T> Vector<T>::end() const { return Yazh::Types::Iterator<T>(DATA + SIZE); }
} // namespace Yazh::Containers