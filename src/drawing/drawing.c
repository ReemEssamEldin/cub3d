/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/06 19:05:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cub3d.h"

/*
 * put_pixel - Puts a pixel of a specified color
 at a given position in the image.
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 * @color: The color of the pixel in RGB format.
 * @cub3d: A pointer to the t_data structure containing image data.
 *
 * This function sets the color of the pixel at the specified (x, y) coordinates
 * in the image represented by the t_data structure. If the coordinates are
 * outside the bounds of the image,
 * the function returns without making any changes.
 *
 * The color is specified in RGB format, and the function extracts the individual
 * red, green, and blue components to store them in the image data.
 */

void	put_pixel(int x, int y, int color, t_data *cub3d)
{
	int	idx;

	if (x >= WID || y >= HEI || x < 0 || y < 0)
		return ;
	idx = y * cub3d->line_len + x * cub3d->bpp / 8;
	cub3d->addr[idx] = color & 0xFF;
	cub3d->addr[idx + 1] = (color >> 8) & 0xFF;
	cub3d->addr[idx + 2] = (color >> 16) & 0xFF;
}

/* void ray_casting(t_data *cub3d, float start_x, float *ray_x, float *ray_y)
{
    float dir_x = cos(start_x);
    float dir_y = sin(start_x);

    // Ray starting position (player position)
    float pos_x = cub3d->player.x / BLOCK;
    float pos_y = cub3d->player.y / BLOCK;
    
    // Current map cell the ray is in
    int map_x = (int)(pos_x);
    int map_y = (int)(pos_y);
    
    // Length of ray from current position to next x or y-side
    float side_dist_x;
    float side_dist_y;
    
    // Length of ray from one x or y-side to next x or y-side
    float delta_dist_x = (dir_x == 0) ? 1e30 : fabs(1 / dir_x);
    float delta_dist_y = (dir_y == 0) ? 1e30 : fabs(1 / dir_y);
    
    // Direction to step in x or y direction (either +1 or -1)
    int step_x;
    int step_y;
    
    // Calculate step and initial side_dist
    if (dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (pos_x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
    }
    
    if (dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (pos_y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
    }
    
    // Variable to track which side of the wall was hit (0 = NS wall, 1 = EW wall)
    int side;
    int hit = 0;
    
    // Perform DDA
    while (hit == 0)
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
            hit = 1;
        }
    }
    
    // Calculate exact hit position
    float wall_dist;
    if (side == 0)
        wall_dist = side_dist_x - delta_dist_x;
    else
        wall_dist = side_dist_y - delta_dist_y;
    
    // Calculate exact hit coordinates
    if (side == 0)
    {
        *ray_x = map_x * BLOCK;
        if (step_x > 0)
            *ray_x -= 0.001; // Adjust for edge case
        *ray_y = (pos_y + wall_dist * dir_y) * BLOCK;
    }
    else
    {
        *ray_x = (pos_x + wall_dist * dir_x) * BLOCK;
        *ray_y = map_y * BLOCK;
        if (step_y > 0)
            *ray_y -= 0.001; // Adjust for edge case
    }
}
 */

/* void ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y)
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
	 
	 // Length of ray from current position to next x or y-side
	 float side_dist_x;
	 float side_dist_y;
	 
	 // Length of ray from one x or y-side to next x or y-side
	 float delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
	 float delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
	 
	 // Direction to step in x or y direction (either +1 or -1)
	 int step_x;
	 int step_y;
	 
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
	 
	 // Variable to track which side of the wall was hit (0 = NS wall, 1 = EW wall)
	 int side;
	 int hit = 0;
	 
	 // Perform DDA
	 while (hit == 0)
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
			 hit = 1;
		 }
	 }
	 
	 // Calculate exact hit position
	 float wall_dist;
	 if (side == 0)
		 wall_dist = side_dist_x - delta_dist_x;
	 else
		 wall_dist = side_dist_y - delta_dist_y;
	 
	 // Calculate exact hit coordinates
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
	 
	 // Store additional data in the cub3d structure if needed
	 // cub3d->calc.wall_dist = wall_dist;
	 // cub3d->calc.side = side;
 } */

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

/* void	draw_md(t_player *player, t_data *cub3d, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		col_wall;
	int		col_ceil;
	int		col_floo;

	//ray_marching(cub3d, start_x, &ray_x, &ray_y);
	//ray_casting(cub3d, start_x, &ray_x, &ray_y);
	(void)start_x;
	float camera_x = 2.0 * i / (float)WID - 1.0;  // x-coordinate in camera space
	ray_casting(cub3d, camera_x, &ray_x, &ray_y);
	// Handle first-person perspective
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d);
	//dist = distance(ray_x - player->x, ray_y - player->y);
	height = (BLOCK / dist) * (WID / 2);
	start_y = (HEI - height) / 2;
	end = start_y + height;
	col_wall = GRE;
	col_ceil = rgb_to_colour(cub3d->map_info.ce_col, cub3d);
	col_floo = rgb_to_colour(cub3d->map_info.fl_col, cub3d);
	draw_line(0, start_y, col_ceil, cub3d, i);
	draw_line(start_y, end, col_wall, cub3d, i);
	draw_line(end, HEI, col_floo, cub3d, i);
} */

void draw_md(t_player *player, t_data *cub3d, float start_x, int i)
{
	float ray_x;
	float ray_y;
	//t_ray_hit hit;
	int col_wall;
	int col_ceil;
	int col_floo;

	(void)start_x;
	float camera_x = 2.0 * i / (float)WID - 1.0;

	// Cast ray and get all hit information
	ray_casting(cub3d, camera_x, &ray_x, &ray_y);

	// Select wall color based on side and direction
	//if (hit.side == 0)
	if (cub3d->calc.side == 0)
	{
		if (cub3d->calc.map_x > player->x / BLOCK)
			col_wall = RED;  // East
		else
			col_wall = GRE;  // West
	}
	else
	{
		if (cub3d->calc.map_y > player->y / BLOCK) 
			col_wall = BLU;  // South
		else
			col_wall = YEL;  // North
	}

	// Make y-sides darker
	if (cub3d->calc.side == 1)
		col_wall = (col_wall >> 1) & 0x7F7F7F;  // Divide RGB components by 2

	// Get ceiling and floor colors
	col_ceil = rgb_to_colour(cub3d->map_info.ce_col, cub3d);
	col_floo = rgb_to_colour(cub3d->map_info.fl_col, cub3d);

	// Draw ceiling, wall and floor
	draw_line(0, cub3d->calc.draw_start, col_ceil, cub3d, i);
	draw_line(cub3d->calc.draw_start, cub3d->calc.draw_end, col_wall, cub3d, i);
	draw_line(cub3d->calc.draw_end, HEI, col_floo, cub3d, i);
}

void	draw_line(int top, int bot, int colour, t_data *cub3d, int i)
{
	(void) i;
	while (top < bot)
	{
		put_pixel(i, top, colour, cub3d);
		top++;
	}
}

/* int	render(t_data *cub3d)
{
	float	fraction;
	float	start_x;
	int		i;
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	max_ray_length;
	float	current_length;
	float	ray_angles[WID]; // Store ray angles for later use
	move_player(&cub3d->player, cub3d);
	clear_image(cub3d);
	// Calculate and store ray angles
	fraction = PI / 3 / WID;
	start_x = cub3d->player.angle - PI / 6;
	i = 0;
	while (i < WID)
	{
		ray_angles[i] = start_x;
		draw_maindisplay(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	// Draw minimap
	draw_map(cub3d);
	// Redraw rays on top of minimap
	max_ray_length = BLOCK * 3;
	i = 0;
	while (i < WID)
	{
		cos_angle = cos(ray_angles[i]);
		sin_angle = sin(ray_angles[i]);
		ray_x = cub3d->player.x;
		ray_y = cub3d->player.y;
		current_length = 0;
		while (!touch(ray_x, ray_y, cub3d) && current_length < max_ray_length)
		{
			// Calculate intensity based on distance
			float intensity = 1.0 - (current_length / max_ray_length);
			if (intensity < 0) intensity = 0;
	
			// Adjust the base color (WHITE) to create a gradient
			int base_color = WHI;
			int r = ((base_color >> 16) & 0xFF) * intensity;
			int g = ((base_color >> 8) & 0xFF) * intensity;
			int b = (base_color & 0xFF) * intensity;
			int gradient_color = (r << 16) | (g << 8) | b;
	
			// Background color of the minimap
			int background_color = BLA;
	
			// Blend the gradient color with the background color
			int blended_r = ((background_color >> 16) & 0xFF) * (1.0 - intensity) +
							((gradient_color >> 16) & 0xFF) * intensity;
			int blended_g = ((background_color >> 8) & 0xFF) * (1.0 - intensity) +
							((gradient_color >> 8) & 0xFF) * intensity;
			int blended_b = (background_color & 0xFF) * (1.0 - intensity) +
							(gradient_color & 0xFF) * intensity;
			int blended_color = (blended_r << 16) | (blended_g << 8) | blended_b;
	
			// Draw the pixel with the blended color
			put_pixel(ray_x, ray_y, blended_color, cub3d);

			ray_x += cos_angle;
			ray_y += sin_angle;
			current_length += 1;
		}
		i++;
	}
	draw_filled_square(cub3d->player.x - (BLOCK/4), cub3d->player.y - (BLOCK/4), BLOCK/2, BLU, cub3d);
	//draw_filled_circle(cub3d->player.x - (BLOCK/4), cub3d->player.y - (BLOCK/4), BLOCK/4, BLU, cub3d);
	//put_pixel(cub3d->player.x, cub3d->player.y, BLU, cub3d);

	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img_ptr, 0, 0);
	return (0);
} */

/* void	draw_map(t_data *cub3d)
{
	char	**map;
	int		map_width;
	int		map_height;
	int		wall_color;
	int		bg_color;
	int		space_color;
	int		map_padding;
	int		len;

	map = cub3d->map_info.map;
	map_height = 0;
	map_width = 0;
	map_padding = 1;
	while (map[map_height])
	{
		len = 0;
		while (map[map_height][len])
			len++;
		if (len > map_width)
			map_width = len;
		map_height++;
	}
	map_width += map_padding;
	map_height += map_padding;
	bg_color = BLA;
	wall_color = BRO;
	space_color = BLA;
	// Fill background
	for (int y = 0; y < map_height * BLOCK; y++)
		for (int x = 0; x < map_width * BLOCK; x++)
			put_pixel(x, y, bg_color, cub3d);
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_filled_square(x * BLOCK, y * BLOCK, BLOCK,
					wall_color, cub3d);
			else if (map[y][x] == '0')
				draw_filled_square(x * BLOCK, y * BLOCK, BLOCK,
					space_color, cub3d);
} */

void	clear_image(t_data *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEI)
	{
		x = 0;
		while (x < WID)
		{
			put_pixel(x, y, 0, cub3d);
			x++;
		}
		y++;
	}
}
