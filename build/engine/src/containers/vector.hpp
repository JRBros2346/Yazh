#pragma once

#include"defines.hpp"

namespace Yazh::Containers {
	template<class T>
	class Vector {
		const static u64 DEFAULT_CAPACITY = 1;
		const static u64 RESIZE_FACTOR = 2;
		
		u64 SIZE;
		u64 CAPACITY;
		T* DATA;
		public:
			Vector(T* data = nullptr);
			Vector(Vector<T>& other);
			Vector(u64 capacity);
			~Vector() { delete [] DATA; }
			
			T& operator[](u64 pos);
			T& at(u64 pos);
			
			void resize();
			
			void push(T value, u64 pos = SIZE);
			T pop(T value, u64 pos = SIZE);
			
			void clear();
			u64 size();
			u64 capacity();
			
			void setSize(u64 size);
	};
} // namespace Yazh::Containers
