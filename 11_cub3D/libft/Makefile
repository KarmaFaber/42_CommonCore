# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 11:47:14 by jdiaz-he          #+#    #+#              #
#    Updated: 2025/08/11 09:55:59 by mzolotar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
CRESET					:=	\033[0m
CRED					:=	\033[31m
CGREEN					:=	\033[32m
CYELLOW					:=	\033[33m
CBLUE					:=	\033[34m
CGREEN_BG				:=	\033[42m
CYELLOW_BG				:=	\033[43m
CBLUE_BG				:=	\033[44m

# Compiler
CC						:=	gcc
CC_FLAGS				:=	-Wall -Werror -Wextra
LEAK_FLAGS				:=	-g3 -fsanitize=address
OPTIMIZE_FLAGS			:=	-O3

# LIBFT
DIR_INC					:=	inc/
DIR_SRC					:=	src/
DIR_OBJ					:=	obj/
NAME					:=	libft.a
LIBFT_HEADER			:=	$(DIR_INC)libft.h
LIBFT_SRC				:=	ft_atoi.c\
							ft_atol.c\
							ft_bzero.c\
							ft_calloc.c\
							ft_free_strtrim.c\
							ft_isalnum.c\
							ft_isalpha.c\
							ft_isdigit.c\
							ft_isnumeric.c\
							ft_itoa.c\
							ft_matrix_free.c\
							ft_matrix_size.c\
							ft_puterr.c\
							ft_putnbr.c\
							ft_putstr_fd.c\
							ft_putstr.c\
							ft_split_free.c\
							ft_split.c\
							ft_strchr.c\
							ft_strchrset.c\
							ft_strcmp.c\
							ft_strcpy.c\
							ft_strdup.c\
							ft_strdup_free.c\
							ft_strjoin_free.c\
							ft_strjoin_sfree.c\
							ft_strjoin.c\
							ft_strlen.c\
							ft_strncmp.c\
							ft_strnstr.c\
							ft_strtrim.c\
							ft_substr.c\
							ft_write.c\
							get_next_line_utils.c\
							get_next_line.c

LIBFT_OBJ				:=	$(addprefix $(DIR_OBJ), $(LIBFT_SRC:c=o))

all						:	$(NAME)

# Files
$(DIR_OBJ)%.o			:	$(DIR_SRC)%.c $(LIBFT_HEADER)
						@if [ ! -e $@ ]; then \
							echo "$(CBLUE)Libft: Compiling $(notdir $@):	\c"; \
						else \
							echo "$(CBLUE)Libft: $(CBLUE_LIGHT)Re$(CRESET)$(CBLUE)compiling $(notdir $@):	\c"; \
						fi
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) $(OPTIMIZE_FLAGS) -c $< -o $@ $(LEAKS_FLAGS)
						@echo "$(CGREEN)File compiled.$(CRESET)"

$(NAME)					: $(LIBFT_OBJ)
						@echo "$(CYELLOW)Libft: Compiling $(notdir $@):	$(CRESET)"
						@ar -rcs $(NAME) $(LIBFT_OBJ)
						@echo "$(CGREEN)************************************$(CRESET)"
						@echo "$(CRED)* $(CGREEN_BG)        Libft compiled          $(CRESET)$(CGREEN) *$(CRESET)"
						@echo "$(CGREEN)************************************$(CRESET)"

# Clean rules
clean					:
						@if [ -d $(DIR_OBJ) ]; then \
							rm -rf $(LIBFT_OBJ) $(DIR_OBJ); \
							echo "$(CYELLOW_BG)Libft:$(CRESET)$(CYELLOW) Object files removed.$(CRESET)"; \
						fi

fclean					:	clean
						@rm -rf $(NAME)
						@echo "$(CYELLOW_BG)Libft:$(CRESET)$(CYELLOW) Libft removed.$(CRESET)"

re						:	fclean all

.PHONY					:	all clean fclean re