/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:39 by reldahli          #+#    #+#             */
/*   Updated: 2025/04/29 15:50:52 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* bool	touch(float px, float py, t_data *cub3d)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (cub3d->map_info.map[y][x] == '1')
		return (true);
	return (false);
} */

/* bool	touch(float px, float py, t_data *cub3d)
{
	int	x;
	int	y;

	// Check if position is outside the map boundaries
	if (px < 0 || py < 0)
		return (true);
	x = px / BLOCK;
	y = py / BLOCK;
	// Check if position is outside map array bounds
	if (y >= cub3d->map_info.map_rows || x >= cub3d->map_info.map_cols
		|| y < 0 || x < 0)
		return (true);
	// Check if position has a wall
	if (cub3d->map_info.map[y] && x < (int)ft_strlen(cub3d->map_info.map[y])
		&& cub3d->map_info.map[y][x] == '1')
		return (true);
	return (false);
} */

bool	touch(float px, float py, t_data *cub3d)
{
    int	x;
    int	y;

    // Check if position is outside the map boundaries
    if (px < 0 || py < 0)
        return (true);

    // Adjust px and py slightly to ensure proper rounding for south/east edges
    x = (int)((px + 0.001) / BLOCK);
    y = (int)((py + 0.001) / BLOCK);

    // Check if position is outside map array bounds
    if (y >= cub3d->map_info.map_rows || x >= cub3d->map_info.map_cols
        || y < 0 || x < 0)
        return (true);

    // Check if position has a wall
    if (cub3d->map_info.map[y] && x < (int)ft_strlen(cub3d->map_info.map[y])
        && cub3d->map_info.map[y][x] == '1')
        return (true);

    return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - cub3d->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle); // the correction
	return (fix_dist);
}
