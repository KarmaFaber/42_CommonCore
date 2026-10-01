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

NAME        := exceptions
CC          := c++
CPPFLAGS    := -Wall -Wextra -Werror -std=c++98 
RM          := rm -rf

#◉───▣───▢◇▢───▣───◉•◉───▣───▢      srcs      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

SRCS	:= main.cpp Bureaucrat.cpp AForm.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp Test.cpp
OBJS	:= $(SRCS:.cpp=.o)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: $(NAME) banner instructions

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

instructions:
	@echo "$(BLACK)Test Use: ./$(NAME) <n>$(RESET)"
	@echo "$(GREEN)                       $(RESET)"

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
		--track-origins=yes --track-fds=yes ./$(NAME) 1

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re banner instructions valgrind 