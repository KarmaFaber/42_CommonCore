/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_messages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:11 by mzolotar          #+#    #+#             */
/*   Updated: 2024/11/27 10:38:32 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Prints a message when the player exits the game.
 *
 * @param void No parameters are used in this function.
 * @return void This function does not return.
 */

void	exit_message(void)
{
	ft_printf("\033[1;33m\033[0m\n");
	ft_printf("--------------------------------------------------\n");
	ft_printf("|              You gave up 🙁                    |\n");
	ft_printf("|   Is the game hard for you? Try again......    |\n");
	ft_printf("--------------------------------------------------\n");
}

/**
 * @brief Prints a congratulatory message when the player wins the game.
 *
 * @param void No parameters are used in this function.
 * @return void This function does not return.
 */

void	winner_message(void)
{
	ft_printf("\033[1;32m-------------------------------------------\033[0m\n");
	ft_printf("\033[1;32m|  🎉🎉🎉  Congratulations!!!!!  🎉🎉🎉   |\033[0m\n");
	ft_printf("\033[1;32m|  You found all collectibles and exit.   |\033[0m\n");
	ft_printf("\033[1;32m|      ✓✓✓✓✓✓✓✓ You won! ✓✓✓✓✓✓✓✓         |\033[0m\n");
	ft_printf("\033[1;32m-------------------------------------------\033[0m\n");
}

/**
 * @brief Handles the case of an invalid file type.
 *
 * @param void No parameters are used in this function.
 * @return int Returns 1 to indicate an error.
 */

int	handle_invalid_file_error(void)
{
	perror("\033[1;31m🛑ERROR:\nThe file is not a .ber type.\033[0m\n");
	return (1);
}

/**
 * @brief Handles the case of incorrect argument count in the program.
 *
 * @param void No parameters are used in this function.
 * @return int Returns 1 to indicate an error.
 */

int	handle_argument_error(void)
{
	perror("\033[1;31m🛑ERROR:\nIncorrect number of arguments.\033[0m\n");
	return (1);
}

/**
 * @brief Checks if the given filename has a valid ".ber" extension.
 *
 * @param filename The file name to check.
 * @return int Returns 1 if valid, 0 otherwise.
 */

int	is_valid_file_type(char *filename)
{
	return (ft_strnstr(filename, ".ber", ft_strlen(filename)) != NULL);
}
