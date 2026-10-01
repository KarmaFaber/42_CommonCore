#◉────▣───▢◇▢───▣────◉•◉───▣───▢   Colors:   ▢───▣───◉•◉───▣────▢◇▢───▣───◉#

BLACK   := \033[0;30m
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m

CURRENT_COLOR := \033[0;34m
RESET   := \033[0m

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Variables:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

NAME        := push_swap
CC          := cc
CFLAGS      := -Wall -Wextra -Werror 
RM          := rm -rf

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Libft Variables ▢───▣───◉•◉───▣───▢◇▢───▣──◉#

LIBFT_DIR	:= libft/
LIBFT		:= $(LIBFT_DIR)/libft.a
INCLUDES_LIBFT := -I$(LIBFT_DIR)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ push_swap srcs ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

PUSH_SWAP_SRCS	:= push_swap.c error_utils.c stack_utils.c \
				push_command.c swap_command.c reverse_rotate_command.c rotate_command.c \
				push_swap_utils.c init_list_utils.c algorithm_utils.c init_a_to_b.c \
				init_b_to_a.c 

PUSH_SWAP_OBJS	:= $(PUSH_SWAP_SRCS:.c=.o)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBFT_DEPS)
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(PUSH_SWAP_OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(PUSH_SWAP_OBJS) -L$(LIBFT_DIR) -lft $(INCLUDES_LIBFT) 
	@echo "$(CURRENT_COLOR) $(NAME) created.\n$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_LIBFT) -c $< -o $@ 

clean:
	$(RM) $(PUSH_SWAP_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(CURRENT_COLOR)All object files have been cleaned.\n$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(CURRENT_COLOR) $(NAME) and libft.a: have been cleaned.\n$(RESET)"

re: fclean all

#◉───▣───▢◇▢───▣───◉•◉───▣───▢      Test      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

#TEST_DIR := push_swap_Tester/

#test: all 
#	@$(MAKE) -C $(TEST_DIR)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re #test 
