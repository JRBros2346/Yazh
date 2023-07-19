#pragma once

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class Vector {
		constexpr const static ysize DEFAULT_CAPACITY = 1;
		constexpr const static ysize RESIZE_FACTOR = 2;
		
		ysize m_size = 0;
		ysize m_capacity = 0;
		T* m_data = nullptr;
		public:
			Vector();
			explicit Vector(ysize);
			Vector(const Vector<T>&);
			Vector(Vector<T>&&);
			Vector(std::initializer_list<T>);
			~Vector();

			constexpr T& operator[](ysize);
			constexpr const T& operator[](ysize) const;
			constexpr T& at(ysize);
			constexpr const T& at(ysize) const;

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

			class Iter {
				T* ptr;
				public:
					constexpr Iter();
					constexpr Iter(T*);
					constexpr ~Iter();

					constexpr T& operator*();
					constexpr T* operator->();
					constexpr const T& operator*() const;
					constexpr const T* operator->() const;

					constexpr Iter operator+(yptrdiff);
					constexpr Iter operator-(yptrdiff);

					constexpr Iter& operator=(const Iter&);
					constexpr Iter& operator=(Iter&&);
					constexpr Iter& operator+=(yptrdiff);
					constexpr Iter& operator-=(yptrdiff);

					constexpr Iter& operator++();
					constexpr Iter operator++(int);
					constexpr Iter& operator--();
					constexpr Iter operator--(int);

					constexpr bool operator==(const Iter&);
					constexpr bool operator!=(const Iter&);
					constexpr bool operator>=(const Iter&);
					constexpr bool operator<=(const Iter&);
					constexpr bool operator>(const Iter&);
					constexpr bool operator<(const Iter&);
			};

			Iter begin();
			Iter end();
			Iter rbegin();
			Iter rend();
			const Iter cbegin() const;
			const Iter cend() const;
			const Iter crbegin() const;
			const Iter crend() const;
	};

	
} // namespace Yazh::Types

#include"vector.tcc"