FLAGS = -Wall -Werror -Wextra -std=c++98 -pedantic -g3 #-fsanitize=address,undefined
#-Wshadow -Wconversion -Wsign-conversion -Wfloat-equal -Wformat=2 -Wundef -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls
NAME := webserv
MAIN := src/main.cpp
OBJ_DIR := obj

PARSER_HDR := HttpStatusEnum.hpp HttpVersionEnum.hpp Message.hpp Request.hpp Response.hpp HttpError.hpp
PARSER_HDR_DIR := inc/Parser
PARSER_HDR := $(foreach hdr, $(PARSER_HDR), $(PARSER_HDR_DIR)/$(hdr))

PARSER_SRC := Message.cpp Request.cpp Response.cpp HttpError.cpp
PARSER_SRC_DIR := src/Parser
PARSER_SRC := $(foreach src, $(PARSER_SRC), $(PARSER_SRC_DIR)/$(src))

IO_HDR := Client.hpp ConnectionManager.hpp ConnectionSocket.hpp NetworkMessage.hpp
IO_HDR_DIR := inc/IO
IO_HDR := $(foreach hdr, $(IO_HDR), $(IO_HDR_DIR)/$(hdr))

IO_SRC := ConnectionManager.cpp ConnectionSocket.cpp Client.cpp NetworkMessage.cpp
IO_SRC_DIR := src/IO
IO_SRC := $(foreach src, $(IO_SRC), $(IO_SRC_DIR)/$(src))

CFG_HDR := ConfigParser.hpp ConfigParser.tpp ServerConfig.hpp LocationConfig.hpp ConfigValidatorData.hpp ConfigException.hpp 
CFG_HDR_DIR := inc/Config
CFG_HDR := $(foreach hdr, $(CFG_HDR), $(CFG_HDR_DIR)/$(hdr))

CFG_SRC := ConfigParser.cpp ServerConfig.cpp LocationConfig.cpp ConfigException.cpp conf_utils/ConfigParserWrapper.cpp conf_utils/initDirectiveMap.cpp conf_utils/parsersUtilsStr.cpp conf_utils/parsersUtilsVector.cpp conf_utils/parserUtils.cpp validators/checkLocationLogic.cpp validators/checkServerCore.cpp validators/ConfigValidatorData.cpp parsers/parserBodySize.cpp parsers/parserErrorPage.cpp parsers/parserListen.cpp parsers/parserLocation.cpp parsers/parserLocationUtils.cpp parsers/parserMainMethods.cpp parsers/parseVectorDirective.cpp
CFG_SRC_DIR := src/Config
CFG_SRC := $(foreach src, $(CFG_SRC), $(CFG_SRC_DIR)/$(src))

SYS_HDR := Action.hpp GetAction.hpp PostAction.hpp DeleteAction.hpp ErrorAction.hpp RedirectAction.hpp CGIAction.hpp Logger.hpp
SYS_HDR_DIR := inc/System
SYS_HDR := $(foreach hdr, $(SYS_HDR), $(SYS_HDR_DIR)/$(hdr))

SYS_SRC := Action.cpp GetAction.cpp PostAction.cpp DeleteAction.cpp ErrorAction.cpp RedirectAction.cpp CGIAction.cpp Logger.cpp
SYS_SRC_DIR := src/System
SYS_SRC := $(foreach src, $(SYS_SRC), $(SYS_SRC_DIR)/$(src))

BNS_HDR := Session.hpp SessionManager.hpp
BNS_HDR_DIR := inc/Bonus
BNS_HDR := $(foreach hdr, $(BNS_HDR), $(BNS_HDR_DIR)/$(hdr))

BNS_SRC := SessionManager.cpp
BNS_SRC_DIR := src/Bonus
BNS_SRC := $(foreach src, $(BNS_SRC), $(BNS_SRC_DIR)/$(src))

SRC := $(PARSER_SRC) $(SYS_SRC) $(IO_SRC) $(CFG_SRC) $(BNS_SRC)
HDR := $(PARSER_HDR) $(SYS_HDR) $(IO_HDR) $(CFG_HDR) $(BNS_HDR)
HDR_DIRS := $(PARSER_HDR_DIR) $(SYS_HDR_DIR) $(IO_HDR_DIR) $(CFG_HDR_DIR) $(BNS_HDR_DIR)

OBJ_DIR := obj
OBJ := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))
OBJ_MAIN := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN))

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN) $(HDR)
	c++ $(FLAGS) $(foreach hdr_dir, $(HDR_DIRS), -isystem $(hdr_dir)) $(OBJ) $(OBJ_MAIN) -o ${NAME}

fast: #parallel compiling
	make -j

-include $(OBJ:.o=.d) $(OBJ_MAIN:.o=.d)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	c++ $(FLAGS) $(foreach hdr_dir,$(HDR_DIRS),-isystem $(hdr_dir)) -MMD -MP -c $< -o $@

TEST_SRC := testing/main.cpp testing/request.cpp
TEST_OBJ_DIR := testing/obj
TEST_OBJ := $(patsubst testing/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
-include $(TEST_OBJ:.o=.d)
TEST_BIN := testing/testmain

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf ${TEST_OBJ_DIR}

fclean: clean
	@rm -rf ${NAME}
	@rm -rf ${TEST_BIN}

re: fclean all


$(TEST_BIN): $(TEST_OBJ) $(OBJ) testing/catch.hpp
	c++ $(FLAGS) $(TEST_OBJ) $(OBJ) -o $(TEST_BIN)

$(TEST_OBJ_DIR)/%.o: testing/%.cpp
	@mkdir -p $(dir $@)
	c++ $(FLAGS) $(foreach hdr_dir,$(HDR_DIRS),-isystem $(hdr_dir)) -MMD -MP -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

lint:
	cppcheck --enable=all --std=c++98 --quiet --disable=missingInclude src #ignore missingInclude

#◉───▣───▢◇▢───▣───◉•◉───▣───▢    Valgrind    ▢───▣───◉•◉───▣───▢◇▢───▣───◉#
VALGRIND := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --log-file=testing/valgrind_outputs/valgrind_output_$(shell date +%Y%m%d_%H%M%S).log -s

valgrind: all
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──Running Valgrind..──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──$(RESET)"
	@-$(VALGRIND) ./$(NAME) Config/default.conf
	@mkdir -p testing/valgrind_outputs
	@echo "$(CURRENT_COLOR)➵⤐╌╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣── Valgrind completed. Check valgrind_output.log for details. ─╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣╌╌─$(RESET)"

clean_test:
	@./testing/scripts/clean_tests.sh
#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets  ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all fast clean fclean re test valgrind lint valgrind clean_test
