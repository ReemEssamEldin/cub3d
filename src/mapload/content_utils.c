/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:45:47 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/10 22:37:17 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * @brief Determines if a character represents a walkable tile on the map
 *
 * @param c The character to check
 * @return int 1 (true) if the character represents a walkable tile, 0 (false) 
 * otherwise
 */
int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * @brief Checks if a position (i, j) is on the boundary of the map
 *
 * This function determines whether the given coordinates represent a position
 * on the outer edge of the map. It checks if the position is on the first row,
 * last row, first column, or last column of its row.
 *
 * @param cub3d Pointer to the main data structure containing map information
 * @param i     Row index to check
 * @param j     Column index to check
 * 
 * @return int  Returns 1 (true) if the position is on a boundary, 0 (false) 
 * otherwise
 */
int	is_boundpos(t_data *cub3d, int i, int j)
{
	return (i == 0 || i == cub3d->map_info.map_rows - 1 || j == 0
		|| j == (int)ft_strlen(cub3d->map_info.map[i]) - 1);
}

/**
 * @brief Checks if all 8 neighboring cells around position (i,j) are valid
 *
 * This function examines all 8 cells surrounding the position (i,j) in the map
 * to ensure none of them are spaces (' ') or out of bounds. It checks the
 * cells above, below, to the sides, and diagonally adjacent to the given 
 * position.
 *
 * @param cub3d  Pointer to the main data structure
 * @param i      Row index in the map
 * @param j      Column index in the map
 *
 * @return 1 if all neighboring cells are valid, 0 if any neighbor is a space or
 * out of bounds
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
 * @brief Validates if a position on the map is valid for player movement
 *
 * This function checks if the position at coordinates (i, j) is valid by:
 * 1. Checking if the position is walkable
 * 2. Checking if the position is at a boundary
 * 3. Checking the neighboring positions
 *
 * @param cub3d Pointer to the main data structure
 * @param i Row index in the map
 * @param j Column index in the map
 *
 * @return 1 if the position is invalid, 0 if the position is valid
 */
int	validate_position(t_data *cub3d, int i, int j)
{
	if (!is_walkable(cub3d->map_info.map[i][j]))
		return (1);
	if (is_boundpos(cub3d, i, j))
		return (0);
	return (check_neighbours(cub3d, i, j));
}
