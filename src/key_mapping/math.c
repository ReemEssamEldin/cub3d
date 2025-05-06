/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:39 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/06 19:51:55 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
