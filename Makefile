# Program name
NAME = cub3D

# Directories
INCDIR = includes
OBJDIR = objs
LIBFTDIR = libft
MLXDIR = minilibx-linux

# Source files
SRCS_MAIN = main.c

SRCS_PARSE = \
	srcs/parse/check_map.c \
	srcs/parse/parse_cub3d.c

SRCS_UTILS = \
	srcs/utils/clear.c \
	srcs/utils/error.c


# SRCS_RAYCAST = \
	# srcs/raycast/raycast.c

# Combine all sources
SRCS = $(SRCS_MAIN) $(SRCS_PARSE) $(SRCS_UTILS) $(SRCS_RAYCAST)

# Object files 
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Includes
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR)

# LDFLAGS
LDFLAGS = -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(LIBFTDIR)/libft.a $(MLXDIR)/libmlx.a $(NAME)
	@echo "$(GREEN)🎉 $(NAME) ready! 🎉$(RESET)"

$(LIBFTDIR)/libft.a:
	@echo "$(CYAN)📚 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory
	@echo "$(GREEN)✓ libft compiled$(RESET)"

$(MLXDIR)/libmlx.a:
	@echo "$(CYAN)🖼️  Building minilibx...$(RESET)"
	@$(MAKE) -C $(MLXDIR) > /dev/null 2>&1
	@echo "$(GREEN)✓ minilibx compiled$(RESET)"

# Règle générique pour la compilation des .o
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling $(notdir $<)...$(RESET)\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)✓ Compiled $(notdir $<)   $(RESET)\n"

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

clean:
	@$(MAKE) -C $(LIBFTDIR) clean --no-print-directory
	@$(MAKE) -C $(MLXDIR) clean > /dev/null 2>&1
	@rm -rf $(OBJDIR)
	@echo "$(CYAN)✓ Object files removed$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(CYAN)✓ $(NAME) removed$(RESET)"

re: fclean all

# Utilities
run: all
	@echo "$(GREEN)🚀 Running $(NAME)...$(RESET)"
	@./$(NAME) maps/valid_map/intra.cub

valgrind: all
	@echo "$(YELLOW)🔍 Running valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME) maps/valid_map/intra.cub

norm:
	@echo "$(YELLOW)📋 Checking norminette...$(RESET)"
	@norminette srcs $(INCDIR) $(LIBFTDIR) main.c 2>&1 | grep -v "OK!" || \
		echo "$(GREEN)✓ All files conform to norminette$(RESET)"

help:
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)  Cub3D Makefile - Available targets$(RESET)"
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"
	@echo "  $(YELLOW)all$(RESET)       - Build $(NAME)"
	@echo "  $(YELLOW)clean$(RESET)     - Remove object files"
	@echo "  $(YELLOW)fclean$(RESET)    - Remove object files and executable"
	@echo "  $(YELLOW)re$(RESET)        - Rebuild everything from scratch"
	@echo "  $(YELLOW)run$(RESET)       - Build and run $(NAME) with intra.cub"
	@echo "  $(YELLOW)valgrind$(RESET)  - Run with valgrind memory checker"
	@echo "  $(YELLOW)norm$(RESET)      - Check norminette compliance"
	@echo "  $(YELLOW)help$(RESET)      - Show this help message"
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"

.PHONY: all clean fclean re run valgrind norm help