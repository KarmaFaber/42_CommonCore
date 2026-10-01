#Variables
NAME	:=	libft.a
CC	:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
ARFLAGS	:=	ar rcs
RM	:=	rm -rf 

# Mandatory function files
SRC		:=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
			ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
			ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_tolower.c ft_toupper.c \
			ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c ft_lstlast_bonus.c \
			ft_lstmap_bonus.c ft_lstnew_bonus.c \
			ft_lstsize_bonus.c \
			ft_atol_own.c \
			ft_count_digits_own.c \
			ft_count_dig_unsigned_own.c \
			ft_delete_first_node_own.c \
			ft_delete_node_own.c \
			ft_delete_node_tail_own.c \
			ft_find_node_n_val_own.c \
			ft_int_to_char_own.c \
			ft_islower_own.c \
			ft_isspace_own.c \
			ft_isupper_own.c \
			ft_memrchr_own.c \
			ft_putnbr_unsigned_fd_own.c \
			ft_swap_own.c \
			ft_word_count_own.c \
			ft_putstr_fd_int.c \

OBJS		:=	$(SRC:.c=.o)


# Rules
all: $(NAME)
	@echo "\033[0;34mStatic library '$(NAME)' created.\n\033[0m"

$(NAME): $(OBJS)
	$(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@$(RM) $(OBJS)
	@echo "\033[0;34mObject files '$(NAME)' removed.\n\033[0m"
	
fclean: clean 
	@$(RM) $(NAME)
	@echo "\033[0;34mStatic library '$(NAME)' removed.\n\033[0m"

re: fclean all 

# Phony declarations
.PHONY: all clean fclaen re #.SILENT
