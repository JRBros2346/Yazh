#include"core/ymemory.hpp"
#include"core/logger.hpp"

namespace Yazh::Types {
	template<typename T>
	inline Vector<T>::Vector()
			: m_size(0),
			  m_capacity(DEFAULT_CAPACITY) {
		m_data = (T*)Core::Memory::allocate(DEFAULT_CAPACITY * sizeof(T), Core::Memory::Tag::Vector);
	}
	template<typename T>
	inline Vector<T>::Vector(std::size_t capacity)
			: m_size(0),
			  m_capacity(capacity) {
		m_data = (T*)Core::Memory::allocate(capacity * sizeof(T), Core::Memory::Tag::Vector);
	}
	template<typename T>
	Vector<T>::Vector(const Vector<T>& other)
			: m_size(other.m_size),
			  m_capacity(other.m_capacity) {
		m_data = (T*)Core::Memory::allocate(other.m_capacity * sizeof(T), Core::Memory::Tag::Vector);

		for (std::size_t i = 0; i < other.m_size; ++i)
			m_data[i] = other.m_data[i];
	}
	template<typename T>
	inline Vector<T>::Vector(Vector<T>&& other)
			: m_size(std::move(other.m_size)),
			  m_capacity(std::move(other.m_capacity)) {
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}
	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> elements)
			: m_size(elements.size()),
			  m_capacity(elements.size()) {
		m_data = (T*)Core::Memory::allocate(elements.size() * sizeof(T), Core::Memory::Tag::Vector);
		std::size_t i = 0;
		for (const auto &e : elements)
			m_data[i++] = e;
	}
	template<typename T>
	inline Vector<T>::~Vector() {
		clear();
		Core::Memory::free(m_data, m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		m_size = 0;
		m_capacity = 0;
	}

	template<typename T>
	inline T& Vector<T>::operator[](std::size_t pos) {
		return m_data[pos];
	}
	template<typename T>
	inline const T& Vector<T>::operator[](std::size_t pos) const {
		return m_data[pos];
	}
	template<typename T>
	inline T& Vector<T>::at(std::size_t pos) {
		if (pos >= m_size)
			Core::Logger::Error("Index outside the bounds of this vector! Length: {}, index: {}", m_size, pos);
		return m_data[pos];
	}
	template<typename T>
	inline const T& Vector<T>::at(std::size_t pos) const {
		if (pos >= m_size)
			Core::Logger::Error("Index outside the bounds of this vector! Length: {}, index: {}", m_size, pos);
		return m_data[pos];
	}

	template<typename T>
	inline void Vector<T>::push_back(const T& val) {
		if (m_size == m_capacity)
			resize();
		m_data[m_size++] = val;
	}
	template<typename T>
	void Vector<T>::push_at(std::size_t pos, const T& val) {
		if (pos >= m_size)
			Core::Logger::Error("Index outside the bounds of this vector! Length: {}, index: {}", m_size, pos);
		else {
			if (m_size == m_capacity)
				resize();
			for (auto i = m_size++; i > pos; --i)
				m_data[i] = std::move(m_data[i-1]);
			m_data[pos] = val;
		}
	}
	template<typename T>
	inline void Vector<T>::push_back(T&& val) {
		if (m_size == m_capacity)
			resize();
		m_data[m_size++] = std::move(val);
	}
	template<typename T>
	void Vector<T>::push_at(std::size_t pos, T&& val) {
		if (pos >= m_size)
			Core::Logger::Error("Index outside the bounds of this vector! Length: {}, index: {}", m_size, pos);
		else {
			if (m_size == m_capacity)
				resize();
			for (auto i = m_size++; i > pos; --i)
				m_data[i] = std::move(m_data[i-1]);
			m_data[pos] = std::move(val);
		}
	}

	template<typename T>
	template<typename... Args>
	inline T& Vector<T>::emplace_back(Args&&... args) {
		if (m_size == m_capacity)
			resize();
		new(&m_data[m_size]) T(std::forward<Args>(args)...);
		return m_data[m_size++];
	}
	template<typename T>
	template<typename... Args>
	T& Vector<T>::emplace_at(std::size_t pos, Args&&... args) {
		if (pos >= m_size)
			Core::Logger::Error("Index outside the bounds of this vector! Length: {}, index: {}", m_size, pos);
		if (m_size == m_capacity)
			resize();
		for (auto i = m_size++; i > pos; --i)
			m_data[i] = std::move(m_data[i-1]);
		new(&m_data[pos]) T(std::forward<Args>(args)...);
		return m_data[pos];
	}

	template<typename T>
	inline T Vector<T>::pop_back() {
		T val = std::move(m_data[--m_size]);
		m_data[m_size].~T();
		return val;
	}
	template<typename T>
	T Vector<T>::pop_at(std::size_t pos) {
		if (pos >= m_size)
			Core::Logger::Error("Index outside the bounds of this vector! Length: {}, index: {}", m_size, pos);
		T val = std::move(m_data[pos]);
		m_data[pos].~T();
		for (auto i = pos; i < m_size; ++i)
			m_data[i] = std::move(m_data[i+1]);
		--m_size;
		return val;
	}

	template<typename T>
	void Vector<T>::clear() {
		for (std::size_t i = 0; i < m_size; ++i)
			m_data[i].~T();
		m_size = 0;
	}
	template<typename T>
	inline void Vector<T>::shrink() {
		m_capacity = (m_size == 0) ? 1 : m_size;
		T* block = (T*)Core::Memory::allocate(m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		for (std::size_t i = 0; i < m_size; ++i)
			block[i] = std::move(m_data[i]);
		Core::Memory::free(m_data, m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		m_data = block;
		block = nullptr;
	}
	template<typename T>
	inline void Vector<T>::resize() {
		m_capacity *= RESIZE_FACTOR;
		T* block = (T*)Core::Memory::allocate(m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		for (std::size_t i = 0; i < m_size; ++i)
			block[i] = std::move(m_data[i]);
		Core::Memory::free(m_data, m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		m_data = block;
		block = nullptr;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
		Core::Memory::free(m_data, m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = (T*)Core::Memory::allocate(m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		for (std::size_t i = 0; i < m_size; i++)
			m_data[i] = other.m_data[i];
		return *this;
	}
	template<typename T>
	inline Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
		Core::Memory::free(m_data, m_capacity * sizeof(T), Core::Memory::Tag::Vector);
		m_size = std::move(other.m_size);
		m_capacity = std::move(other.m_capacity);
		m_data = other.m_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
		return *this;
	}

	template<typename T>
	inline std::size_t Vector<T>::size() const { return m_size; }
	template<typename T>
	inline std::size_t Vector<T>::capacity() const { return m_capacity; }
	template<typename T>
	inline T* Vector<T>::data() const { return m_data; }

	template<typename T>
	inline Vector<T>::Iter::Iter() : ptr(nullptr) {
	}
	template<typename T>
	inline Vector<T>::Iter::Iter(T* p) : ptr(p) {
	}
	template<typename T>
	inline Vector<T>::Iter::Iter(const Iter& other) : ptr(other.ptr) {
	}
	template<typename T>
	inline Vector<T>::Iter::~Iter() {
	}

	template<typename T>
	inline T& Vector<T>::Iter::operator*() { return *ptr; }
	template<typename T>
	inline T* Vector<T>::Iter::operator->() { return ptr; }
	template<typename T>
	inline const T& Vector<T>::Iter::operator*() const { return *ptr; }
	template<typename T>
	inline const T* Vector<T>::Iter::operator->() const { return ptr; }

	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::Iter::operator+(std::ptrdiff_t offset) { return ptr + offset; }
	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::Iter::operator-(std::ptrdiff_t offset) { return ptr - offset; }

	template<typename T>
	inline typename Vector<T>::Iter& Vector<T>::Iter::operator=(const Iter& other) {
		ptr = other.ptr;
		return *this;
	}
	template<typename T>
	inline typename Vector<T>::Iter& Vector<T>::Iter::operator=(Iter&& other) {
		ptr = std::move(other.ptr);
		other.ptr = nullptr;
		return *this;
	}
	template<typename T>
	inline typename Vector<T>::Iter& Vector<T>::Iter::operator+=(std::ptrdiff_t offset) {
		ptr += offset;
		return *this;
	}
	template<typename T>
	inline typename Vector<T>::Iter& Vector<T>::Iter::operator-=(std::ptrdiff_t offset) {
		ptr -= offset;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::Iter& Vector<T>::Iter::operator++() {
		++ptr;
		return *this;
	}
	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::Iter::operator++(int) {
		auto tmp = *this;
		++ptr;
		return tmp;
	}
	template<typename T>
	inline typename Vector<T>::Iter& Vector<T>::Iter::operator--() {
		--ptr;
		return *this;
	}
	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::Iter::operator--(int) {
		auto tmp = *this;
		--ptr;
		return tmp;
	}

	template<typename T>
	inline bool Vector<T>::Iter::operator==(const Iter& other) { return ptr == other.ptr; }
	template<typename T>
	inline bool Vector<T>::Iter::operator!=(const Iter& other) { return ptr != other.ptr; }
	template<typename T>
	inline bool Vector<T>::Iter::operator>=(const Iter& other) { return ptr >= other.ptr; }
	template<typename T>
	inline bool Vector<T>::Iter::operator<=(const Iter& other) { return ptr <= other.ptr; }
	template<typename T>
	inline bool Vector<T>::Iter::operator>(const Iter& other) { return ptr > other.ptr; }
	template<typename T>
	inline bool Vector<T>::Iter::operator<(const Iter& other) { return ptr < other.ptr; }

	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::begin() { return m_data; }
	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::end() { return m_data + m_size; }
	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::rbegin() { return m_data + m_size - 1; }
	template<typename T>
	inline typename Vector<T>::Iter Vector<T>::rend() { return m_data - 1; }
	template<typename T>
	inline const typename Vector<T>::Iter Vector<T>::cbegin() const { return m_data; }
	template<typename T>
	inline const typename Vector<T>::Iter Vector<T>::cend() const { return m_data + m_size; }
	template<typename T>
	inline const typename Vector<T>::Iter Vector<T>::crbegin() const { return m_data + m_size - 1; }
	template<typename T>
	inline const typename Vector<T>::Iter Vector<T>::crend() const  { return m_data - 1; }
} // namespace Yazh::Types
