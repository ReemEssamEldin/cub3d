/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/06 19:29:39 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y)
{
	// Camera direction vector (where the player is looking)
	float dir_x = cos(cub3d->player.angle);
	float dir_y = sin(cub3d->player.angle);

	// Camera plane perpendicular to direction vector (FOV control)
	float plane_x = -dir_y * 0.66; // FOV of ~66 degrees
	float plane_y = dir_x * 0.66;  // Perpendicular to direction
	
	// Calculate ray direction using camera plane
	float ray_dir_x = dir_x + plane_x * camera_x;
	float ray_dir_y = dir_y + plane_y * camera_x;

	// Ray starting position (player position)
	float pos_x = cub3d->player.x / BLOCK;
	float pos_y = cub3d->player.y / BLOCK;

	// Current map cell the ray is in
	int map_x = (int)(pos_x);
	int map_y = (int)(pos_y);
	
	// Length of ray from one x or y-side to next x or y-side
	float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
	
	// Direction to step in x or y direction (either +1 or -1)
	int step_x;
	int step_y;
	
	// Length of ray from current position to next x or y-side
	float side_dist_x;
	float side_dist_y;
	
	// Calculate step and initial side_dist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
	}

	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
	}

	// Perform DDA
	int hit_flag = 0;
	int side = 0;  // 0 = NS wall, 1 = EW wall
	
	while (hit_flag == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		
		// Check if ray has hit a wall
		if (map_y < 0 || map_x < 0 || map_y >= cub3d->map_info.map_rows || 
			map_x >= (int)ft_strlen(cub3d->map_info.map[map_y]) || 
			cub3d->map_info.map[map_y][map_x] == '1')
		{
			hit_flag = 1;
		}
	}
	
	// Calculate exact hit position
	float wall_dist;
	if (side == 0)
		wall_dist = side_dist_x - delta_dist_x;
	else
		wall_dist = side_dist_y - delta_dist_y;

	// Calculate exact hit coordinates for minimap
	if (side == 0)
	{
		*ray_x = map_x * BLOCK;
		if (step_x > 0)
			*ray_x -= 0.001; // Adjust for edge case
		*ray_y = (pos_y + wall_dist * ray_dir_y) * BLOCK;
	 }
	 else
	 {
		*ray_x = (pos_x + wall_dist * ray_dir_x) * BLOCK;
		*ray_y = map_y * BLOCK;
		if (step_y > 0)
			*ray_y -= 0.001; // Adjust for edge case
	}
	
	// Calculate wall height and drawing bounds
	int line_height = (int)(HEI / wall_dist);
	int draw_start = -line_height / 2 + HEI / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + HEI / 2;
	if (draw_end >= HEI)
		draw_end = HEI - 1;
	
	// Calculate where exactly the wall was hit
	float wall_x;
	if (side == 0)
		wall_x = pos_y + wall_dist * ray_dir_y;
	else
		wall_x = pos_x + wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	
	// Determine which texture to use
	int tex_num = 0; // Default to north
	if (side == 0)
	{
		tex_num = (step_x > 0) ? 0 : 1;  // 0 = north, 1 = south
	}
	else
	{
		 tex_num = (step_y > 0) ? 2 : 3;  // 2 = east, 3 = west
	}
	
	// Fill the ray hit structure
	cub3d->calc.wall_dist = wall_dist;
	cub3d->calc.map_x = map_x;
	cub3d->calc.map_y = map_y;
	cub3d->calc.side = side;
	cub3d->calc.wall_x = wall_x;
	cub3d->calc.tex_num = tex_num;
	cub3d->calc.line_height = line_height;
	cub3d->calc.draw_start = draw_start;
	cub3d->calc.draw_end = draw_end;
}




