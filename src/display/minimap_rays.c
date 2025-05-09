/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:11:49 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:38:52 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_mmcone(t_data *cub3d);
void	draw_mmray(t_data *cub3d, float ray_dirx, float ray_diry);

/**
 * @brief Draws a cone of rays on the minimap for raycasting visualization
 *
 * This function draws rays on the minimap by:
 * 1. Iterating through screen width pixels
 * 2. Calculating camera x-coordinate for each pixel
 * 3. Defining ray direction vectors
 * 4. Drawing each ray on the minimap
 *
 * @param cub3d Pointer to main program structure containing game data
 *
 * The camera plane x-coordinate is calculated using the formula:
 * cam_x = 2 * pixel_x / screen_width - 1
 * This gives a range from -1 to 1 across the screen width
 */
void	draw_mmcone(t_data *cub3d)
{
	int		i;
	float	cam_x;
	float	ray_dirx;
	float	ray_diry;

	i = 0;
	while (i < WID)
	{
		cam_x = 2.0 * i / (float)WID - 1.0;
		define_raydir(cub3d, cam_x, &ray_dirx, &ray_diry);
		draw_mmray(cub3d, ray_dirx, ray_diry);
		i++;
	}
}

/**
 * @brief Draws a single ray on the minimap
 *
 * This function draws a ray from the player's position in the direction
 * specified by ray_dirx and ray_diry until it either hits a wall or reaches
 * maximum length.
 * The ray's color intensity decreases with distance from the player.
 *
 * @param cub3d    Pointer to the main game data structure
 * @param ray_dirx X component of ray direction vector
 * @param ray_diry Y component of ray direction vector
 *
 * The function:
 * 1. Starts from player position
 * 2. Incrementally draws points along ray direction
 * 3. Blends colors based on distance from player
 * 4. Stops when hitting a wall or reaching maximum ray length
 */
void	draw_mmray(t_data *cub3d, float ray_dirx, float ray_diry)
{
	cub3d->calc.ray_x = cub3d->player.x;
	cub3d->calc.ray_y = cub3d->player.y;
	cub3d->calc.cur_len = 0;
	while (!touch(cub3d->calc.ray_x, cub3d->calc.ray_y, cub3d)
		&& cub3d->calc.cur_len < cub3d->calc.mm_raylen)
	{
		cub3d->calc.ins = 1.0 - (cub3d->calc.cur_len / cub3d->calc.mm_raylen);
		if (cub3d->calc.ins < 0)
			cub3d->calc.ins = 0;
		blend_cols(&cub3d->calc);
		put_pixel(cub3d->calc.ray_x, cub3d->calc.ray_y,
			cub3d->calc.blended_col, cub3d);
		cub3d->calc.ray_x += ray_dirx;
		cub3d->calc.ray_y += ray_diry;
		cub3d->calc.cur_len += 1;
	}
}
