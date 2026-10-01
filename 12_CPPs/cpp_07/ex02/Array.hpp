/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:24:12 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/07 13:11:03 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>
#include <cstddef>
#include <iostream>

template< typename T>

class Array
{
	private:
		T				*_array;
		unsigned int	_size;
	public:
		// Default constructor
		Array(void)
				:	_array(NULL),
					_size(0)
					{
						//std::cout << "[C] Default constructor." << std::endl;
					}

		//Atribute Constructor 
		Array(unsigned int n)
				:	_array(new T[n]()),
					_size(n)
					{
						//std::cout << "[C] Attribute constructor." << std::endl;
					}

		// Copy constructor
		Array(Array const &copy)
				:	_array(new T[copy._size]),
					_size(copy._size)
		{
			//std::cout << "[C] Copy constructor." << std::endl;
			for (unsigned int i = 0; i < _size; ++i)
				_array[i] = copy._array[i];
		}

		// Assignment operator
		Array& operator=(const Array& other)
		{
			//std::cout << "[O] Assignment operator." << std::endl;
			if (this != &other)
			{
				delete[] _array;
				_array = new T[other._size];
				_size = other._size;
				for (unsigned int i = 0; i < _size; ++i)
					_array[i] = other._array[i];
			}
			return (*this);
		}

		// Destructor
		~Array()
		{
			//std::cout << "[D] Destructor." << std::endl;
			delete[] _array;
		}

		// Subscript operator []
		T& operator[](unsigned int i)
		{
			if (i >= _size)
				throw (OutOfBoundsException());
			return (_array[i]);
		}

		// Access operator [] -> Const version
		const T& operator[](unsigned int i) const
		{
			if (i >= _size)
				throw (OutOfBoundsException());
			return (_array[i]);
		}

		//method size()
		unsigned int size() const
		{
			return (_size);
		}

		//exceptions
		class OutOfBoundsException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{
					return "[ARRAY_EXCEPTION] Index out of range";
				}
		};
};

#endif
