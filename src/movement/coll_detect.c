/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:39 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/08 17:41:41 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	touch(float pos_x, float pos_y, t_data *cub3d)
{
	int	x;
	int	y;

	if (pos_x < 0 || pos_y < 0)
		return (true);
	x = (int)((pos_x + 0.001) / BLOCK);
	y = (int)((pos_y + 0.001) / BLOCK);
	if (y >= cub3d->map_info.map_rows || x >= cub3d->map_info.map_cols
		|| y < 0 || x < 0)
		return (true);
	if (cub3d->map_info.map[y] && x < (int)ft_strlen(cub3d->map_info.map[y])
		&& cub3d->map_info.map[y][x] == '1')
		return (true);
	return (false);
}

void	try_move(t_player *player, float dx, float dy, t_data *cub3d)
{
	float	new_x;
	float	new_y;

	new_x = player->x + dx;
	new_y = player->y + dy;
	if (!touch(new_x + cub3d->move.collision_buffer * cub3d->move.dir_x,
			new_y + cub3d->move.collision_buffer * cub3d->move.dir_y, cub3d))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
