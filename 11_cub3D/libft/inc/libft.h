/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdiaz-he <jdiaz-he@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:44:43 by jdiaz-he          #+#    #+#             */
/*   Updated: 2025/03/10 12:31:26 by jdiaz-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*** Typedefs ***/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*** Prototypes libft ***/
int			ft_atoi(const char *str);
long int	ft_atol(const char *str);
void		ft_bzero(void *dst, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_free_strtrim(
				char *to_free, char *str,
				char *(*f)(const char *, const char *));
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isnumeric(char *str, int use_sign);
char		*ft_itoa(int n);
void		ft_matrix_free(char **matrix);
size_t		ft_matrix_size(char **matrix);
void		ft_puterr(char *s);
void		ft_putnbr(int n);
void		ft_putstr_fd(char *s, int fd);
void		ft_putstr(char *s);
void		ft_split_free(char **split);
char		**ft_split(char const *s, char c);
char		*ft_strchr(char *str, char c);
int			ft_strchrset(char *str, char *set);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strdup(const char *s);
char		*ft_strdup_free(char *s);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_sfree(
				char *s1, char *s2, char *for_free1, char *for_free2);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *str, const char *find, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
ssize_t		ft_write(int fd, const void *buff, size_t size);

/*** Prototypes gnl ***/
char		*get_next_line(int fd);
char		*ft_gnl_by_char(int fd);
char		*ft_gnl_by_buffer(int fd, char **buffer, char *line);
char		*ft_read_line_buffer(int fd);
char		*ft_next_line_buffer(char *buffer);
char		*ft_next_buffer(char *buffer);
char		*ft_strjoin_gnl(char *s1, char *s2, char *free_s1, char *free_s2);
size_t		ft_strlen_gnl(char *str);
ssize_t		ft_strchr_index(char *buffer, ssize_t buffer_size, char c);

#endif