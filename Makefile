# Compiler and flags
CC := clang
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(INCLUDE_ALGO) -g3

# Directories
SRC_DIR := srcs
SRC_ALGORITHME := $(SRC_DIR)/algorithme
OBJ_DIR := obj
OBJ_ALGORITHME := $(OBJ_DIR)/algorithme

# Files
SRCS_FILES := main parsing print
SRCS_ALGORITHME := md5 sha256

# Output executable
NAME := ft_ssl

# File paths
SRC := $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRCS_FILES)))
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRCS_FILES)))
SRC_ALGO := $(addprefix $(SRC_ALGORITHME)/, $(addsuffix .c, $(SRCS_ALGORITHME)))
OBJ_ALGO := $(addprefix $(OBJ_ALGORITHME)/, $(addsuffix .o, $(SRCS_ALGORITHME)))

# Dependencies
DEP := $(OBJ:%.o=%.d) $(OBJ_ALGO:%.o=%.d)
NUM_FILES := $(words $(SRCS_FILES) $(SRCS_ALGORITHME))
CURRENT_FILE := 1

# Utility functions
define show_progress
	@echo -n "\033[0;34m [$(CURRENT_FILE)/$(NUM_FILES)] \033[0m"
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
endef

# Targets
all: $(NAME)

$(NAME): $(OBJ) $(OBJ_ALGO)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "\033[0;32m [OK] \033[0m" $<
	$(show_progress)
	@($(CC) $(CFLAGS) -MMD -c $< -o $@) 2> /dev/null || (echo "\033[0;31m [ERROR] \033[0m" $< && $(CC) $(CFLAGS) -MMD -c $< -o $@ && exit 1)

$(OBJ_ALGORITHME)/%.o: $(SRC_ALGORITHME)/%.c
	@mkdir -p $(OBJ_ALGORITHME)
	@echo "\033[0;32m [OK] \033[0m" $<
	$(show_progress)
	@($(CC) $(CFLAGS) -MMD -c $< -o $@) 2> /dev/null || (echo "\033[0;31m [ERROR] \033[0m" $< && $(CC) $(CFLAGS) -MMD -c $< -o $@ && exit 1)

-include $(DEP)

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
