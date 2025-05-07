/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:50 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/07 21:57:10 by hsetyamu         ###   ########.fr       */
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
# include "defines.h"
# include "structs.h"
# include "map.h"
# include "utils.h"
# include "audio.h"
# include "display.h"
# include "key_map.h"
# include "init.h"
# include "player.h" //maybe combine with keymapping?

// enum
// {
// 	KEYPRESS = 2,
// 	KEYRELEASE = 3,
// 	MOUSEDOWN = 4,
// 	MOUSEUP = 5,
// 	MOUSEMOVE = 6,
// 	EXPOSE = 12,
// 	DESTROY = 17
// };

//cub3d.c
int		destroy(t_data *cub3d);
void	check_args(int argc, char *argv);

#endif
