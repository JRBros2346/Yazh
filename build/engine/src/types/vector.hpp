#pragma once

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class Vector {
		const static ysize DEFAULT_CAPACITY = 1;
		const static ysize RESIZE_FACTOR = 2;
		
		ysize SIZE = 0;
		ysize CAPACITY = 0;
		T* DATA = nullptr;
		public:
			explicit Vector();
			explicit Vector(ysize);
			Vector(const Vector<T>&);
			Vector(Vector<T>&&);
			// template<T... Values>
			// Vector(Values...);
			~Vector();

			T& operator[](ysize);
			const T& operator[] (ysize) const;

			void push_back(const T&);
			void push_at(ysize, const T&);
			void push_back(T&&);
			void push_at(ysize, T&&);

			template<typename... Args>
			T& emplace_back(Args&&...);
			template<typename... Args>
			T& emplace_at(ysize, Args&&...);

			T pop_back();
			T pop_at(ysize);
			
			void clear();
			void shrink();
			void resize();

			T& operator=(const Vector<T>&);
			T& operator=(Vector<T>&&);
			
			constexpr ysize size() const;
			constexpr ysize capacity() const;
			constexpr T* data() const;
	};
} // namespace Yazh::Types

#include"vector.tcc"