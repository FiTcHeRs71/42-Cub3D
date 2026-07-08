# Program name
NAME = cub3D

# Directories
INCDIR = includes
OBJDIR = objs
LIBFTDIR = libft
SRCDIR = srcs

# OS detection (Linux X11 mlx vs macOS Metal mlx / mms)
UNAME := $(shell uname)

# Source files
SRCS_MAIN = main.c

SRCS_ENEMIES = $(addprefix $(SRCDIR)/enemies/,\
	enemies.c shoot.c enemies_anim.c enemies_draw_utils.c enemies_draw.c enemies_sort.c)

SRCS_GUN = $(addprefix $(SRCDIR)/gun/,\
	gun.c gun_draw.c gun_anim.c crosshair.c)

SRCS_MM = $(addprefix $(SRCDIR)/mini_map/,\
	mini_map.c mini_map_player.c mini_map_utils.c)

SRCS_PARSE = $(addprefix $(SRCDIR)/parse/, \
	check_map.c parse_config.c parse_cub3d.c parse_utils.c utils.c parse_enemies.c)

SRCS_UTILS = $(addprefix $(SRCDIR)/utils/, \
	init.c clear.c error.c window_clear.c clear_2.c \
	platform_linux.c platform_macos.c)

SRCS_WINDOW = $(addprefix $(SRCDIR)/window/, \
	window.c window_utils.c window_thread.c keyboard.c)

SRCS_MOUV = $(addprefix $(SRCDIR)/mouvement/, \
	mouvement.c mouvement_utils.c utils.c)

SRCS_RAYCAST = $(addprefix $(SRCDIR)/raycasting/, \
	raycasting.c raycasting_utils.c)

SRCS_DRAW = $(addprefix $(SRCDIR)/draw/, \
	draw.c draw_floor.c)

SRCS_TEXTURES = $(addprefix $(SRCDIR)/textures/, \
	textures.c load_textures.c)

# Combine all sources
SRCS = $(SRCS_MAIN) $(SRCS_PARSE) $(SRCS_UTILS) $(SRCS_RAYCAST) $(SRCS_DRAW) $(SRCS_WINDOW) $(SRCS_TEXTURES) $(SRCS_MOUV) $(SRCS_MM) $(SRCS_GUN) $(SRCS_ENEMIES)

# Object files 
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC =  cc
CFLAGS = -Wall -Wextra -Werror -O2

# Platform-specific minilibx: dir, built library and link flags
ifeq ($(UNAME), Darwin)
	MLXDIR = minilibx-macos
	MLX_LIB = $(MLXDIR)/libmlx.dylib
	MLX_LDFLAGS = -L$(MLXDIR) -lmlx -Wl,-rpath,@loader_path/$(MLXDIR) \
		-framework AppKit -framework Metal -framework MetalKit -lm
	# mms builds the dylib with a bare install_name; rewrite it to @rpath so
	# the executable can locate it at runtime via -rpath @loader_path.
	MLX_FIX = install_name_tool -id @rpath/libmlx.dylib $(MLX_LIB)
else
	MLXDIR = minilibx-linux
	MLX_LIB = $(MLXDIR)/libmlx.a
	MLX_LDFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz
	MLX_FIX = true
endif

# Includes
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR)

# LDFLAGS
LDFLAGS = -L$(LIBFTDIR) -lft $(MLX_LDFLAGS)

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

define spin
	@printf "$(CYAN)$(1)$(RESET)  "; \
	log=$$(mktemp); \
	( $(2) ) > $$log 2>&1 & pid=$$!; \
	while kill -0 $$pid 2>/dev/null; do \
		for f in ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏; do \
			printf "\b$$f"; sleep 0.08; \
			kill -0 $$pid 2>/dev/null || break; \
		done; \
	done; \
	wait $$pid; rc=$$?; \
	if [ $$rc -eq 0 ]; then \
		printf "\b$(GREEN)✓$(RESET)\n"; rm -f $$log; \
	else \
		printf "\b$(RED)✗$(RESET)\n"; cat $$log; rm -f $$log; exit $$rc; \
	fi
endef

# Rules
all: $(LIBFTDIR)/libft.a $(MLX_LIB) $(NAME)
	@echo "$(GREEN)🎉 $(NAME) ready! 🎉$(RESET)"

$(LIBFTDIR)/libft.a:
	$(call spin,📚 Building libft...,$(MAKE) -C $(LIBFTDIR) --no-print-directory)

$(MLX_LIB):
	$(call spin,🖼️  Building minilibx...,$(MAKE) -C $(MLXDIR) && $(MLX_FIX))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: _compile
_compile:
	$(call spin,🛠  Compiling sources...,$(MAKE) --no-print-directory $(OBJS))

$(NAME): $(OBJS) | _compile
	$(call spin,🔗 Linking $(NAME)...,$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME))

clean:
	@$(MAKE) -C $(LIBFTDIR) clean --no-print-directory
	@$(MAKE) -C $(MLXDIR) clean > /dev/null 2>&1
	@rm -rf $(OBJDIR)
	@echo "$(CYAN)✓ Object files removed$(RESET)"

fclean: clean
	@rm -f $(LIBFTDIR)/libft.a
	@echo "$(CYAN)✓ libft.a removed$(RESET)"
	@rm -f $(NAME)
	@echo "$(CYAN)✓ $(NAME) removed$(RESET)"

re: fclean all

# Utilities
run: all
	@echo "$(GREEN)🚀 Running $(NAME)...$(RESET)"
	@./$(NAME) maps/valid_map/intra.cub

valgrind: all
	@echo "$(YELLOW)🔍 Running valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME) map/valid_map/intra.cub

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