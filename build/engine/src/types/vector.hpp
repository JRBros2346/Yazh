#pragma once

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class Vector {
		constexpr const static ysize DEFAULT_CAPACITY = 1;
		constexpr const static ysize RESIZE_FACTOR = 2;
		
		ysize SIZE = 0;
		ysize CAPACITY = 0;
		T* DATA = nullptr;
		public:
			constexpr explicit Vector();
			constexpr explicit Vector(ysize);
			constexpr Vector(const Vector<T>&);
			constexpr Vector(Vector<T>&&);
			constexpr Vector(std::initializer_list<T>);
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