/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:41:07 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:49:36 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	dda_setup(t_data *cub3d);
void	dda_execute(t_data *cub3d);

/**
 * Sets up the DDA (Digital Differential Analysis) parameters for raycasting
 *
 * Calculates step and side distance values for both X and Y directions based on
 * the ray direction. These values are used in the DDA algorithm to determine
 * which grid cell the ray intersects with.
 *
 * For X direction:
 * - If ray points left (negative), step_x = -1 and calculate side distance from
 * 		current position
 * - If ray points right (positive), step_x = 1 and calculate side distance to
 * 		next grid line
 *
 * For Y direction:
 * - If ray points up (negative), step_y = -1 and calculate side distance from
 * 		current position
 * - If ray points down (positive), step_y = 1 and calculate side distance to
 * 		next grid line
 *
 * @param cub3d Pointer to main data structure containing raycasting calculation
 * 				variables
 */
void	dda_setup(t_data *cub3d)
{
	if (cub3d->calc.ray_dirx < 0)
	{
		cub3d->calc.step_x = -1;
		cub3d->calc.side_distx = (cub3d->calc.posx - cub3d->calc.map_x)
			* cub3d->calc.delta_distx;
	}
	else
	{
		cub3d->calc.step_x = 1;
		cub3d->calc.side_distx = (cub3d->calc.map_x + 1.0 - cub3d->calc.posx)
			* cub3d->calc.delta_distx;
	}
	if (cub3d->calc.ray_diry < 0)
	{
		cub3d->calc.step_y = -1;
		cub3d->calc.side_disty = (cub3d->calc.posy - cub3d->calc.map_y)
			* cub3d->calc.delta_disty;
	}
	else
	{
		cub3d->calc.step_y = 1;
		cub3d->calc.side_disty = (cub3d->calc.map_y + 1.0 - cub3d->calc.posy)
			* cub3d->calc.delta_disty;
	}
}

/**
 * @brief Executes the DDA (Digital Differential Analysis) algorithm for
 * 			raycasting
 *
 * This function implements the DDA algorithm to find wall intersections in a 2D
 * map. It iteratively steps through the map grid either horizontally or
 * vertically (depending on which distance is shorter) until a wall ('1') is hit
 * or map bounds are exceeded.
 *
 * The algorithm updates:
 * - side_distx/y: Distance to next horizontal/vertical grid line
 * - map_x/y: Current grid position
 * - side: Which wall face was hit (0 for x-side, 1 for y-side)
 *
 * @param cub3d Pointer to main data structure containing map & calculation info
 */
void	dda_execute(t_data *cub3d)
{
	int	hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		if (cub3d->calc.side_distx < cub3d->calc.side_disty)
		{
			cub3d->calc.side_distx += cub3d->calc.delta_distx;
			cub3d->calc.map_x += cub3d->calc.step_x;
			cub3d->calc.side = 0;
		}
		else
		{
			cub3d->calc.side_disty += cub3d->calc.delta_disty;
			cub3d->calc.map_y += cub3d->calc.step_y;
			cub3d->calc.side = 1;
		}
		if (cub3d->calc.map_y < 0 || cub3d->calc.map_x < 0
			|| cub3d->calc.map_y >= cub3d->map_info.map_rows
			|| cub3d->calc.map_x >= (int)ft_strlen
			(cub3d->map_info.map[cub3d->calc.map_y])
			|| cub3d->map_info.map[cub3d->calc.map_y][cub3d->calc.map_x] == '1')
			hit_flag = 1;
	}
}
