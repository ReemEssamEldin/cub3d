/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_loc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:45:41 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:59:03 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	put_player(t_data *cub3d);
bool	set_position(t_data *cub3d, int x, int y, int *found);
void	set_direction(t_data *cub3d, char pos);

/**
 * @brief Searches for and sets the player's starting position on the map
 *
 * Iterates through the map to find a valid player position marker
 * ('N','S','E','W') and sets the player's initial position and direction based
 * on the found marker.
 *
 * @param cub3d Pointer to the main game data structure
 * @return bool true if exactly one valid player position was found and set,
 *              false if no position or multiple positions were found
 */
bool	put_player(t_data *cub3d)
{
	int		x;
	int		y;
	int		found;
	char	pos;

	found = false;
	y = 0;
	while (y < cub3d->map_info.map_rows && cub3d->map_info.map[y] != NULL)
	{
		x = 0;
		while (x < (int) ft_strlen(cub3d->map_info.map[y]))
		{
			pos = cub3d->map_info.map[y][x];
			if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
				if (!set_position(cub3d, x, y, &found))
					return (false);
			x++;
		}
		y++;
	}
	return (found);
}

/**
 * @brief Sets the initial position and direction of the player in the map
 *
 * @param cub3d    Pointer to main game data structure
 * @param x        X coordinate in map grid
 * @param y        Y coordinate in map grid
 * @param found    Pointer to flag indicating if starting position was found
 *
 * @return true    If position was successfully set
 * @return false   If a starting position was already found (*found is true)
 *
 * Sets player's x,y coordinates to center of map block,
 * sets initial direction based on map character,
 * replaces starting position character with '0' in map.
 */
bool	set_position(t_data *cub3d, int x, int y, int *found)
{
	char	pos;

	pos = cub3d->map_info.map[y][x];
	if (*found)
		return (false);
	cub3d->player.x = (x * BLOCK) + (BLOCK / 2);
	cub3d->player.y = (y * BLOCK) + (BLOCK / 2);
	set_direction(cub3d, pos);
	cub3d->map_info.map[y][x] = '0';
	*found = true;
	return (true);
}

/**
 * Sets the initial direction/angle of the player based on cardinal direction
 *
 * @param cub3d Pointer to the main game data structure
 * @param pos Character representing cardinal direction (N/S/E/W)
 *
 * The angle is set in radians:
 * - N: 3π/2 (270 degrees)
 * - S: π/2 (90 degrees)
 * - E: 0 (0 degrees)
 * - W: π (180 degrees)
 */
void	set_direction(t_data *cub3d, char pos)
{
	if (pos == 'N')
		cub3d->player.angle = 3 * PI / 2;
	else if (pos == 'S')
		cub3d->player.angle = PI / 2;
	else if (pos == 'E')
		cub3d->player.angle = 0;
	else if (pos == 'W')
		cub3d->player.angle = PI;
}
