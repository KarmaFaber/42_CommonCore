# Colors
CRESET				:=	\033[0m
CGRAY				:=	\033[30m
CRED				:=	\033[31m
CGREEN				:=	\033[32m
CYELLOW				:=	\033[33m
CBLUE				:=	\033[34m
CPURPLE				:=	\033[35m
CBLUE_LIGHT			:=	\033[36m
CWHITE				:=	\033[37m
CBLACK_BG			:=	\033[40m
CRED_BG				:=	\033[41m
CGREEN_BG			:=	\033[42m
CYELLOW_BG			:=	\033[43m
CBLUE_BG			:=	\033[44m
CPURPLE_BG			:=	\033[45m
CBLUE_LIGHT_BG		:=	\033[46m
CWHITE_BG			:=	\033[47m

# System
UNAME				:=	$(shell uname -s)

# Commons dirs
DIR_INC				:=	inc/
DIR_SRC				:=	src/
DIR_OBJ				:=	obj/

# Libft
DIR_LIB				:=	libft/
LIBFT_NAME			:=	ft
LIBFT_FILE			:=	libft.a
LIBFT				:=	$(DIR_LIB)$(LIBFT_FILE)
LIBFT_MAKE			:=	$(DIR_LIB)Makefile
LIBFT_HEADER		:=	$(DIR_LIB)$(DIR_INC)libft.h
LIBFT_SRC			:=	$(wildcard $(DIR_LIB)$(DIR_SRC)*.c)
LIBFT_OBJ			:=	$(addprefix $(DIR_LIB)$(DIR_OBJ), $(notdir $(LIBFT_SRC:c=o)))

# MLX variables
MLX_DIR				:=	minilibx_linux/
MLX_LIB				:=	$(MLX_DIR)/libmlx_Linux.a
INCLUDES_MLX		:=	-I/usr/include -I$(MLX_DIR)
MLX_FLAGS			:=	-L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# cub3D
NAME				:=	cub3D
HEADER				:=	$(DIR_INC)const.h\
						$(DIR_INC)cub3d.h\
						$(DIR_INC)datatypes.h\
						$(DIR_INC)game.h\

SRC					:=	\
						errors/error_exit.c\
						\
						datatypes/t_color.c\
						datatypes/t_cubfile.c\
						datatypes/t_game.c\
						datatypes/t_img.c\
						datatypes/t_map.c\
						datatypes/t_player.c\
						datatypes/t_ray.c\
						\
						game/game_loop.c\
						\
						game/raycasting/ray_init.c\
						game/raycasting/ray_texture.c\
						\
						game/render/background.c\
						\
						game/init/player_setup.c\
						game/init/textures.c\
						\
						game/input/player_movement.c\
						game/input/camera_movement.c\
						\
						parser/check_args.c\
						parser/check_cubfile.c\
						parser/cubfile_elements.c\
						parser/parser_utils.c\
						parser/playable.c\
						parser/read_cubfile.c\
						parser/read_map.c\
						\
						cub3d.c

OBJ					:=	$(addprefix $(DIR_OBJ), $(SRC:c=o))

# Dependencies
DEPENDENCIES		:=	$(LIBFT_HEADER) \
						$(LIBFT_SRC)

# Compiler (Linux default)
CC					:=	cc
CC_FLAGS			:=	-Wall -Werror -Wextra
#OPTIMIZE_FLAGS		:=	-O3
LIBFT_FLAGS			:=	-I$(DIR_LIB)$(DIR_INC) -L$(DIR_LIB) -l$(LIBFT_NAME)
MATH_FLAGS			:=	-lm
LEAKS_FLAGS			:=	-g3
PREPROCESS_FLAG		:=	-E
ASSEMBLY_FLAG		:=	-S

# Allow spaces in cub3D
ALLOW				:=	-DALLOW_SPACES=\"\ \\t\\n\\v\\f\\r\"
ALLOW_SPACES		:=

# Files
all					:	$(LIBFT) $(MLX_LIB) $(NAME) banner

$(DIR_OBJ)%.o		:	$(DIR_SRC)%.c $(HEADER)
					@if [ ! -e $@ ]; then \
						echo "$(CBLUE)cub3D: Compiling $(notdir $@):	\c"; \
					else \
						echo "$(CBLUE)cub3D: $(CBLUE_BG)Re$(CRESET)$(CBLUE)compiling $(notdir $@):	\c"; \
					fi
					@mkdir -p $(@D)
					@$(CC) $(CC_FLAGS) $(OPTIMIZE_FLAGS) -c $< -o $@ $(LEAKS_FLAGS) $(ALLOW_SPACES)
					@echo "$(CGREEN) File compiled.$(CRESET)"

$(NAME)				:	$(OBJ) $(DEPENDENCIES) $(MLX_LIB)
					@echo "$(CYELLOW)cub3D: Compiling $(notdir $@):	$(CRESET)"
					@$(CC) $(CC_FLAGS) $(OPTIMIZE_FLAGS) $(OBJ) $(LIBFT_FLAGS) $(LEAKS_FLAGS) $(INCLUDES_MLX) $(MLX_FLAGS) -o $@ $(MATH_FLAGS)
					@echo "$(CGREEN)************************************$(CRESET)"
					@echo "$(CRED)* $(CGREEN_BG)       cub3D compiled         $(CRESET)$(CGREEN) *$(CRESET)"
					@echo "$(CGREEN)************************************$(CRESET)"

# LIBFT Compilation
$(LIBFT)			:	$(LIBFT_HEADER) $(LIBFT_SRC)
					@$(MAKE) -s -C $(DIR_LIB) --no-print-directory
					
# MLX Compilation
$(MLX_LIB)			:
					@echo "Compiling minilibx..."
					cd $(MLX_DIR) && chmod +x configure && sh configure 

set_allow			:
					@$(eval ALLOW_SPACES := $(ALLOW))

allow_spaces		:	set_allow re
					@echo "$(CGRAY) Recompiled with allow_spaces... $(CRESET)"

libftclean			:
					@make clean -C $(DIR_LIB) --no-print-directory

libftfclean			:
					@make fclean -C $(DIR_LIB) --no-print-directory

# Clean rules
clean				:	libftclean
					@rm -rf $(OBJ) $(DIR_OBJ)
					@echo "$(CYELLOW_BG)cub3D:$(CRESET)$(CYELLOW) Object files removed.$(CRESET)"

fclean				:	libftfclean clean
					@rm -rf $(NAME)
					@echo "$(CYELLOW_BG)cub3D:$(CRESET)$(CYELLOW) Executable removed.$(CRESET)"

re					:	fclean all

# Banner
banner:
	@echo "$(CBLUE)"
	@echo "                                                               "
	@echo "                                   .--,-\`\`-.                   "
	@echo "                                  /   /     '.      ,---,     "
	@echo "                         ,---,   / ../        ;   .'  .' \`\\   "
	@echo "                   ,--,,---.'|   \ \`\`\  .\`-    ',---.'     \\  "
	@echo "                 ,'_ /||   | :    \___\\/   \\   :|   |  .\`\\  | "
	@echo "   ,---.    .--. |  | ::   : :         \\   :   |:   : |  '  | "
	@echo "  /     \\ ,'_ /| :  . |:     |,-.      /  /   / |   ' '  ;  : "
	@echo " /    / ' |  ' | |  . .|   : '  |      \\  \\   \\ '   | ;  .  | "
	@echo ".    ' /  |  | ' |  | ||   |  / :  ___ /   :   ||   | :  |  ' "
	@echo "'   ; :__ :  | : ;  ; |'   : |: | /   /\\   /   :'   : | /  ;  "
	@echo "'   | '.'|'  :  \`--'   \\   | '/ :/ ,,/  ',-    .|   | '\` ,/   "
	@echo "|   :    ::  ,      .-./   :    |\\ ''\\        ; ;   :  .'     "
	@echo " \\   \\  /  \`--\`----'   /    \\  /  \\   \\     .'  |   ,.'       "
	@echo "  \`----'               \`-'----'    \`--\`-,,-'    '---'         "
	@echo "                                                               "
	@echo "$(CRESET)"


# Norminette
norm				:
					@echo "$(CGREEN)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Checking Norminette: ──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔$(CRESET)"
					@norminette $(DIR_LIB)$(DIR_INC) $(DIR_LIB)$(DIR_SRC)*.c $(DIR_INC)*.h $(addprefix $(DIR_SRC), $(SRC))
					@echo "$(CGREEN)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Norminette completed. Check your output for details. ─╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣╌╌─$(CRESET)"

.PHONY:	all clean fclean re norm allow_spaces libftclean libftfclean .SILENT
