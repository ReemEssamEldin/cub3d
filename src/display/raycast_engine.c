/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:36:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 23:52:49 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ray_casting(t_data *cub3d, float cam_x, float *ray_x, float *ray_y);
void	calc_deltadist(t_data *cub3d);
void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y);
void	calc_drawparams(t_data *cub3d);
void	calc_textinfo(t_data *cub3d);

/**
 * Performs ray casting calculation for a single ray in the game
 *
 * @param cub3d    Main game data structure containing player & calculation info
 * @param cam_x    Camera x coordinate in camera space (-1 to 1)
 * @param ray_x    Pointer to store the x coordinate of ray hit position
 * @param ray_y    Pointer to store the y coordinate of ray hit position
 *
 * This function:
 * 1. Defines ray direction based on camera position
 * 2. Sets player position in grid coordinates
 * 3. Calculates delta distances for DDA algorithm
 * 4. Sets up and executes DDA (Digital Differential Analysis)
 * 5. Determines wall hit position
 * 6. Calculates drawing parameters
 * 7. Computes texture information for rendering
 *
 * Used in rendering pipeline for raycasting-based 3D visualization
 */
void	ray_casting(t_data *cub3d, float cam_x, float *ray_x, float *ray_y)
{
	define_raydir(cub3d, cam_x, &cub3d->calc.ray_dirx, &cub3d->calc.ray_diry);
	cub3d->calc.posx = cub3d->player.x / BLOCK;
	cub3d->calc.posy = cub3d->player.y / BLOCK;
	cub3d->calc.map_x = (int)(cub3d->calc.posx);
	cub3d->calc.map_y = (int)(cub3d->calc.posy);
	calc_deltadist(cub3d);
	dda_setup(cub3d);
	dda_execute(cub3d);
	determine_hitpos(cub3d, ray_x, ray_y);
	calc_drawparams(cub3d);
	calc_textinfo(cub3d);
}

/**
 * Calculates delta distances for DDA algorithm in raycasting
 *
 * Delta distance represents the distance the ray has to travel to move from
 * one x-side to the next x-side, or one y-side to the next y-side.
 * If ray direction is 0, delta distance is set to a very large value (1e30)
 * to avoid division by zero.
 *
 * @param cub3d Pointer to main data structure containing raycasting information
 * @return void
 */
void	calc_deltadist(t_data *cub3d)
{
	if (cub3d->calc.ray_dirx == 0)
		cub3d->calc.delta_distx = 1e30;
	else
		cub3d->calc.delta_distx = fabs(1 / cub3d->calc.ray_dirx);
	if (cub3d->calc.ray_diry == 0)
		cub3d->calc.delta_disty = 1e30;
	else
		cub3d->calc.delta_disty = fabs(1 / cub3d->calc.ray_diry);
}

/**
 * Determines the exact hit position of a ray on a wall in a raycasting engine
 * Calculates the perpendicular wall distance and exact x,y coordinates where
 * ray hits
 *
 * @param cub3d    Main data structure containing raycasting calculation variables
 * @param ray_x    Pointer to store the x-coordinate of ray hit position
 * @param ray_y    Pointer to store the y-coordinate of ray hit position
 *
 * The function:
 * 1. Calculates perpendicular wall distance based on which side was hit (x / y)
 * 2. Determines exact hit coordinates based on:
 *    - If x-side was hit: uses map grid x-position with y interpolation
 *    - If y-side was hit: uses map grid y-position with x interpolation
 * 3. Applies small offset (-0.001) to prevent precision errors
 */
void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y)
{
	if (cub3d->calc.side == 0)
		cub3d->calc.wall_dist = cub3d->calc.side_distx
			- cub3d->calc.delta_distx;
	else
		cub3d->calc.wall_dist = cub3d->calc.side_disty
			- cub3d->calc.delta_disty;
	if (cub3d->calc.side == 0)
	{
		*ray_x = cub3d->calc.map_x * BLOCK;
		if (cub3d->calc.step_x > 0)
			*ray_x -= 0.001;
		*ray_y = (cub3d->calc.posy + cub3d->calc.wall_dist
				* cub3d->calc.ray_diry) * BLOCK;
	}
	else
	{
		*ray_x = (cub3d->calc.posx + cub3d->calc.wall_dist
				* cub3d->calc.ray_dirx) * BLOCK;
		*ray_y = cub3d->calc.map_y * BLOCK;
		if (cub3d->calc.step_y > 0)
			*ray_y -= 0.001;
	}
}

/**
 * Calculates drawing parameters for wall rendering in a raycasting engine.
 * Determines the height of the wall line to be drawn and its starting/ending
 * y-coordinates on the screen based on the wall distance.
 *
 * @param cub3d Pointer to main data structure containing calculation parameters
 *              and rendering information
 *
 * The function:
 * 1. Calculates line height based on window height and wall distance
 * 2. Determines where to start and end drawing the wall vertically
 * 3. Ensures drawing bounds stay within screen limits (0 to HEI-1)
 * 4. Stores calculated values in the cub3d structure for later use
 */
void	calc_drawparams(t_data *cub3d)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(HEI / cub3d->calc.wall_dist);
	draw_start = -line_height / 2 + HEI / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEI / 2;
	if (draw_end >= HEI)
		draw_end = HEI - 1;
	cub3d->calc.line_height = line_height;
	cub3d->calc.draw_start = draw_start;
	cub3d->calc.draw_end = draw_end;
}

/**
 * Calculates texture information for raycasting
 *
 * This function determines exact position where the ray hits the wall (wall_x)
 * and which texture should be used based on which side of the wall was hit.
 *
 * The wall_x value is calculated differently depending on whether the ray hit a
 * vertical or horizontal wall side. The texture number (0-3) is determined by:
 * - 0: East-facing wall
 * - 1: West-facing wall
 * - 2: South-facing wall
 * - 3: North-facing wall
 *
 * @param cub3d Pointer to main data struct containing raycasting calculations
 */
void	calc_textinfo(t_data *cub3d)
{
	float	wal_x;
	int		tex_num;

	if (cub3d->calc.side == 0)
		wal_x = cub3d->calc.posy + cub3d->calc.wall_dist * cub3d->calc.ray_diry;
	else
		wal_x = cub3d->calc.posx + cub3d->calc.wall_dist * cub3d->calc.ray_dirx;
	wal_x -= floor(wal_x);
	tex_num = 0;
	if (cub3d->calc.side == 0)
	{
		if (cub3d->calc.step_x > 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (cub3d->calc.step_y > 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	cub3d->calc.wall_x = wal_x;
	cub3d->calc.tex_num = tex_num;
}
