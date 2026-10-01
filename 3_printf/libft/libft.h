/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:48:36 by mzolotar          #+#    #+#             */
/*   Updated: 2024/10/14 10:01:16 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// mandatory functions:
/**
 * @brief Converts a string to an integer.
 *
 * @param nptr Pointer to the string to convert.
 *
 * @return The converted integer value.
 */
int					ft_atoi(const char *nptr);

/**
 * @brief Sets the first n bytes of memory to zero.
 *
 * @param s Pointer to the memory block.
 * @param n Number of bytes to set to zero.
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief Allocates memory for an array and sets it to zero.
 *
 * @param nmemb Number of elements.
 * @param size Size of each element.
 *
 * @return Pointer to allocated memory, or NULL if it fails.
 */
void				*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Checks if a character is alphanumeric.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int					ft_isalnum(int c);

/**
 * @brief Checks if a character is alphabetic.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is alphabetic, 0 otherwise.
 */
int					ft_isalpha(int c);

/**
 * @brief Checks if a character is ASCII.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is ASCII, 0 otherwise.
 */
int					ft_isascii(int c);

/**
 * @brief Checks if a character is a digit.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is a digit, 0 otherwise.
 */
int					ft_isdigit(int c);

/**
 * @brief Checks if a character is printable.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is printable, 0 otherwise.
 */
int					ft_isprint(int c);

/**
 * @brief Converts an integer to a string.
 *
 * @param n The integer to convert.
 *
 * @return Pointer to the string, or NULL if allocation fails.
 */
char				*ft_itoa(int n);

/**
 * @brief Searches memory for a byte.
 *
 * @param s Pointer to the memory block.
 * @param c The byte value to search for.
 * @param n Number of bytes to search.
 *
 * @return Pointer to the byte found, or NULL if not found.
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares two memory blocks.
 *
 * @param s1 Pointer to the first block.
 * @param s2 Pointer to the second block.
 * @param n Number of bytes to compare.
 *
 * @return The difference between the first differing bytes, or 0 if equal.
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies memory from one area to another.
 *
 * @param dest Pointer to the destination area.
 * @param src Pointer to the source area.
 * @param n Number of bytes to copy.
 *
 * @return Pointer to the destination area.
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Moves memory from one area to another, handling overlap.
 *
 * @param dest Pointer to the destination area.
 * @param src Pointer to the source area.
 * @param n Number of bytes to move.
 *
 * @return Pointer to the destination area.
 */
void				*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fills a block of memory with a byte.
 *
 * @param ptr Pointer to the memory area.
 * @param c The byte value to set.
 * @param n Number of bytes to set.
 *
 * @return Pointer to the memory area.
 */
void				*ft_memset(void *ptr, int c, size_t n);

/**
 * @brief Writes a character to a file descriptor.
 *
 * @param c The character to write.
 * @param fd The file descriptor to write to.
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief Writes a string followed by a newline to a file descriptor.
 *
 * @param s The string to write.
 * @param fd The file descriptor to write to.
 */
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes an integer to a file descriptor.
 *
 * @param n The integer to write.
 * @param fd The file descriptor to write to.
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Writes a string to a file descriptor.
 *
 * @param s The string to write.
 * @param fd The file descriptor to write to.
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief Writes a string to a specified file descriptor.
 *
 * This function writes the string 's' to the file descriptor 'fd'. If the 
 * file descriptor is invalid or the string is NULL, it returns -1. Otherwise, 
 * it returns the number of characters written.
 *
 * @param s The string to write. If 's' is NULL, "(null)" will be written.
 * @param fd The file descriptor to write to. Should be a valid file 
 * descriptor.
 * @return The number of characters written, or -1 if an error occurs.
 */
int					ft_putstr_fd_int(char *s, int fd);

/**
 * @brief Splits a string into an array of substrings.
 *
 * @param s The string to split.
 * @param c The delimiter character.
 *
 * @return Array of substrings, or NULL if allocation fails.
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Locates a character in a string.
 *
 * @param s The string to search.
 * @param c The character to locate.
 *
 * @return Pointer to the first occurrence, or NULL if not found.
 */
char				*ft_strchr(const char *s, int c);

/**
 * @brief Duplicates a string.
 *
 * @param s The string to duplicate.
 *
 * @return Pointer to the new string, or NULL if allocation fails.
 */
char				*ft_strdup(const char *s);

/**
 * @brief Iterates over a string, applying a function to each character.
 *
 * @param s The string to iterate.
 * @param f The function to apply.
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Joins two strings into a new string.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 *
 * @return Pointer to the new string, or NULL if allocation fails.
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Concatenates two strings, ensuring null termination.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer.
 *
 * @return Total length of the string it tried to create.
 */
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Copies a string to a destination buffer.
 *
 * @param dst The destination buffer.
 * @param src The source string.
 * @param size The size of the destination buffer.
 *
 * @return Total length of the source string.
 */
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Computes the length of a string.
 *
 * @param s The string to compute the length of.
 *
 * @return The length of the string.
 */
size_t				ft_strlen(const char *s);

/**
 * @brief Applies a function to each character of a string, creating a new one.
 *
 * @param s The input string.
 * @param f The function to apply.
 *
 * @return A new string with the transformed characters,
 * or NULL if allocation fails.
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Compares two strings up to n characters.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The number of characters to compare.
 *
 * @return An integer indicating the difference between the strings.
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Locates a substring within a string.
 *
 * @param big The string to search.
 * @param little The substring to find.
 * @param len The maximum number of characters to search.
 *
 * @return Pointer to the first occurrence, or NULL if not found.
 */
char				*ft_strnstr(const char *big, const char *little,
						size_t len);

/**
 * @brief Locates the last occurrence of a character in a string.
 *
 * @param s The string to search.
 * @param c The character to locate.
 *
 * @return Pointer to the last occurrence, or NULL if not found.
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @brief Trims characters from the beginning and end of a string.
 *
 * @param s1 The string to trim.
 * @param set The set of characters to remove.
 *
 * @return A new string with trimmed characters, or NULL if allocation fails.
 */
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Extracts a substring from a string.
 *
 * @param s The original string.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 *
 * @return Pointer to the substring, or NULL if allocation fails.
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c The character to convert.
 *
 * @return The converted character.
 */
int					ft_tolower(int c);

/**
 * @brief Converts an uppercase letter to lowercase.
 *
 * @param c The character to convert.
 *
 * @return The converted character.
 */
int					ft_toupper(int c);

// bonus funcions: simply linked lists.
/**
 * @brief Adds a new node to the end of a linked list.
 *
 * This function appends the given new node to the end of the list.
 * If the list is empty, the new node becomes the head of the list.
 * If the list is not empty, the function traverses to the last node
 * and updates its `next` pointer to point to the new node.
 *
 * @param lst A pointer to the pointer of the head node of the list.
 *            This allows the function to modify the head if the list
 *            is empty and the new node is the first node.
 * @param new The node to be added at the end of the list. This node
 *            should be properly allocated and initialized before being
 *            passed to this function.
 *
 * @return This function does not return a value.
 */

void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Adds a new node at the beginning of a linked list.
 *
 * This function checks if the list is empty. If it is, the new node
 * becomes the first and only node. If the list is not empty, the new
 * node is linked to the current first node, and then it becomes the
 * new head of the list.
 *
 * @param lst A pointer to the head of the list.
 * @param new The new node to be added at the beginning of the list.
 *
 * @return void
 */

void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Deletes and frees the given node and all subsequent nodes.
 *
 * @param lst Address of a pointer to the first node of the list.
 * @param del Function pointer to delete the content of each node.
 *
 * @return None, the list is cleared and the pointer is set to NULL.
 */

void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Deletes a node from a linked list and frees its memory.
 *
 * @param lst Pointer to the node to be deleted.
 * @param del Function pointer to free the node's content.
 *
 * @return None.
 */

void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Applies a function to each element of a linked list.
 *
 * This function iterates over each node in the linked list and applies
 * the provided function to the data contained in each node. The function
 * is called once for each node, allowing the caller to modify or inspect
 * the node's data.
 *
 * @param lst Pointer to the first node of the linked list.
 * @param f Pointer to a function that takes a void pointer and returns void.
 *          This function will be applied to the data of each node.
 *
 * @return This function does not return a value.
 */

void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Finds the last node of a linked list.
 *
 * This function traverses the linked list starting from the
 * given node, and returns a pointer to the last node in the list.
 *
 * @param lst Pointer to the first node of the linked list.
 *
 * @return Pointer to the last node of the list, or NULL if empty.
 */

t_list				*ft_lstlast(t_list *lst);

/**
 * @brief Applies a function to each element of a linked list to
 *        create a new list with the results. Handles errors by
 *        freeing allocated nodes using a deletion function.
 *
 * @param lst A pointer to the first node of the original linked list.
 * @param f A pointer to a function that takes a void pointer and
 *          returns a new void pointer for the transformed node content.
 * @param del A pointer to a function used to free memory of nodes
 *            if an error occurs during the list creation.
 *
 * @return A pointer to the first node of the new linked list with
 *         transformed elements. Returns NULL if the list is NULL
 *         or if memory allocation fails.
 */

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief Creates a new node for a linked list.
 *
 * This function allocates memory for a new node, initializes the node's
 * content with the provided value, and sets the next pointer to NULL.
 *
 * @param content Pointer to the data that will be stored in the new node.
 *
 * @return t_list* Pointer to the newly created node, or NULL if allocation
 * fails.
 */

t_list				*ft_lstnew(void *content);

/**
 * @brief Counts the number of nodes in a linked list.
 *
 * This function iterates through the linked list and increments
 * a counter for each node it encounters. The total count is then
 * returned as the size of the list.
 *
 * @param lst Pointer to the first node of the linked list.
 *
 * @return The total number of nodes in the linked list.
 */

int					ft_lstsize(t_list *lst);

// own funcions:
/**
 * @brief Inserts a new node at the beginning of the linked list.
 *
 * This function creates a new node with the given content and inserts it
 * at the head of the list. The new node becomes the new head of the list,
 * and its next pointer points to the previous head node.
 *
 * @param head A double pointer to the head of the linked list. This allows
 *             modification of the head pointer itself.
 * @param content A pointer to the content to be stored in the new node.
 *                If the content is NULL, it will still create a node, but
 *                the node's content pointer will be NULL.
 *
 * @return void
 */

void				ft_add_node_front(t_list **head, void *content);

/**
 * @brief   Converts the string pointed to by nptr to a long integer.
 *
 * This function takes a string and converts it to a long integer. It handles
 * leading whitespace characters and an optional '+' or '-' sign.
 *
 * @param   nptr A pointer to the null-terminated string to be converted.
 *
 * @return  The converted long integer value. If the string does not contain
 *          any valid number, the function returns 0.
 */

long int			ft_atol(const char *nptr);

/**
 * @brief Counts the digits in an unsigned integer.
 *
 * This function calculates the number of digits in a given unsigned
 * integer by repeatedly dividing it by 10.
 *
 * @param number The unsigned integer whose digits are to be counted.
 *
 * @return int The number of digits in the unsigned integer.
 */

int					ft_count_digits_unsigned(unsigned int number);

/**
 * @brief  Returns the number of digits in an integer.
 *
 * @param  n The integer whose digits are to be counted.
 * Handles INT_MIN and LONG_MIN as special cases to avoid overflow.
 *
 * @return The count of digits in the integer,
 *  not including the '-' for negative numbers.
 */

int					ft_count_digits(int number);

/**
 * @brief Deletes the first node of a linked list and updates the head pointer.
 *
 * This function removes the first node of a linked list and frees its memory.
 * If the node contains dynamically allocated content,
	it also frees the content.
 * The head pointer is updated to point to the next node in the list.
 * If the list is empty (head is NULL), the function does nothing.
 *
 * @param head Double pointer to the head of the linked list.
 *
 * @return void. The function does not return a value.
 */

void				ft_delete_first_node(t_list **head);

/**
 * @brief Deletes a specified node from a linked list.
 *
 * This function removes a node from a linked list. It handles the case
 * where the node to be deleted is the head of the list, as well as
 * the case where it is a middle or last node. After the node is removed,
 * the memory allocated for the node is freed.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 * @param node_to_delete Pointer to the node that needs to be deleted.
 *
 * @return None.
 */

void				ft_delete_node(t_list **head, t_list *node_to_delete);

/**
 * @brief Deletes the last node of a singly linked list.
 *
 * @param head Double pointer to the head of the linked list.
 *
 * @return void
 */

void				ft_delete_node_tail(t_list **head);

/**
 * @brief Searches for a specific value in a linked list.
 *
 * @param head Pointer to the head of the linked list.
 * @param val Integer value to search for in the list.
 *
 * @return Pointer to the node containing the value, or NULL if not found.
 */

t_list				*ft_find_node_n_val(t_list *head, int val);

/**
 * @brief  Converts an integer to its string representation.
 *
 * @param  n The integer to be converted.
 * @param  new_char A pointer to the allocated memory
	where the result will be stored.
 * @param  size The size of the string, including the sign and '\0'.
 *
 * @return A pointer to the resulting string.
 */

void				ft_int_to_char(int n, char *new_char, size_t size);

/**
 * @brief	Check if a character is lowercase.
 *
 * @param c	The character to check.
 *
 * @return	1 if the character is lowercase, 0 otherwise.
 */

int					ft_islower(int c);

/**
 * @brief   Checks if the given character is a whitespace character.
 *
 * This function checks if the character passed as an argument is a whitespace
 * character, which includes space, tab, newline, vertical tab,
 * form feed, and carriage return.
 *
 * @param   c The character to be checked, represented as an integer.
 *
 * @return  1 if the character is a whitespace character, 0 otherwise.
 */

int					ft_isspace(int c);

/**
 * @brief	Check if a character is uppercase.
 *
 * @param c	The character to check.
 *
 * @return	1 if the character is uppercase, 0 otherwise.
 */

int					ft_isupper(int c);

/**
 * @brief Search for the last occurrence of a byte in a memory block.
 *
 * @param s Pointer to the memory block to search.
 * @param c Byte to search for (converted to unsigned char).
 * @param n Number of bytes to search in the block.
 * @return Pointer to the last occurrence of the byte, or NULL if not found.
 */

void				*ft_memrchr(const void *s, int c, size_t n);

/**
 * @brief Outputs an unsigned integer to the specified file descriptor.
 *
 * This function recursively prints each digit of the unsigned integer
 * by dividing it by 10 until all digits are printed.
 *
 * @param n The unsigned integer to be printed.
 * @param fd The file descriptor to which the output will be written.
 *
 * @return void This function does not return a value.
 */

void				ft_putnbr_unsigned_fd(unsigned int n, int fd);

/**
 * Swaps the values of two integers.
 *
 * This function takes two integer pointers as arguments and swaps
 * the values they point to. The value of the integer pointed to
 * by `a` is exchanged with the value of the integer pointed to by `b`.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */

void				ft_swap(int *a, int *b);

/**
 * @brief Counts the number of words in a string separated by a delimiter.
 *
 * @param s Pointer to the input string to analyze.
 * @param delimiter Character used to separate words in the input string.
 *
 * @return The number of words found in the string.
 */

size_t				ft_word_count(const char *s, char delimiter);

#endif
