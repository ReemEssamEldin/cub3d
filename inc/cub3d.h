#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h> //bool
# include <fcntl.h> //open
# include <X11/X.h> //keys
# include <X11/keysym.h> //keys
# include <math.h>
# ifdef __APPLE__
#  include <mlx.h>
# else
#  include "../lib/minilibx-linux/mlx.h"
# endif
# include "../lib/src/libft/libft.h"
# include "../lib/src/get_next_line/get_next_line.h"
# include "../lib/src/ft_printf/ft_printf.h"
# include "structs.h"
# include "map.h"
# include "utils.h"
# include "audio.h"
# include "drawing.h"
# include "key_map.h"
# include "init.h"
# include "player.h" //maybe combine with keymapping?

# define WID 1280
# define HEI 720
# define PI 3.14159265359
# define BLOCK 20 //what?

# define RED 0xFF0000
# define GRE 0x008000
# define BLU 0x0000FF
# define YEL 0xFFFF00
# define VIO 0x800080
# define WHI 0xFFFFFF
# define BLA 0x000000

# define ESC			0xff1b
//# define UP			0xff52
//# define DOWN			0xff54
# define LEFT			0xff51
# define RIGHT			0xff53
# define W				0x0077
# define A				0x0061
# define S				0x0073
# define D				0x0064
//# define Q			0x0071
//# define E			0x0065

enum
{
	KEYPRESS = 2,
	KEYRELEASE = 3,
	MOUSEDOWN = 4,
	MOUSEUP = 5,
	MOUSEMOVE = 6,
	EXPOSE = 12,
	DESTROY = 17
};

int		destroy(t_data *cub3d);
void	check_args(int argc, char *argv);

#endif
