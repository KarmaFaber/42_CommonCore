/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:28:36 by mzolotar          #+#    #+#             */
/*   Updated: 2025/10/28 09:51:34 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/
/*	Default Constructor		*/
Brain::Brain(void)
{
	RandomIdeas();
	std::cout << CBLACK << D_C_BRAIN << CRESET << std::endl;
}

/*	Copy Constructor		*/
Brain::Brain(const Brain& other)
{
	for (int i = 0; i < BRAIN_IDEAS; i++)
		this->ideas[i] = other.ideas[i];
	std::cout << CBLACK << C_C_BRAIN << CRESET << std::endl;
}

/*	Desctructor				*/
Brain::~Brain()
{
	std::cout << CBLACK << D_BRAIN << CRESET << std::endl;
}

/******************************************************************************/
/*								OPERATORS								  	  */
/******************************************************************************/
/*	Copy Assignment Operator	*/
Brain& Brain::operator=(const Brain& other)
{
	if (this != &other)
	{
		for (int i = 0; i < BRAIN_IDEAS; i++)
			this->ideas[i] = other.ideas[i];
	}
	std::cout << CBLACK << C_O_BRAIN << CRESET << std::endl;
	return (*this);
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

std::string Brain::getIdea(int idx) const
{
	if (idx < 0 || idx >= BRAIN_IDEAS)
		return "[ERROR]: Wrong Idea Index";
	return ideas[idx];
}

/******************************************************************************/
/*								SETTERS										  */
/******************************************************************************/

void Brain::setIdea(int idx, const std::string& idea)
{
	if (idx < 0 || idx >= BRAIN_IDEAS)
	{
		std::cout << CRED << "[ERROR]: Wrong Idea Index" << CRESET << std::endl;
	}
	if (idx >= 0 && idx < BRAIN_IDEAS)
		ideas[idx] = idea;
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Brain::RandomIdeas()
{
	const std::string random_ideas[] = {
		"Chasing butterflies in the garden",
		"Sleeping under the warm sunlight",
		"Running after a bouncing ball",
		"Exploring a hidden corner of the house",
		"Dreaming of endless food bowls",
		"Climbing up to a higher place",
		"Watching birds through the window",
		"Rolling on the soft grass",
		"Scratching or digging just for fun",
		"Looking for a cozy spot to nap"
	};

	for (int i = 0; i < BRAIN_IDEAS; i++)
		this->ideas[i] = random_ideas[rand() % 10];
}
