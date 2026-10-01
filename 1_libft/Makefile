# Variables
NAME        :=  libft.a
CC          :=  cc
CFLAGS      :=  -Wall -Wextra -Werror
ARFLAGS     :=  ar rcs
RM          :=  rm -rf

# Mandatory function files
SRC         :=  ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
                ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
                ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
                ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
                ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
                ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
                ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
                ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
                ft_tolower.c ft_toupper.c

# Bonus functions:
BONUS_SRC   :=  ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
                ft_lstclear_bonus.c ft_lstdelone_bonus.c \
                ft_lstiter_bonus.c ft_lstlast_bonus.c \
                ft_lstmap_bonus.c ft_lstnew_bonus.c \
                ft_lstsize_bonus.c

OBJS        :=  $(SRC:.c=.o)
BONUS_OBJS  :=  $(BONUS_SRC:.c=.o)

# bonus flag:
BONUS_MARK  :=  .bonus_flag

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(ARFLAGS) $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\033[0;32mStatic library '$(NAME)' with mandatory functions created.\n\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_MARK)

$(BONUS_MARK): $(NAME) $(BONUS_OBJS)
	$(ARFLAGS) $(NAME) $(BONUS_OBJS)
	@touch $(BONUS_MARK)
	@echo "\033[0;32mStatic library '$(NAME)' with bonus functions created.\n\033[0m"

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS) $(BONUS_MARK)

fclean: clean 
	@$(RM) $(NAME)
	@echo "\033[0;32mStatic library '$(NAME)' removed.\n\033[0m"

re: fclean all

# Phony declarations
.PHONY: all clean fclean re bonus
