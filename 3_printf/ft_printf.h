/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:13:51 by mzolotar          #+#    #+#             */
/*   Updated: 2024/10/18 10:26:32 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/**
 * @brief Custom implementation of printf that handles format specifiers.
 *
 * This function mimics the behavior of the standard printf function. It
 * processes the format string, detects format specifiers, and prints the
 * corresponding arguments. It supports common format specifiers like %c,
 * %s, %p, %d, %i, %u, %x, and %X. For each specifier, it calls the
 * respective helper function to print the formatted value.
 *
 * @param format The format string containing text and format specifiers.
 *
 * @return The total number of characters printed.
 */

int	ft_printf(char const *format, ...);

/*-----%c-----*/
/**
 * @brief Prints a character to the standard output.
 *
 * This function takes a character as input and writes it to the
 * standard output (file descriptor 1) using the helper function
 * `ft_putchar_fd`. It always returns 1, indicating that one
 * character has been printed successfully.
 *
 * @param c The character to be printed.
 *
 * @return Returns 1 to indicate that one character has been printed.
 */

int	ft_print_char(char c);

/*-----%s-----*/
/**
 * @brief Prints a string to the standard output.
 *
 * This function takes a string as input and writes it to the
 * standard output (file descriptor 1). If the input string is
 * NULL, it prints "(null)" instead and returns 6. Otherwise,
 * it calculates the length of the string, prints it, and
 * returns the length.
 *
 * @param str The string to be printed. If NULL, "(null)" is printed.
 *
 * @return Returns the length of the string if it's not NULL,
 *         or 6 if the string is NULL.
 */

int	ft_print_str(char *str);

/*-----%i + %d-----*/
/**
 * @brief Prints an integer to the standard output.
 *
 * This function takes an integer as input, counts the number of digits
 * in the integer, and prints it to the standard output (file descriptor 1).
 * The digit count is determined by calling the helper function
 * `ft_count_digits`. The function returns the total count of digits
 * printed.
 *
 * @param number The integer to be printed.
 *
 * @return Returns the number of digits in the integer.
 */

int	ft_print_int(int number);

/*----%u----*/
/**
 * @brief Prints an unsigned decimal number to the standard output.
 *
 * This function takes an unsigned integer as input, counts the number of
 * digits in that integer, and prints the integer to the file descriptor 1
 * (standard output). It returns the total number of digits printed.
 *
 * @param number The unsigned integer to be printed.
 *
 * @return The number of digits printed.
 */

int	ft_printdec_unsig(unsigned int number);

/*----%p----*/
/**
 * @brief Prints the memory address of a pointer in hexadecimal format.
 *
 * This function prints the memory address pointed to by the pointer,
 * using the '0x' prefix followed by the hexadecimal representation
 * of the address.
 *
 * @param pointer The pointer whose address will be printed.
 * @return The number of characters printed.
 */

int	ft_print_ptr(void *pointer);

/*----%x + %X----*/
/**
 * @brief Prints an unsigned integer in hexadecimal format.
 *
 * This function prints the given unsigned integer as a hexadecimal
 * number, using either lowercase or uppercase letters based on the
 * specified format.
 *
 * @param num The unsigned integer to print in hexadecimal.
 * @param format Format specifier, either 'a' for lowercase or 'A'
 * for uppercase.
 * @return The number of characters printed.
 */

int	ft_print_hex(unsigned int num, char format);

#endif
