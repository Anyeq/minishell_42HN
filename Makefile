CC ?= cc
DEBUG ?= 0
BONUS ?= 0
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := ./lib/libft

$(LIBFT):
	@$(MAKE) --no-print-directory bonus -C $(LIBFT_DIR)
	@echo "libft.a is compiled"

submodules:
	@if [ ! -f "$(LIBFT_DIR)/Makefile" ]; then \
		echo "Initializing Submodules..."; \
		echo "Cloning Libft"; \
		git submodule update --init --recursive; \
	else \
		echo "Submodules are already initialized."; \
	fi
