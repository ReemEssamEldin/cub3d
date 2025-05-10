/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:39 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 23:57:46 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Checks if a position collides with walls in the map
 *
 * This function determines if a given position (x,y) intersects with walls (1)
 * in the map or is outside valid map boundaries.
 *
 * @param pos_x X coordinate of the position to check
 * @param pos_y Y coordinate of the position to check
 * @param cub3d Pointer to main data structure containing map information
 *
 * @return true if position collides with a wall or is out of bounds,
 *         false if position is valid and empty
 */
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

/**
 * Attempts to move the player to a new position while checking for collisions
 *
 * @param player Pointer to the player structure containing position data
 * @param dx The change in x-coordinate for the movement attempt
 * @param dy The change in y-coordinate for the movement attempt
 * @param cub3d Pointer to main game data structure containing collision info
 *
 * The function:
 * 1. Calculates new potential position
 * 2. Checks for collision using touch() function with a collision buffer
 * 3. Updates player position only if no collision is detected
 */
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
