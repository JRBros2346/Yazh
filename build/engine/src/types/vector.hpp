#pragma once

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class Vector {
		const static ysize DEFAULT_CAPACITY = 1;
		const static ysize RESIZE_FACTOR = 2;
		
		ysize SIZE;
		ysize CAPACITY;
		T* DATA;
		public:
			explicit Vector();
			explicit Vector(ysize);
			~Vector();

			T& operator[](u64);

			void resize();

			void push(T);
			void push(T, u64);
			T pop();
			T pop(u64);
			
			void clear();
			void shrink();
			
			ysize size();
			ysize capacity();
			T* data();
	};
} // namespace Yazh::Containers

#include"vector.tcc"