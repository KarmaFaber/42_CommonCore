/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:38:05 by mzolotar          #+#    #+#             */
/*   Updated: 2025/11/06 11:07:01 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checkers.hpp"

bool	checkSpecial(const std::string& str)
{
	if (str == "nan" || str == "nanf" || str == "+inf" || str == "+inff" || str == "-inf" || str == "-inff")
		return (true);
	return (false);
}

bool	checkChar(const std::string& str)
{
	if (str.length() == 1 && !isdigit(str[0]))
		return (true);
	if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
		return (true);
	return (false);
}

bool	checkInt(const std::string& str)
{
	if (str.empty())
		return (false);
	size_t i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str.length() == 1)
			return (false);
		i++;
	}
	for (; i < str.length(); ++i)
	{
		if (!std::isdigit(str[i]))
			return (false);
	}
	errno = 0;
	char* endPtr;
	long value = std::strtol(str.c_str(), &endPtr, 10);		//✅ detecta errores y overflow explícitamente.

	if (*endPtr != '\0' || errno == ERANGE) // Si strtol no consumió toda la cadena o hubo desbordamiento:
		return (false);
	if (value < std::numeric_limits<int>::min()
		|| value > std::numeric_limits<int>::max())
		return (false);
	return (true);
}

bool	checkFloat(const std::string& str, size_t& dot)
{
	if (dot == std::string::npos || str[str.length() - 1] != 'f') //	// Debe existir un punto y terminar en 'f'
		return (false);
		
	if (str.length() < 3) // Verificación mínima: que haya algo antes de la 'f' ->  ejemplos: "f", ".f", "0f"
		return (false);
		
	bool hasDigitBefore = (false);
	bool hasDigitAfter = (false);

	for (int j = static_cast<int>(dot) - 1; j >= 0; j--) 	// --- Parte izquierda del punto --- > Comprueba que antes del punto solo haya dígitos o signo +/−.
	{
		if (isdigit(str[j]))
			hasDigitBefore = true;
		else if (j == 0 && (str[j] == '+' || str[j] == '-'))
			continue; // signo permitido solo al principio
		else
			return (false);
	}
	
	for (size_t i = dot + 1; i < str.length() - 1; i++) 	// --- Parte derecha del punto (antes de la 'f') ---
	{
		if (isdigit(str[i]))
			hasDigitAfter = true;
		else
			return (false);
	}
	
	if (!hasDigitBefore && !hasDigitAfter)	// Al menos un dígito antes o después del '.'
		return (false);
	return (true);
}
