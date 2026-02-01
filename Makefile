# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/18 21:21:03 by asando            #+#    #+#              #
#    Updated: 2026/02/01 15:22:51 by asando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================
# MAIN
#==============================================================================
CC ?= cc
DEBUG ?= 0
BONUS ?= 0
HEADER := include
LIBFT_DIR := ./lib/libft
LIBFT_HEADER := $(LIBFT_DIR)/includes
LIBFT := $(LIBFT_DIR)/libft.a
CFLAGS := -Wall -Wextra -Werror -I$(HEADER) -I$(LIBFT_HEADER)

#==============================================================================
# SOURCES
#==============================================================================
SRC_DIR := ./src
SRC_LEXER_DIR := $(SRC_DIR)/lexer
SRC_PARSE_DIR := $(SRC_DIR)/parse

FILE_LEXER := lexer.c lexer_read.c lexer_tokenizer.c lexer_utils.c
SRC_FILE_LEXER := $(addprefix $(SRC_LEXER_DIR)/, $(FILE_LEXER))

FILE_PARSE := parse.c parse_cmd.c parse_free_function.c
SRC_FILE_PARSE := $(addprefix $(SRC_PARSE_DIR)/, $(FILE_PARSE))

SRCS := $(SRC_FILE_LEXER) $(SRC_FILE_PARSE)

#==============================================================================
# OBJECTS
#==============================================================================
OBJ_DIR := ./obj
OBJ_LEXER_DIR := $(OBJ_DIR)/lexer_obj
OBJ_PARSE_DIR := $(OBJ_DIR)/parse_obj

OBJ_FILE_LEXER := $(SRC_FILE_LEXER:$(SRC_LEXER_DIR)/%.c=$(OBJ_LEXER_DIR)/%.o)
OBJ_FILE_PARSE := $(SRC_FILE_PARSE:$(SRC_PARSE_DIR)/%.c=$(OBJ_PARSE_DIR)/%.o)
OBJS := $(OBJ_FILE_LEXER) $(OBJ_FILE_PARSE)

#==============================================================================
# RULES
#==============================================================================
NAME := minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)

$(LIBFT):
	@$(MAKE) --no-print-directory bonus -C $(LIBFT_DIR)
	@echo "libft.a is compiled"

$(OBJ_LEXER_DIR)/%.o: $(SRC_LEXER_DIR)/%.c | $(OBJ_LEXER_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PARSE_DIR)/%.o: $(SRC_PARSE_DIR)/%.c | $(OBJ_PARSE_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(OBJ_LEXER_DIR): $(OBJ_DIR)
	@mkdir -p $(OBJ_LEXER_DIR)

$(OBJ_PARSE_DIR): $(OBJ_DIR)
	@mkdir -p $(OBJ_PARSE_DIR)

submodules:
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ]; then \
		echo "Initializing Submodules..."; \
		echo "Cloning Libft"; \
		git submodule update --init --recursive; \
	else \
		echo "Submodules are already initialized."; \
	fi

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "Program deleted"
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re submodules
