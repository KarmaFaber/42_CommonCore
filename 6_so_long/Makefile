#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──Variables──✧❅✦❅✧──────❅••❅──────✧❅✦❅✧─────❅•#

NAME        := so_long
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
RM          := rm -rf
VALGRIND	:= valgrind --leak-check=full --show-leak-kinds=all -s

#•❅─────✧❅✦❅✧─────❅••❅─────✧❅✦❅✧──Libft Variables──✧❅✦❅✧─────❅••❅─────✧❅✦❅✧─────❅•#

LIBFT_DIR	:= libft/
LIBFT		:= $(LIBFT_DIR)/libft.a
INCLUDES_LIBFT := -I$(LIBFT_DIR)

#•❅──────✧❅✦❅✧─────❅••❅──────✧❅✦❅✧──so_long srcs──✧❅✦❅✧──────❅••❅─────✧❅✦❅✧──────❅•#

SO_LONG_SRCS:=  so_long.c read_map.c check_map.c error_gestor.c map_utils.c mlx_hook.c \
				render_map.c game_messages.c check_path.c copi_split.c movements.c \
				img_gestor.c read_map_utils.c check_map_utils.c

SO_LONG_OBJS	:= $(SO_LONG_SRCS:.c=.o)

#•❅────✧❅✦❅✧────❅••❅────✧❅✦❅✧────MLX variables────✧❅✦❅✧─────❅••❅─────✧❅✦❅✧───────❅•#

MLX_DIR 	:= mlx_linux
MLX_LIB 	:= $(MLX_DIR)/libmlx_Linux.a
INCLUDES_MLX := -I/usr/include -I$(MLX_DIR)
MLX_FLAGS 	:= -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

#•❅───────✧❅✦❅✧──────❅••❅───────✧❅✦❅✧──rules──✧❅✦❅✧─────────❅••❅──────✧❅✦❅✧──────❅•#

all: $(LIBFT) $(MLX_LIB) $(NAME)
	
$(NAME): $(SO_LONG_OBJS) 
	@$(CC) $(CFLAGS) -o $(NAME) $(SO_LONG_OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)
	@echo "\033[0;35m'$(NAME)' created.\n\033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all
	@echo "\033[0;35m$ libft.a created.\n\033[0m"

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_LIBFT) $(INCLUDES_MLX) -c $< -o $@ 

clean:
	$(RM) $(SO_LONG_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "\033[0;35m$ All object files have been cleaned.\n\033[0m"

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[0;35m$(NAME) and libft.a: have been cleaned.\n\033[0m"

re: fclean all

#•❅───────✧❅✦❅✧───────❅••❅───────✧❅✦❅✧──Valgrind──✧❅✦❅✧───────❅••❅──────✧❅✦❅✧───────❅•#

valgrind: all
	$(VALGRIND) ./$(NAME) map_8_invalid.ber

valgrind: all
	$(VALGRIND) ./$(NAME) $(MAP_NAME)

#•❅───────✧❅✦❅✧──────❅••❅───────✧❅✦❅✧──Norminette──✧❅✦❅✧───────❅••❅──────✧❅✦❅✧───────❅•#

norm:
	@echo "\033[0;35mChecking Norminette:\n\033[0m"
	@norminette libft $(SO_LONG_SRCS) so_long.h

#•❅───────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──Phony targets──✧❅✦❅✧───────❅••❅──────✧❅✦❅✧─────❅•#

.PHONY: all clean fclean re valgrind norm test