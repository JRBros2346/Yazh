#pragma once

#include"defines.hpp"

namespace Yazh::Types {
	template<typename T>
	class YAPI Vector {
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

			T& operator[](ysize);
			const T& operator[](ysize) const;
			T& at(ysize);
			const T& at(ysize) const;

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

			Vector<T>& operator=(const Vector<T>&);
			Vector<T>& operator=(Vector<T>&&);
			
			ysize size() const;
			ysize capacity() const;
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

					Iter operator+(yptrdiff);
					Iter operator-(yptrdiff);

					Iter& operator=(const Iter&);
					Iter& operator=(Iter&&);
					Iter& operator+=(yptrdiff);
					Iter& operator-=(yptrdiff);

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