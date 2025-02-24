#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h> //bool
# include <fcntl.h> //open
# include <X11/X.h> //keys
# include <X11/keysym.h> //keys
# include <math.h>
# include "../lib/mlx/mlx.h"
# include "../lib/src/libft/libft.h"
# include "../lib/src/get_next_line/get_next_line.h"
# include "../lib/src/ft_printf/ft_printf.h"

# define WID 1280
# define HEI 720
# define PI 3.14159265359
# define BLOCK 64 //what?

# define RED 0xFF0000
# define GRE 0x008000
# define BLU 0x0000FF
# define YEL 0xFFFF00
# define VIO 0x800080
# define WHI 0xFFFFFF
# define BLA 0x000000

typedef struct s_player
{
	float x;
	float y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool left_rotate;
	bool right_rotate;
}	t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

	t_player	player;
	char		**map;
}	t_data;
#endif