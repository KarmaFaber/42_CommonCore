/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:23:26 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 11:52:24 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Serializer::Serializer (void)	{}

/*	Copy Constructor		*/
Serializer::Serializer(const Serializer &other)
{
	(void)other;
}

/*	Desctructor				*/
Serializer::~Serializer() {}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Serializer& Serializer::operator=(Serializer const &other)
{
	(void)other;
	return (*this);
}

/******************************************************************************/
/*							PUBLIC METHODS									  */
/******************************************************************************/
uintptr_t Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}
