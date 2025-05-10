/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:45:47 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 16:03:33 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Checks if a position is a walkable space or player start
 */
int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * @brief Checks if a position is at the map boundary
 */
int	is_boundpos(t_data *cub3d, int i, int j)
{
	return (i == 0 || i == cub3d->map_info.map_rows - 1 || j == 0
		|| j == (int)ft_strlen(cub3d->map_info.map[i]) - 1);
}

/**
 * @brief Validates that surrounding cells don't contain spaces
 */
int	check_neighbours(t_data *cub3d, int i, int j)
{
	if (j >= (int)ft_strlen(cub3d->map_info.map[i - 1])
		|| cub3d->map_info.map[i - 1][j - 1] == ' '
		|| cub3d->map_info.map[i - 1][j] == ' '
		|| cub3d->map_info.map[i - 1][j + 1] == ' ')
		return (0);
	if (cub3d->map_info.map[i][j - 1] == ' '
		|| cub3d->map_info.map[i][j + 1] == ' ')
		return (0);
	if (j >= (int)ft_strlen(cub3d->map_info.map[i + 1])
		|| cub3d->map_info.map[i + 1][j - 1] == ' '
		|| cub3d->map_info.map[i + 1][j] == ' '
		|| cub3d->map_info.map[i + 1][j + 1] == ' ')
		return (0);
	return (1);
}

/**
 * @brief Validates a single position in the map
 */
int	validate_position(t_data *cub3d, int i, int j)
{
	if (!is_walkable(cub3d->map_info.map[i][j]))
		return (1);
	if (is_boundpos(cub3d, i, j))
		return (0);
	return (check_neighbours(cub3d, i, j));
}
