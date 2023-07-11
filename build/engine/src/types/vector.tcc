#include"core/ymemory.hpp"
#include"core/asserts.hpp"

namespace Yazh::Types {
	template<typename T>
	Vector<T>::Vector()
			: SIZE(0),
			  CAPACITY(DEFAULT_CAPACITY) {
		DATA = (T*)Yazh::Memory::allocate(DEFAULT_CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
	}
	template<typename T>
	Vector<T>::Vector(ysize capacity)
			: SIZE(0),
			  CAPACITY(capacity) {
		DATA = (T*)Yazh::Memory::allocate(capacity * sizeof(T), Yazh::Memory::Tag::Vector);
	}
	template<typename T>
	Vector<T>::Vector(const Vector<T>& other)
			: SIZE(other.SIZE),
			  CAPACITY(other.CAPACITY) {
		DATA = (T*)Yazh::Memory::allocate(other.CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);

		for (ysize i = 0; i < other.SIZE; ++i)
			DATA[i] = other.DATA[i];
	}
	template<typename T>
	Vector<T>::Vector(Vector<T>&& other)
			: SIZE(other.SIZE),
			  CAPACITY(other.CAPACITY) {
		DATA = other.DATA;

		other.SIZE = 0;
		other.CAPACITY = 0;
		other.DATA = nullptr;
	}
	// template<typename T>
	// template<typename... Values>
	// Vector<T>::Vector(Values&&... elements) {

	// }
	template<typename T>
	Vector<T>::~Vector() {
		clear();
		Yazh::Memory::free(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
	}

	template<typename T>
	T& Vector<T>::operator[](ysize pos) {
		return DATA[pos];
	}
	template<typename T>
	const T& Vector<T>::operator[](ysize pos) const {
		return DATA[pos];
	}

	template<typename T>
	void Vector<T>::resize() {
		CAPACITY *= RESIZE_FACTOR;
		T* block = (T*)Yazh::Memory::allocate(CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		for (ysize i = 0; i < SIZE; ++i)
			block[i] = std::move(DATA[i]);
		// clear();
		Yazh::Memory::free(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		DATA = block;
		block = nullptr;
	}

	template<typename T>
	void Vector<T>::push_back(const T& val) {
		if (SIZE == CAPACITY)
			resize();
		DATA[SIZE++] = val;
	}
	template<typename T>
	void Vector<T>::push_at(ysize pos, const T& val) {
		if (SIZE == CAPACITY)
			resize();
		for (auto i = SIZE++; i > pos; --i)
			DATA[i] = std::move(DATA[i-1]);
		DATA[pos] = val;
	}
	template<typename T>
	void Vector<T>::push_back(T&& val) {
		if (SIZE == CAPACITY)
			resize();
		DATA[SIZE++] = std::move(val);
	}
	template<typename T>
	void Vector<T>::push_at(ysize pos, T&& val) {
		if (SIZE == CAPACITY)
			resize();
		for (auto i = SIZE++; i > pos; --i)
			DATA[i] = std::move(DATA[i-1]);
		DATA[pos] = std::move(val);
	}

	template<typename T>
	template<typename... Args>
	T& Vector<T>::emplace_back(Args&&... args) {
		if (SIZE == CAPACITY)
			resize();
		new(&DATA[SIZE]) T(std::forward<Args>(args)...);
		return DATA[SIZE++];
	}
	template<typename T>
	template<typename... Args>
	T& Vector<T>::emplace_at(ysize pos, Args&&... args) {
		if (SIZE == CAPACITY)
			resize();
		for (auto i = SIZE++; i > pos; --i)
			DATA[i] = std::move(DATA[i-1]);
		new(&DATA[pos]) T(std::forward<Args>(args)...);
		return DATA[pos];
	}

	template<typename T>
	T Vector<T>::pop_back() {
		T val = std::move(DATA[--SIZE]);
		DATA[SIZE].~T();
		return val;
	}
	template<typename T>
	T Vector<T>::pop_at(ysize pos) {
		T val = std::move(DATA[pos]);
		DATA[pos].~T();
		for (auto i = pos; i < SIZE; ++i)
			DATA[i] = std::move(DATA[i+1]);
		--SIZE;
		return val;
	}

	template<typename T>
	void Vector<T>::clear() {
		for (ysize i = 0; i < SIZE; ++i)
			DATA[i].~T();
		SIZE = 0;
	}
	template<typename T>
	void Vector<T>::shrink() {
		CAPACITY = (SIZE == 0) ? 1 : SIZE;
		T* block = (T*)Yazh::Memory::allocate(CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		for (ysize i = 0; i < SIZE; ++i)
			block[i] = std::move(DATA[i]);
		Yazh::Memory::free(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		DATA = block;
		block = nullptr;
	}

	template<typename T>
	T& Vector<T>::operator=(const Vector<T>& other) {
		Yazh::Memory::free(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		SIZE = other.SIZE;
		CAPACITY = other.CAPACITY;
		DATA = (T*)Yazh::Memory::allocate(CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		for (ysize i = 0; i < SIZE; i++)
			DATA[i] = other.DATA[i];
		return *this;
	}
	template<typename T>
	T& Vector<T>::operator=(Vector<T>&& other) {
		Yazh::Memory::free(DATA, CAPACITY * sizeof(T), Yazh::Memory::Tag::Vector);
		SIZE = other.SIZE;
		CAPACITY = other.CAPACITY;
		DATA = other.DATA;

		other.SIZE = 0;
		other.CAPACITY = 0;
		other.DATA = nullptr;
		return *this;
	}

	template<typename T>
	ysize Vector<T>::size() const { return SIZE; }
	template<typename T>
	ysize Vector<T>::capacity() const { return CAPACITY; }
	template<typename T>
	T* Vector<T>::data() const { return DATA; }
} // namespace Yazh::Types
