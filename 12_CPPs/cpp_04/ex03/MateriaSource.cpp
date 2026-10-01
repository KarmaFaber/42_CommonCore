/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:50 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 10:01:16 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
MateriaSource::MateriaSource(void)
{
	std::cout << CYAN << MSRC_DEF_CTOR << RESET << std::endl;
	for (int i = 0; i < L_SIZE; i++)
		this->_learnInventory[i] = NULL;
	
}

/*	Copy Constructor		*/
MateriaSource::MateriaSource(const MateriaSource& other)
{
	std::cout << CYAN << MSRC_COPY_CTOR << RESET << std::endl;
	for (int i = 0; i < L_SIZE; i++)
	{
		if (other._learnInventory[i])
			this->_learnInventory[i] = other._learnInventory[i]->clone();
		else
			this->_learnInventory[i] = NULL;
	}
}

/*	Desctructor				*/
MateriaSource::~MateriaSource()
{
	std::cout << CYAN << MSRC_DTOR << RESET << std::endl;
	
	for (int i = 0; i < L_SIZE; i++)
	{
		if (this->_learnInventory[i])
		{
			delete this->_learnInventory[i];
			this->_learnInventory[i] = NULL;
		}
	}
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	std::cout << CYAN << MSRC_ASS_OP << RESET << std::endl;
	if (this == &other)
		return (*this);
	for (int i = 0; i < L_SIZE; i++)
	{
		if (this->_learnInventory[i])
		{
			delete this->_learnInventory[i];
			this->_learnInventory[i] = NULL;
		}
	}
	for (int i = 0; i < L_SIZE; i++)
	{
		if (other._learnInventory[i])
			this->_learnInventory[i] = other._learnInventory[i]->clone();
		else
			this->_learnInventory[i] = NULL;
	}
	return (*this);
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/
void MateriaSource::learnMateria(AMateria *materia)
{
	if (!materia)
	{
		std::cout << CYAN << MSRC_NULL << RESET << std::endl;
		return;
	}
	for (int i = 0; i < L_SIZE; i++)
	{
		if (!this->_learnInventory[i])
		{
			this->_learnInventory[i] = materia;
			std::cout << CYAN << "MateriaSource learned " << materia->getType() << RESET << std::endl;
			return;
		}
	}
	std::cout << CYAN << MSRC_FULL << RESET << std::endl;
	delete materia;
}

AMateria*	MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < L_SIZE; i++)
	{
		if (this->_learnInventory[i] && this->_learnInventory[i]->getType() == type)
		{
			std::cout << CYAN << MSRC_CREAT << type << RESET << std::endl;
			return (this->_learnInventory[i]->clone());
		}
	}
	std::cout << CYAN << MSRC_UNKNOWN << type << RESET << std::endl;
	return (NULL);
}
