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

NAME        := serialization
CC          := c++
CPPFLAGS    := -Wall -Wextra -Werror -std=c++98 
RM          := rm -rf

#◉───▣───▢◇▢───▣───◉•◉───▣───▢      srcs      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

SRCS	:= main.cpp Serializer.cpp
OBJS	:= $(SRCS:.cpp=.o)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: $(NAME) banner 

$(NAME): $(OBJS) 
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CURRENT_COLOR)$(NAME) created.$(RESET)"

%.o: %.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@

banner:
	@echo "$(GREEN)                             $(RESET)"
	@echo "$(GREEN)  ______                     $(RESET)"
	@echo "$(GREEN) /      \    __        __    $(RESET)"
	@echo "$(GREEN)/++++++  |  /  |      /  |   $(RESET)"
	@echo "$(GREEN)++ |  ++/ __++ |__  __++ |__ $(RESET)"
	@echo "$(GREEN)++ |     /  ++    |/  ++    |$(RESET)"
	@echo "$(GREEN)++ |   __++++++++/ ++++++++/ $(RESET)"
	@echo "$(GREEN)++ \__/  |  ++ |      ++ |   $(RESET)"
	@echo "$(GREEN)++    ++/   ++/       ++/    $(RESET)"
	@echo "$(GREEN) ++++++/                     $(RESET)"
	@echo "$(GREEN)                             $(RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "$(CURRENT_COLOR)All object files have been cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CURRENT_COLOR)$(NAME): have been cleaned.$(RESET)"

re: fclean all

valgrind: all $(NAME)
	@echo "$(CURRENT_COLOR)Running valgrind on $(NAME)... $(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./$(NAME) 

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re banner valgrind 