# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asando <asando@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/18 21:21:03 by asando            #+#    #+#              #
#    Updated: 2026/03/16 16:46:57 by asando           ###   ########.fr        #
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
SRC_EXPANSION_DIR := $(SRC_DIR)/expansion
SRC_EXECUTION_DIR := $(SRC_DIR)/execution
SRC_MINISHELL_MAIN_DIR := $(SRC_DIR)/minishell_main

FILE_LEXER := lexer.c lexer_read.c lexer_tokenizer.c lexer_utils.c
SRC_FILE_LEXER := $(addprefix $(SRC_LEXER_DIR)/, $(FILE_LEXER))

FILE_PARSE := parse.c parse_cmd.c parse_free_function.c parse_utils.c
SRC_FILE_PARSE := $(addprefix $(SRC_PARSE_DIR)/, $(FILE_PARSE))

FILE_EXPANSION := expansion.c expansion_case.c expansion_handle_quote.c \
				  expansion_utils.c
SRC_FILE_EXPANSION := $(addprefix $(SRC_EXPANSION_DIR)/, $(FILE_EXPANSION))

FILE_EXECUTION := execution_executor.c execution_child_process.c \
				  execution_heredoc.c execution_path_finder.c \
				  execution_process_utils.c execution_parent_process.c \
				  execution_pipe.c execution_redirection.c
SRC_FILE_EXECUTION := $(addprefix $(SRC_EXECUTION_DIR)/, $(FILE_EXECUTION))

FILE_MINISHELL_MAIN := main_loop.c signal.c
SRC_FILE_MINISHELL_MAIN := $(addprefix $(SRC_MINISHELL_MAIN_DIR)/, \
						   $(FILE_MINISHELL_MAIN))

SRCS := $(SRC_FILE_LEXER) $(SRC_FILE_PARSE) $(SRC_FILE_EXPANSION) \
		$(SRC_FILE_EXECUTION) $(SRC_FILE_MINISHELL_MAIN)

#==============================================================================
# OBJECTS
#==============================================================================
OBJ_DIR := ./obj

OBJ_LEXER_DIR := $(OBJ_DIR)/lexer_obj
OBJ_PARSE_DIR := $(OBJ_DIR)/parse_obj
OBJ_EXPANSION_DIR := $(OBJ_DIR)/expansion_obj
OBJ_EXECUTION_DIR := $(OBJ_DIR)/execution_obj
OBJ_MINISHELL_MAIN_DIR := $(OBJ_DIR)/minishell_main_obj

OBJ_SUBDIR := $(OBJ_LEXER_DIR) $(OBJ_PARSE_DIR) $(OBJ_EXPANSION_DIR) \
			  $(OBJ_EXECUTION_DIR) $(OBJ_MINISHELL_MAIN_DIR)

OBJ_FILE_LEXER := $(SRC_FILE_LEXER:$(SRC_LEXER_DIR)/%.c=$(OBJ_LEXER_DIR)/%.o)
OBJ_FILE_PARSE := $(SRC_FILE_PARSE:$(SRC_PARSE_DIR)/%.c=$(OBJ_PARSE_DIR)/%.o)
OBJ_FILE_EXPANSION := $(SRC_FILE_EXPANSION:$(SRC_EXPANSION_DIR)/%.c=\
					  $(OBJ_EXPANSION_DIR)/%.o)
OBJ_FILE_EXECUTION := $(SRC_FILE_EXECUTION:$(SRC_EXECUTION_DIR)/%.c=\
					  $(OBJ_EXECUTION_DIR)/%.o)
OBJ_FILE_MINISHELL_MAIN := $(SRC_FILE_MINISHELL_MAIN:$(SRC_MINISHELL_MAIN_DIR)/\
						   %.c=$(OBJ_MINISHELL_MAIN_DIR)/%.o)
OBJS := $(OBJ_FILE_LEXER) $(OBJ_FILE_PARSE) $(OBJ_FILE_EXPANSION) \
		$(OBJ_FILE_EXECUTION) $(OBJ_FILE_MINISHELL_MAIN)

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

$(OBJ_EXPANSION_DIR)/%.o: $(SRC_EXPANSION_DIR)/%.c | $(OBJ_EXPANSION_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_EXECUTION_DIR)/%.o: $(SRC_EXECUTION_DIR)/%.c | $(OBJ_EXECUTION_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_MINISHELL_MAIN_DIR)/%.o: $(SRC_MINISHELL_MAIN_DIR)/%.c | \
	$(OBJ_MINISHELL_MAIN_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(OBJ_SUBDIR): | $(OBJ_DIR)
	@mkdir -p $@

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
