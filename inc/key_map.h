/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:04 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/06 19:56:17 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_MAP_H
# define KEY_MAP_H

# include "cub3d.h"

int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);
//void	move_player(t_player *player);
void	move_player(t_player *player, t_data *cub3d);
void	key_hooks(t_data *cub3d);

// math.c
bool	touch(float px, float py, t_data *cub3d);

#endif
