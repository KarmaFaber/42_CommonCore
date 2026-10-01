#◉────▣───▢◇▢───▣────◉•◉───▣───▢   Colors:   ▢───▣───◉•◉───▣────▢◇▢───▣───◉#
BLACK			= \033[0;30m
RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
BG_BRIGHT_CYAN	= \e[106m
BG_BRIGHT_YELLOW = \e[103m

CURRENT_COLOR	= \033[0;34m
RESET			= \033[0m

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Variables:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

NAME			= exceptions
CC				= c++
CPPFLAGS		= -Wall -Wextra -Werror -std=c++98 
RM				= rm -rf

#◉───▣───▢◇▢───▣───◉•◉───▣───▢      srcs      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

SRCS			= main.cpp Test.cpp Bureaucrat.cpp
OBJS			= $(SRCS:.cpp=.o)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: $(NAME) banner instructions

$(NAME): $(OBJS) 
	@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CURRENT_COLOR)$(NAME) created.$(RESET)"

%.o: %.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(CURRENT_COLOR)All object files have been cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CURRENT_COLOR)$(NAME): have been cleaned.$(RESET)"

re: fclean all

banner:
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

TEST_NUM		= 4
TETS_NUM_MIN	= 1
TETS_NUM_MAX	= 4
MAX_GRADE_ALOW	= 1
MIN_GRADE_ALOW	= 150
TETS_INDEX_DEFAULT = 0
TETS_INDEX_MIN = 1
TETS_INDEX_MAX = 200

instructions:
	@echo "$(BLACK)Test usage: $(RESET)"
	@echo "$(CYAN)./$(NAME) <test_number> <name> <grade> <variable_index>$(RESET)"
	@echo ""
	@echo "$(PURPLE)Valid input ranges:$(RESET)"
	@echo "$(CYAN)<test_number>:$(RESET)    1 - $(TEST_NUM)"
	@echo "$(CYAN)<name>:$(RESET)           alphabetic characters only (A-Z, a-z)"
	@echo "$(CYAN)<grade>:$(RESET)          $(MIN_GRADE_ALOW) - $(MAX_GRADE_ALOW)"
	@echo "$(CYAN)<variable_index>:$(RESET) $(TETS_INDEX_MIN) - $(TETS_INDEX_MAX)"
	@echo ""
	@echo "$(BLACK)Examples:$(RESET)"
	@echo "$(CYAN)Test 1:$(RESET)"
	@echo "$(CYAN)./$(NAME) 1 Belphegor 2 2 $(RESET) $(RED)  ➜  🚨  exception caught $(RESET) "
	@echo "$(CYAN)./$(NAME) 1 Mammon 3 2 $(RESET) $(GREEN)  ➜  ✅  without exception $(RESET)"
	@echo "$(CYAN)Test 2:$(RESET)"
	@echo "$(CYAN)./$(NAME) 2 Astaroth 2 2 $(RESET)  $(RED) ➜  🚨  exception caught $(RESET)"
	@echo "$(CYAN)./$(NAME) 2 Beelzebub 5 2 $(RESET) $(GREEN)  ➜  ✅  without exception $(RESET)"
	@echo "$(CYAN)Test 3:$(RESET)"
	@echo "$(CYAN)./$(NAME) 3 Abaddon 3 5 $(RESET) $(RED)  ➜  🚨  exception caught $(RESET)"
	@echo "$(CYAN)./$(NAME) 3 Asmodeus 10 5 $(RESET) $(GREEN) ➜  ✅  without exception $(RESET)"
	@echo "$(CYAN)Test 4:$(RESET)"
	@echo "$(CYAN)./$(NAME) 4 Leviathan 140 148 $(RESET) $(RED) ➜  🚨  exception caught $(RESET)"
	@echo "$(CYAN)./$(NAME) 4 Belial 140 5 $(RESET) $(GREEN)   ➜  ✅  without exception $(RESET)"
	@echo ""
	@echo "$(RED)[!] Invalid or out-of-range arguments will trigger test exceptions.$(RESET)"
	@echo ""

test: 
	@echo ""
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/+                                ARGC TEST                                     +/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo ""
	-./$(NAME)
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 1 12 -ksdnklsd 2
	@echo "__________________________________________________________________________________"
	@echo ""
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/+                              Running TEST 1:                                 +/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo ""
	-./$(NAME) 1 Azazel -10 2
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 1 Azazel 0 2
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 1 Azazel 2 2
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 1 Azazel 151 2
	@echo ""
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/+                              Running TEST 2:                                 +/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo ""
	-./$(NAME) 2 Vetala 2 2 
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 2 Vetala 5 2 
	@echo ""
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/+                              Running TEST 3:                                 +/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo ""
	-./$(NAME) 3 Pazuzu 5 3
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 3 Pazuzu 3 5
	@echo ""
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/+                              Running TEST 4:                                 +/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo ""
	-./$(NAME) 4 Oni 140 148
	@echo "__________________________________________________________________________________"
	@echo ""
	-./$(NAME) 4 Oni 140 5
	@echo ""
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)+                              END OF TESTS                                     +/$(RESET)"
	@echo "$(BG_BRIGHT_YELLOW)/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++/$(RESET)"
	@echo ""

valgrind: all $(NAME)
	@echo "$(CURRENT_COLOR)Running valgrind on $(NAME)... $(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./$(NAME) 2 Ana 2 2

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re banner instructions test valgrind 