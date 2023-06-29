#pragma once

#include"defines.hpp"

#include"types/iterator.hpp"

namespace Yazh::Containers {
	template<class T>
	class Vector {
		const static u64 DEFAULT_CAPACITY = 1;
		const static u64 RESIZE_FACTOR = 2;
		
		u64 SIZE;
		u64 CAPACITY;
		T* DATA;
		public:
			explicit Vector();
			explicit Vector(T*);
			explicit Vector(Vector<T>&);
			explicit Vector(u64);
			~Vector();
			
			T& operator[](u64);
			T& at(u64);
			
			void resize();
			
			u64 push(T, u64 = SIZE);
			T pop(u64 = SIZE - 1);
			
			void clear();
			u64 size() const;
			u64 capacity() const;
			T* data() const;
			
			Yazh::Types::Iterator<T> begin() const;
			Yazh::Types::Iterator<T> end() const;
	};
} // namespace Yazh::Containers
