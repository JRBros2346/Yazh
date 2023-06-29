#include"iterator.hpp"

namespace Yazh::Types {
	template<class T>
	explicit Iterator<T>::Iterator() : ptr(nullptr) {
	}
	template<class T>
	explicit Iterator<T>::Iterator(T* p) : ptr(p) {
	}
	
	template<class T>
	Iterator<T>::~Iterator() { delete [] ptr; }
	
	template<class T>
	bool Iterator<T>::operator==(const Iterator<T>& other) const {
		return (*this == other);
	}
	template<class T>
	bool Iterator<T>::operator!=(const Iterator<T>& other) const {
		return !(*this == other);
	}
	
	template<class T>
	T Iterator<T>::operator*() const {
		return *ptr;
	}
	
	template<class T>
	Iterator<T>& Iterator<T>::operator++() {
		++ptr;
		return *this;
	}
	template<class T>
	Iterator<T> Iterator<T>::operator++(int) {
		Iterator temp(ptr);
		++ptr;
		return temp;
	}
	
	template<class T>
	Iterator<T>& Iterator<T>::operator--() {
		--ptr;
		return *this;
	}
	template<class T>
	Iterator<T> Iterator<T>::operator--(int) {
		Iterator temp(ptr);
		--ptr;
		return temp;
	}
} // namespace Yazh::Types