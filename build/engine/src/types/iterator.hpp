#pragma once 

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class YAPI Iterator {
		T* ptr;
		
		public:
			explicit Iterator();
			explicit Iterator(T* p);
			
			~Iterator();
			
			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;
			
			T operator*() const;
			
			Iterator& operator++();
			Iterator operator++(int);
			
			Iterator& operator--();
			Iterator operator--(int);
	};
} // namespace Yazh::Types

#include"iterator.tpp"