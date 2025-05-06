##------------------------------------------------------------------##
# Variables.

## Preparation, set up MLX
UNAME				= $(shell uname)
ifeq ($(UNAME), Darwin)
	MLXFLAGS 	= -I/usr/X11/include -lmlx -lX11 -L/usr/X11/lib -lXext
else ifeq ($(UNAME), Linux)
	MLXTAR		= minilibx-linux.tgz
	MLXDIR		= ./lib/minilibx-linux/
#	MLXURL		= "https://cdn.intra.42.fr/document/document/30910/minilibx-linux.tgz"
	MLXURL		= https://cdn.intra.42.fr/document/document/31891/minilibx-linux.tgz
	MLXFLAGS 	= -lmlx -lXext -lX11 -lm
	MLXGIT		= https://github.com/42Paris/minilibx-linux.git
endif

## Name(s)
NAME-C3				= cub3d
NAME-LIBFT			= ./lib/libft.a

## Set MLX library based on OS
ifeq ($(UNAME), Linux)
NAME-MLX			= $(MLXDIR)libmlx.a
else
NAME-MLX			=
endif

## Sources & headers & others
SRC-C3				= ./src/cub3d.c \
						./src/utils/utils.c \
						./src/map_loading/map_init.c \
						./src/map_loading/map_header.c \
						./src/map_loading/map_content.c \
						./src/audio/audio.c \
						./src/display/rendering.c \
						./src/display/raycasting.c \
						./src/display/maindisplay.c \
						./src/display/minimap.c \
						./src/display/minimap_utils.c \
						./src/display/draw_floceil.c \
						./src/display/textures.c \
						./src/display/render_utils.c \
						./src/key_mapping/key_map.c \
						./src/key_mapping/math.c \
						./src/init/init.c \
						./src/player_properties/position_direction.c \

HEADER				= ./src/


# Determine dependencies based on OS
ifeq ($(UNAME), Linux)
C3-DEPS = $(SRC-C3) $(NAME-LIBFT) $(NAME-MLX)
else
C3-DEPS = $(SRC-C3) $(NAME-LIBFT)
endif

## Compiler, flags, & other commands
CC 					= cc
CFLAGS 				= -g -Wall -Werror -Wextra -I
RM					= rm -f

## Text colors
RED					=	\033[1;31m
GREEN				=	\033[1;32m
YELLOW				=	\033[1;33m
COLOFF				=	\033[0m

##------------------------------------------------------------------##
# Build rules

all:				$(NAME-MLX) $(NAME-LIBFT) $(NAME-C3)

clean:
					@$(RM) $(NAME-C3)
					@echo "$(RED)cub3d's gone, baby, gone!$(COLOFF)"

fclean:				clean
					@make fclean -C ./lib
					@echo "$(RED)Libft's gone, baby, gone!$(COLOFF)"
					@if [ "$(UNAME)" = "Linux" ]; then \
						$(RM) ./lib/$(MLXTAR); \
						make clean -C ./lib/minilibx-linux; \
						rm -rf $(MLXDIR); \
						echo "$(RED)Minilibx's gone, baby, gone!$(COLOFF)"; \
					fi

re:					fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME-C3) ./assets/maps/small.cub

##------------------------------------------------------------------##
# Targets

ifeq ($(UNAME), Linux)
$(NAME-MLX):
		@if [ ! -d "${MLXDIR}" ]; then \
		echo "$(YELLOW)Getting minilibx.$(COLOFF)"; \
		curl -0 "${MLXURL}" --output ./lib/"${MLXTAR}"; \
		echo "$(YELLOW)Extracting minilibx.$(COLOFF)"; \
		mkdir -p ${MLXDIR}; \
		tar -xzvf ./lib/"${MLXTAR}" -C ./lib/ > /dev/null; \
		rm -rf ${MLXDIR}/.git/; \
		fi
		@echo "$(YELLOW)Making minilibx.$(COLOFF)"
		@make -C ${MLXDIR} -s
		@echo "$(GREEN)Minilibx ready!$(COLOFF)"
endif

$(NAME-LIBFT):
		@echo "$(YELLOW)Making libft.$(COLOFF)"
		@make -C./lib
		@echo "$(GREEN)Libft ready!$(COLOFF)"

$(NAME-C3): $(C3-DEPS)
		@echo "$(YELLOW)Compiling cub3d.$(COLOFF)"
ifeq ($(UNAME), Darwin)
		@$(CC) $(CFLAGS) $(HEADER) $(SRC-C3) $(NAME-LIBFT) $(MLXFLAGS) -o $(NAME-C3)
else
		@$(CC) $(CFLAGS) $(HEADER) $(SRC-C3) $(NAME-LIBFT) $(NAME-MLX) -L${MLXDIR} $(MLXFLAGS) -o $(NAME-C3)
endif
		@echo "$(GREEN)cub3d ready!$(COLOFF)"

##------------------------------------------------------------------##
.PHONY: clean fclean all re test
