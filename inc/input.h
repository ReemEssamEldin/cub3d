/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:04 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 14:24:07 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

# define APPLE 0

# ifdef __APPLE__
#  define APPLE 1
# endif

//key_map.c
void	key_hooks(t_data *cub3d);
int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);

// math.c
bool	touch(float pos_x, float pos_y, t_data *cub3d);

#endif
