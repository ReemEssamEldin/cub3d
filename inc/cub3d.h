/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:50 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/02 16:43:26 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define BLOCK 10 //what?
# define DIST_EDGE_MOUSE_WRAP 20
# define FOV (PI / 3)


/* # define RED 0xFF0000
# define GRE 0x008000
# define DARK_GREY 0x404040
# define BLU 0x0000FF
# define YEL 0xFFFF00
# define VIO 0x800080
# define WHI 0xFFFFFF
# define BLA 0x000000
# define BROWN 0xA52A2A */

#define WHI		0xFFFFFF  // White
#define BLA		0x000000  // Black
#define RED		0xFF0000  // Red
#define GRE		0x00FF00  // Green
#define BLU		0x0000FF  // Blue
#define YEL		0xFFFF00  // Yellow
#define CYA		0x00FFFF  // Cyan
#define MAG		0xFF00FF  // Magenta
#define ORA		0xFFA500  // Orange
#define PUR		0x800080  // Purple
#define GRY		0x808080  // Grey
#define DGRY	0x404040  // Dark Grey
#define LGRY	0xC0C0C0  // Light Grey
#define BRO		0x8B4513  // Brown
#define PIN		0xFFC0CB  // Pink
#define GOL		0xFFD700  // Gold
#define SIL		0xC0C0C0  // Silver
#define TEA		0x008080  // Teal
#define NAV		0x000080  // Navy Blue
#define SLATE_GREY   0x708090  // Slate Grey
#define DIM_GREY     0x696969  // Dim Grey
#define LIGHT_SLATE  0x778899  // Light Slate Grey
#define GAINSBORO    0xDCDCDC  // Gainsboro
#define DARK_SLATE   0x2F4F4F  // Dark Slate Grey
#define CHARCOAL     0x36454F  // Charcoal
#define ASH_GREY     0xB2BEB5  // Ash Grey
#define PLATINUM     0xE5E4E2  // Platinum
#define SMOKE_GREY   0x738276  // Smoke Grey
#define CLOUD_GREY   0xB0C4DE  // Cloud Grey

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
