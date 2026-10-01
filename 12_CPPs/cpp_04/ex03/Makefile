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

NAME        := interface
CC          := c++
CPPFLAGS    := -Wall -Wextra -Werror -std=c++98 
RM          := rm -rf

#◉───▣───▢◇▢───▣───◉•◉───▣───▢      srcs      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

SRCS	:= AMateria.cpp Character.cpp Cure.cpp ICharacter.cpp Ice.cpp MateriaSource.cpp IMateriaSource.cpp Test.cpp main.cpp
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
	@echo "$(BLACK)                                                 $(RESET)"
	@echo "$(BLACK)Test Optinons:                                             $(RESET)"
	@echo "$(BLACK)  Subject Test:                                          $(RESET)"
	@echo "$(BLACK)   ./interface <0>  ➙ TEST 0: Subject default test code. $(RESET)"
	@echo "$(BLACK)  General Errors:                                          $(RESET)"
	@echo "$(BLACK)   ./interface <1>  ➙ TEST 1: Attempting to instantiate abstract classes (theoretical only).$(RESET)"
	@echo "$(BLACK)   ./interface <2>  ➙ TEST 2: Polymorphism with Base Pointers.$(RESET)"
	@echo "$(BLACK)   ./interface <3>  ➙ TEST 3: Create Unknown Materia.$(RESET)"
	@echo "$(BLACK)   ./interface <4>  ➙ TEST 4: Character Inventory Limit.$(RESET)"
	@echo "$(BLACK)   ./interface <5>  ➙ TEST 5: MateriaSource Limit. $(RESET)"
	@echo "$(BLACK)   ./interface <6>  ➙ TEST 6: Unequip Invalid Index. $(RESET)"
	@echo "$(BLACK)  Cahracters Tests:                                          $(RESET)"
	@echo "$(BLACK)   ./interface <7>  ➙ TEST 7: Basic Character equip/unequip.$(RESET)"
	@echo "$(BLACK)   ./interface <8>  ➙ TEST 8: Character use() behavior.$(RESET)"
	@echo "$(BLACK)   ./interface <9>  ➙ TEST 9: Character edge cases & errors.$(RESET)"
	@echo "$(BLACK)   ./interface <10> ➙ TEST 10: Deep copy & independence.$(RESET)"
	@echo "$(BLACK)  Materia Duel Between Two Characters Tests:                     $(RESET)"
	@echo "$(BLACK)   ./interface <11> ➙ TEST 11: Materia Duel Between Two Characters.$(RESET)"
	@echo "$(BLACK)   ./interface <12> ➙ TEST 12: MateriaSource Full Behavior → dynamic interface (IMateriaSource*).$(RESET)"
	@echo "$(BLACK)   ./interface <13> ➙ TEST 13: MateriaSource Stack Behavior → direct instance (MateriaSource src).$(RESET)"
	@echo "$(BLACK)  Orthodox Canonical Form Tests:                     $(RESET)"
	@echo "$(BLACK)   ./interface <14> ➙ TEST 14: Orthodox Canonical Form - MateriaSource.$(RESET)"
	@echo "$(BLACK)   ./interface <15> ➙ TEST 15: Orthodox Canonical Form - Character.$(RESET)"
	@echo "$(BLACK)   ./interface <16> ➙ TEST 16: Orthodox Canonical Form - AMateria / Ice / Cure.$(RESET)"
	@echo "$(BLACK)                             $(RESET)"

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
		--track-origins=yes ./$(NAME) 0

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re banner instructions valgrind 