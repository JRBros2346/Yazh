namespace Yazh::Containers {
	template<typename T>
	Vector<T>::Vector()
		: SIZE(0),
		  CAPACITY(DEFAULT_CAPACITY),
		  DATA(new T[DEFAULT_CAPACITY]) {
	}
	template<typename T>
	Vector<T>::Vector(u64 capacity)
		: SIZE(0),
		  CAPACITY(capacity),
		  DATA(new T[capacity]) {
	}
	template<typename T>
	Vector<T>::~Vector() { delete[] DATA; }

	template<typename T>
	T& Vector<T>::operator[](u64) { return DATA[u64]; }

	template<typename T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* temp = DATA;
		DATA = new T[CAPACITY];
		copy(temp, temp + SIZE, DATA);
		delete [] temp;
	}

	template<typename T>
	void Vector<T>::push(T val) { DATA[SIZE++] = val; }
	template<typename T>
	T Vector<T>::pop() { 
		T val = DATA[--SIZE];
		return val;
	}
	template<typename T>
	T Vector<T>::pop(u64) {
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
