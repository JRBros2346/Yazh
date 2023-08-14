#pragma once

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class YAPI Vector {
		constexpr static std::size_t DEFAULT_CAPACITY = 1;
		constexpr static std::size_t RESIZE_FACTOR = 2;
		
		std::size_t m_size = 0;
		std::size_t m_capacity = 0;
		T* m_data = nullptr;
		public:
			Vector();
			explicit Vector(std::size_t);
			Vector(const Vector<T>&);
			Vector(Vector<T>&&);
			Vector(std::initializer_list<T>);
			~Vector();

			T& operator[](std::size_t);
			const T& operator[](std::size_t) const;
			T& at(std::size_t);
			const T& at(std::size_t) const;

			void push_back(const T&);
			void push_at(std::size_t, const T&);
			void push_back(T&&);
			void push_at(std::size_t, T&&);

			template<typename... Args>
			T& emplace_back(Args&&...);
			template<typename... Args>
			T& emplace_at(std::size_t, Args&&...);

			T pop_back();
			T pop_at(std::size_t);
			
			void clear();
			void shrink();
			void resize();

			Vector<T>& operator=(const Vector<T>&);
			Vector<T>& operator=(Vector<T>&&);
			
			std::size_t size() const;
			std::size_t capacity() const;
			T* data() const;

			class Iter {
				T* ptr = nullptr;
				public:
					Iter();
					Iter(T*);
					Iter(const Iter&);
					~Iter();

					T& operator*();
					T* operator->();
					const T& operator*() const;
					const T* operator->() const;

					Iter operator+(std::ptrdiff_t);
					Iter operator-(std::ptrdiff_t);

					Iter& operator=(const Iter&);
					Iter& operator=(Iter&&);
					Iter& operator+=(std::ptrdiff_t);
					Iter& operator-=(std::ptrdiff_t);

					Iter& operator++();
					Iter operator++(int);
					Iter& operator--();
					Iter operator--(int);

					bool operator==(const Iter&);
					bool operator!=(const Iter&);
					bool operator>=(const Iter&);
					bool operator<=(const Iter&);
					bool operator>(const Iter&);
					bool operator<(const Iter&);
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