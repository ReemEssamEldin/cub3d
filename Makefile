##------------------------------------------------------------------##
# Variables.

## Preparation, set up MLX
UNAME				= $(shell uname)
ifeq ($(UNAME), Darwin)
	MLXTAR		= minilibx_opengl.tgz
	MLXDIR		= ./lib/minilibx_opengl_20191021/ 
	MLXURL		= "https://cdn.intra.42.fr/document/document/30911/minilibx_opengl.tgz"
	MLXFLAGS 	= -lmlx -framework OpenGL -framework AppKit 
	MLXGIT		= https://github.com/dannywillems/minilibx-mac-osx.git
else ifeq ($(UNAME), Linux)
	MLXTAR		= minilibx-linux.tgz
	MLXDIR		= ./lib/minilibx-linux/
	MLXURL		= "https://cdn.intra.42.fr/document/document/30910/minilibx-linux.tgz"
	MLXFLAGS 	= -lmlx -lXext -lX11 -lm
	MLXGIT		= https://github.com/42Paris/minilibx-linux.git
endif

## Name(s)
NAME-C3				= cub3d
#NAME-BONUS			= so_long_bonus
NAME-LIBFT			= ./lib/libft.a
NAME-MLX			= $(MLXDIR)libmlx.a

## Sources & headers & others
SRC-C3				= ./src/cub3d.c\

HEADER				= ./src/
HEADERFILES			= ./src/cub3d.h

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
					@$(RM) $(NAME-BONUS)
					@echo "$(RED)cub3d's gone, baby, gone!$(COLOFF)"

fclean:				clean
					@make fclean -C ./lib
					@echo "$(RED)Libft's gone, baby, gone!$(COLOFF)"
					@$(RM) ./lib/$(MLXTAR)
					@make clean -C ./lib/minilibx-linux
					@rm -rf $(MLXDIR)
					@echo "$(RED)Minilibx's gone, baby, gone!$(COLOFF)"

re:					fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME-SL)

#re-bonus:			fclean bonus

##------------------------------------------------------------------##
# Targets

$(NAME-MLX):
#		@if [ ! -d "${MLXDIR}" ]; then \
#		echo "$(YELLOW)Cloning minilibx.$(COLOFF)"; \
#		git clone "${MLXGIT}" "${MLXDIR}"; \
#		fi
		@if [ ! -d "${MLXDIR}" ]; then \
		echo "$(YELLOW)Getting minilibx.$(COLOFF)"; \
		curl -0 "${MLXURL}" --output ./lib/"${MLXTAR}"; \
		echo "$(YELLOW)Extracting minilibx.$(COLOFF)"; \
		tar -xzvf ./lib/"${MLXTAR}" -C ./lib/ > /dev/null; \
		fi
		@echo "$(YELLOW)Making minilibx.$(COLOFF)"
		@make -C ${MLXDIR} -s
		@echo "$(GREEN)Minilibx ready!$(COLOFF)"

$(NAME-LIBFT):
		@echo "$(YELLOW)Making libft.$(COLOFF)"
		@make -C./lib
		@echo "$(GREEN)Libft ready!$(COLOFF)"

$(NAME-C3): $(SRC-C3) $(NAME-LIBFT) $(NAME-MLX) $(HEADERFILES)
		@echo "$(YELLOW)Compiling cub3d.$(COLOFF)"
		@$(CC) $(CFLAGS) $(HEADER) $(SRC-C3) $(NAME-LIBFT) $(NAME-MLX) \
		-L${MLXDIR} $(MLXFLAGS) -o $(NAME-C3)
		@echo "$(GREEN)cub3d ready!$(COLOFF)"
		
#$(NAME-BONUS): $(SRC-BONUS) $(NAME-LIBFT) $(NAME-MLX) $(HEADERFILESB)
#		@echo "$(YELLOW)Compiling so long bonus.$(COLOFF)"
#		@$(CC) $(CFLAGS) $(HEADERB) $(SRC-BONUS) $(NAME-LIBFT) $(NAME-MLX) \
#		-L${MLXDIR} $(MLXFLAGS) -o $(NAME-BONUS)
#		@echo "$(GREEN)So Long ready!$(COLOFF)"

##------------------------------------------------------------------##
#.PHONY
.PHONY: clean fclean all re
