/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:48:36 by mzolotar          #+#    #+#             */
/*   Updated: 2024/09/18 10:19:35 by mzolotar         ###   ########.fr       */
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

#endif
