#include"core/ymemory.hpp"

namespace Yazh::Types {
	template<typename T>
	Vector<T>::Vector()
		: SIZE(0),
		  CAPACITY(DEFAULT_CAPACITY),
		  DATA((T*)Yazh::Memory::yallocate(DEFAULT_CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector)) {
	}
	template<typename T>
	Vector<T>::Vector(u64 capacity)
		: SIZE(0),
		  CAPACITY(capacity),
		  DATA((T*)Yazh::Memory::yallocate(capacity * sizeof(T), Yazh::Memory::Tag::Vector)) {
	}
	template<typename T>
	Vector<T>::~Vector() { Yazh::Memory::yfree(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector); }

	template<typename T>
	T& Vector<T>::operator[](u64 pos) { return DATA[pos]; }

	template<typename T>
	void Vector<T>::resize() {
		T* temp = DATA;
		Yazh::Memory::yfree(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		CAPACITY *= RESIZE_FACTOR;
		DATA = (T*)Yazh::Memory::yallocate(CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		// std::copy(temp, temp + SIZE, DATA);
		DATA = (T*)Yazh::Memory::ycopy(DATA, temp, SIZE * sizeof(T));
		delete [] temp;
	}

	template<typename T>
	void Vector<T>::push(T val) {
		if (SIZE == CAPACITY) this->resize(); 
		DATA[SIZE++] = val; 
	}
	template<typename T>
	void Vector<T>::push(T val, u64 pos) {
		if (SIZE == CAPACITY) this->resize();
		for (auto i = SIZE++; i > pos; i--) DATA[i] = DATA[i-1];
		DATA[pos] = val;
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
	u64 Vector<T>::size() { return SIZE; }
	template<typename T>
	u64 Vector<T>::capacity() { return CAPACITY; }
	template<typename T>
	T* Vector<T>::data() { return DATA; }
} // namespace Yazh::Containers
