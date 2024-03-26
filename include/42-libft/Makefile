# Compiler and flags
CC := clang
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR) -g3

# Directories
SRC_DIR := srcs
OBJ_DIR := obj

# Files
SRCS := ft_free.c ft_read_fd.c ft_memset.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_bzero.c ft_atoi.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_tolower.c ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c
BONUS := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

# Output library
NAME := libft.a

# File paths
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS := $(addprefix $(OBJ_DIR)/, $(BONUS:.c=.o))

# Dependencies
DEP := $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)
NUM_FILES := $(words $(SRCS) $(BONUS))
CURRENT_FILE := 1

# Utility functions
define show_progress
	@echo -n "\033[0;34m [$(CURRENT_FILE)/$(NUM_FILES)] \033[0m"
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
endef

# Targets
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Archiving:\033[0m" $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "\033[0;32m [OK] \033[0m" $<
	$(show_progress)
	@($(CC) $(CFLAGS) -MMD -c $< -o $@) 2> /dev/null || (echo "\033[0;31m [ERROR] \033[0m" $< && $(CC) $(CFLAGS) -MMD -c $< -o $@ && exit 1)

-include $(DEP)

bonus: $(BONUS_OBJS)
	@ar rcs $(NAME) $^
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Archiving bonus:\033[0m" $(NAME)

clean:
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
