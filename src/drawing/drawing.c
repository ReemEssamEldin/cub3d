/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/30 12:19:48 by hsetyamu         ###   ########.fr       */
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

void	cast_ray(t_data *cub3d, float start_x, float *ray_x, float *ray_y)
{
    float	cos_angle;
    float	sin_angle;
    float	max_ray_length = BLOCK * 100;
    float	current_length;

    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    // *ray_x = cub3d->player.x + BLOCK / 4;  // Start from middle of player square
    // *ray_y = cub3d->player.y + BLOCK / 4;  // Start from middle of player square
	*ray_x = cub3d->player.x;
    *ray_y = cub3d->player.y;
    max_ray_length = BLOCK * 100;      // Limit ray to 5 blocks length
    current_length = 0;

    while (!touch(*ray_x, *ray_y, cub3d) && current_length < max_ray_length)
    //while (!touch(*ray_x, *ray_y, cub3d))
	{
        put_pixel(*ray_x, *ray_y, RED, cub3d); // This line handles rays
        *ray_x += cos_angle;
        *ray_y += sin_angle;
        current_length += 1;
    }
}

void	draw_line(t_player *player, t_data *cub3d, float start_x, int i)
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

	cast_ray(cub3d, start_x, &ray_x, &ray_y);
	// Handle first-person perspective
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d);
	height = (BLOCK / dist) * (WID / 2);
	start_y = (HEI - height) / 2;
	end = start_y + height;
	col_wall = GRE;
	col_ceil = rgb_to_colour(cub3d->map_info.ce_col);
	col_floo = rgb_to_colour(cub3d->map_info.fl_col);
	draw_maindisplay(0, start_y, col_ceil, cub3d, i);
	draw_maindisplay(start_y, end, col_wall, cub3d, i);
	draw_maindisplay(end, HEI, col_floo, cub3d, i);
	
	/* //--------------------------------------------------------------------------
	// Define variables for texture mapping
	int tex_num = 0;        // Which texture to use (N,S,E,W)
	double wall_x = 0;      // Where exactly the ray hit the wall
	int tex_x;              // X coordinate on the texture

	// Determine which wall was hit and exact position
	// This requires knowing if we hit a vertical or horizontal wall edge
	int map_x = (int)(ray_x / BLOCK);
	//int map_y = (int)(ray_y / BLOCK);

	// Check if we hit a vertical or horizontal wall
	if (fabs(ray_x - map_x * BLOCK) < 0.01 || fabs(ray_x - (map_x+1) * BLOCK) < 0.01)
	{
		// Hit vertical wall
		wall_x = ray_y - floor(ray_y / BLOCK) * BLOCK;
		if (cos_angle > 0)
			tex_num = 3;    // West wall
		else
			tex_num = 2;    // East wall
	}
	else
	{
		// Hit horizontal wall
		wall_x = ray_x - floor(ray_x / BLOCK) * BLOCK;
		if (sin_angle > 0)
			tex_num = 0;    // North wall
		else
			tex_num = 1;    // South wall
	}

	// Get the texture X coordinate
	tex_x = (int)(wall_x / BLOCK * cub3d->textures[tex_num].width);

	// Calculate wall height based on distance
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d);
	height = (BLOCK / dist) * (WID / 2);
	start_y = (HEI - height) / 2;
	end = start_y + height;

	// Draw ceiling
	draw_maindisplay(0, start_y, rgb_to_colour(cub3d->map_info.ce_col), cub3d, i);

	// Draw textured wall
	double step = cub3d->textures[tex_num].height / (double)height;
	double tex_pos = 0;

	for (int y = start_y; y < end; y++)
	{
		int tex_y = (int)tex_pos & (cub3d->textures[tex_num].height - 1);
		tex_pos += step;

		// Get pixel color from texture
		int idx = tex_y * cub3d->textures[tex_num].line_len +
				 tex_x * (cub3d->textures[tex_num].bpp / 8);
		unsigned char b = cub3d->textures[tex_num].addr[idx];
		unsigned char g = cub3d->textures[tex_num].addr[idx + 1];
		unsigned char r = cub3d->textures[tex_num].addr[idx + 2];

		// Optional: apply distance shading
		float shade = 1.0f / (1.0f + dist * 0.04f);
		if (shade > 1.0f) shade = 1.0f;
		if (shade < 0.3f) shade = 0.3f;

		r *= shade;
		g *= shade;
		b *= shade;

		// Combine colors into one value
		int color = (r << 16) | (g << 8) | b;

		put_pixel(i, y, color, cub3d);
	}

	// Draw floor
	draw_maindisplay(end, HEI, rgb_to_colour(cub3d->map_info.fl_col), cub3d, i); */
}

void	draw_maindisplay(int top, int bot, int colour, t_data *cub3d, int i)
{
	(void) i;
	while (top < bot)
	{
		put_pixel(i, top, colour, cub3d);
		top++;
	}
}

//first person
int	draw_loop(t_data *cub3d)
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
		draw_line(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	// Draw minimap
	draw_map(cub3d);
	// Redraw rays on top of minimap
	max_ray_length = BLOCK * 5;
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
	
			// Adjust the base color (DARK_GREY) to create a gradient
			int base_color = DARK_GREY;
			int r = ((base_color >> 16) & 0xFF) * intensity;
			int g = ((base_color >> 8) & 0xFF) * intensity;
			int b = (base_color & 0xFF) * intensity;
			int gradient_color = (r << 16) | (g << 8) | b;
	
			// Background color of the minimap
			int background_color = GREY;
	
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
	//draw_filled_square(cub3d->player.x - (BLOCK/4), cub3d->player.y - (BLOCK/4), BLOCK/2, BLU, cub3d);
	//draw_filled_circle(cub3d->player.x - (BLOCK/4), cub3d->player.y - (BLOCK/4), BLOCK/4, BLU, cub3d);
	//put_pixel(cub3d->player.x, cub3d->player.y, BLU, cub3d);
	put_pixel(cub3d->player.x, cub3d->player.y, BLU, cub3d);

	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img_ptr, 0, 0);
	return (0);
}

void	draw_filled_square(int x, int y, int size, int color, t_data *cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		while (i < size)
		{
			put_pixel(x + i, y + j, color, cub3d);
			i++;
		}
		i = 0;
		j++;
	}
}

void draw_filled_circle(int x, int y, int radius, int color, t_data *cub3d)
{
	int i, j;

	for (j = -radius; j <= radius; j++)
	{
		for (i = -radius; i <= radius; i++)
		{
			// Check if the pixel is within the circle's radius
			if (i * i + j * j <= radius * radius)
			{
				put_pixel(x + i, y + j, color, cub3d);
			}
		}
	}
}

void	draw_map(t_data *cub3d)
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
	bg_color = GREY;
	wall_color = YEL;
	space_color = GREY;
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
}

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
