# Printf variables:
NAME        :=  libftprintf.a
CC          :=  cc
CFLAGS      :=  -Wall -Wextra -Werror
ARFLAGS     :=  ar rcs
RM          :=  rm -rf

#libft variables:
LIBFT_DIR	:=	libft/
LIBFT		=	$(LIBFT_DIR)/libft.a
INCLUDES	:=	-I$(LIBFT_DIR)
VPATH		:=	$(LIBFT_DIR)

#printf:
SRC         :=  ft_printf.c \
					ft_print_char.c \
					ft_printdec_unsig.c  \
					ft_print_hex.c  \
					ft_print_int.c  \
					ft_print_ptr.c  \
					ft_print_str.c  \

OBJS        :=  $(SRC:.c=.o)

#libft:
LIBFT_SRCS	:=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
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

LIBFT_OBJS	:=	$(LIBFT_SRCS:.c=.o)
LIBFT_DEPS	:=	$(addprefix $(LIBFT_DIR), $(LIBFT_OBJS))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	$(ARFLAGS) $(NAME) $(LIBFT_DEPS) $(OBJS)
	@echo "\033[0;35mStatic library '$(NAME)' created.\n\033[0m"
	
$(LIBFT): $(LIBFT_DEPS)
	$(MAKE) -C $(LIBFT_DIR) all
	@echo "\033[0;35m$ libft.a created.\n\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[0;35m$ All object files have been cleaned.\n\033[0m"
	
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[0;35m$(NAME) and libft.a: have been cleaned.\n\033[0m"

re: fclean all

# Phony declarations
.PHONY: all clean fclean re 
