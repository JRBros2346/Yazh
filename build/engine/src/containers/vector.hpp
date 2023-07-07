#pragma once

#include"defines.hpp"

#include"types/iterator.hpp"

namespace Yazh::Containers {
	template<typename T>
	class YAPI Vector {
		const static u64 DEFAULT_CAPACITY = 1;
		const static u64 RESIZE_FACTOR = 2;
		
		u64 CAPACITY;
		T* DATA;
		u64 SIZE;
		public:
			explicit Vector();
			explicit Vector(u64);
			~Vector();
			
			T& operator[](u64);
			// T& at(u64);
			
			void resize();
			
			u64 push(T);
			// u64 push(T, u64);
			T pop();
			T pop(u64);
			
			void clear();
			u64 size() const;
			u64 capacity() const;
			T* data() const;
			
			// Yazh::Types::Iterator<T> begin() const;
			// Yazh::Types::Iterator<T> end() const;
	};
} // namespace Yazh::Containers

#include"vector.tpp"
