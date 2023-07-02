#pragma once

#include"defines.hpp"

namespace Yazh::Containers {
	template<typename T>
	class Vector {
		const static u64 DEFAULT_CAPACITY = 1;
		const static u64 RESIZE_FACTOR = 2;
		
		u64 SIZE;
		u64 CAPACITY;
		T* DATA;
		public:
			explicit Vector();
			explicit Vector(u64);
			~Vector();

			T& operator[](u64);

			void resize();

			void push(T);
			void push(T, u64);
			T pop();
			T pop(u64);
			
			void clear();
			u64 size();
			u64 capacity();
			T* data();
	};
} // namespace Yazh::Containers

#include"vector.tpp"