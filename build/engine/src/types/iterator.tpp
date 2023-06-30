
namespace Yazh::Types {
	template<typename T>
	Iterator<T>::Iterator() : ptr(nullptr) {
	}
	template<typename T>
	Iterator<T>::Iterator(T* p) : ptr(p) {
	}
	
	template<typename T>
	Iterator<T>::~Iterator() { delete [] ptr; }
	
	template<typename T>
	bool Iterator<T>::operator==(const Iterator<T>& other) const {
		return (*this == other);
	}
	template<typename T>
	bool Iterator<T>::operator!=(const Iterator<T>& other) const {
		return !(*this == other);
	}
	
	template<typename T>
	T Iterator<T>::operator*() const {
		return *ptr;
	}
	
	template<typename T>
	Iterator<T>& Iterator<T>::operator++() {
		++ptr;
		return *this;
	}
	template<typename T>
	Iterator<T> Iterator<T>::operator++(int) {
		Iterator temp(ptr);
		++ptr;
		return temp;
	}
	
	template<typename T>
	Iterator<T>& Iterator<T>::operator--() {
		--ptr;
		return *this;
	}
	template<typename T>
	Iterator<T> Iterator<T>::operator--(int) {
		Iterator temp(ptr);
		--ptr;
		return temp;
	}
} // namespace Yazh::Types