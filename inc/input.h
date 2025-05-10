/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:04 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 14:33:01 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

//key_map.c
void	key_hooks(t_data *cub3d);
int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);

// math.c
bool	touch(float pos_x, float pos_y, t_data *cub3d);

#endif
