/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:12:30 by reldahli          #+#    #+#             */
/*   Updated: 2025/04/14 16:29:41 by hsetyamu         ###   ########.fr       */
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

/*
// shading based on distance
void	draw_line(t_player *player, t_data *cub3d, float start_x, int i)
{
	(void)i;
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	float	ray_x = player->x;
	float	ray_y = player->y;

	while(!touch(ray_x, ray_y, cub3d))
	{
		put_pixel(ray_x, ray_y, RED, cub3d); //this line handles rays
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	//this part handles 1st-person perspective
	float	dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d);
	//fix fish-eye
	//float	dist = distance(ray_x - player->x, ray_y - player->y); //fish-eye
	float	height = (BLOCK / dist) * (WID / 2);
	int	start_y = (HEI - height) / 2;
	int	end = start_y + height;

	float shading_factor = 1.0 / (1.0 + dist * 0.1);
	if (shading_factor > 1.0)
		shading_factor = 1.0;
	if (shading_factor < 0.2)
		shading_factor = 0.2;

	// Apply shading to the color
	int	color = GRE;
	int	shaded_color = ((int)((color & 0xFF) * shading_factor) & 0xFF) |
			(((int)(((color >> 8) & 0xFF) * shading_factor) & 0xFF) << 8) |
			(((int)(((color >> 16) & 0xFF) * shading_factor) & 0xFF) << 16);

	while(start_y < end)
	{
		//put_pixel(i, start_y, GRE, cub3d);
		put_pixel(i, start_y, shaded_color, cub3d);
		start_y++;
	}
}*/

void	draw_line(t_player *player, t_data *cub3d, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		color;
	int		color2;
	int		color3;

	(void)i;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, cub3d))
	{
		put_pixel(ray_x, ray_y, RED, cub3d); //this line handles rays
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	//this part handles 1st-person perspective
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, cub3d); //fix fish-eye
	//float dist = distance(ray_x - player->x, ray_y - player->y); //fish-eye
	height = (BLOCK / dist) * (WID / 2);
	start_y = (HEI - height) / 2;
	end = start_y + height;
	color = GRE;
	color2 = rgb_to_colour(cub3d->map_info.ce_col);
	color3 = rgb_to_colour(cub3d->map_info.fl_col);
	// if (cos_angle > 0) // Wall facing right
	// 	color = (color >> 1) & 0x7F7F7F; // Darken the color
	// else if (cos_angle < 0) // Wall facing left
	// 	color = (color << 1) | 0x808080; // Lighten the color
	int top = 0;
	while ( top < start_y)
	{
		put_pixel(i, top, color2, cub3d);
		top++;
	}
	while (start_y < end)
	{
		put_pixel(i, start_y, color, cub3d);
		start_y++;
	}
	int bot = HEI;
	while (end < bot)
	{
		put_pixel(i, end, color3, cub3d);
		end++;
	}
}


//first person
int	draw_loop(t_data *cub3d)
{
	float	fraction;
	float	start_x;
	int		i;

	//move_player(&cub3d->player);
	move_player(&cub3d->player, cub3d);
	clear_image(cub3d);
	//1st-person
	fraction = PI / 3 / WID; //FOV width
	start_x = cub3d->player.angle - PI / 6;
	i = 0;
	while (i < WID)
	{
		draw_line(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	draw_map(cub3d);
	//top-down
	draw_triangle(cub3d->player.x, cub3d->player.y, BLOCK / 2, BLU, cub3d);

	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img_ptr, 0, 0);
	return (0);
}

void	draw_square(int x, int y, int size, int color, t_data *cub3d)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, cub3d);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, cub3d);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, cub3d);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, cub3d);
}

void	draw_filled_square(int x, int y, int size, int color, t_data *cub3d)
{
	for (int j = 0; j < size; j++)
		for (int i = 0; i < size; i++)
			put_pixel(x + i, y + j, color, cub3d);
}

void	draw_triangle(int x, int y, int size, int color, t_data *cub3d)
{
	// Calculate the vertices of the triangle
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	x3;
	int	y3;
	int	tx;
	int	ty;
	int	rx;
	int	ry;
	int	bx;
	int	by;

	x1 = x;
	y1 = y;
	x2 = x - size / 2;
	y2 = y + size;
	x3 = x + size / 2;
	y3 = y + size;
	// Draw the three sides of the triangle
	for (int i = 0; i <= size; i++)
	{
		// Top left edge: from (x1, y1) to (x2, y2)
		tx = x1 + (x2 - x1) * i / size;
		ty = y1 + (y2 - y1) * i / size;
		put_pixel(tx, ty, color, cub3d);
		// Top right edge: from (x1, y1) to (x3, y3)
		rx = x1 + (x3 - x1) * i / size;
		ry = y1 + (y3 - y1) * i / size;
		put_pixel(rx, ry, color, cub3d);
		// Bottom edge: from (x2, y2) to (x3, y3)
		bx = x2 + (x3 - x2) * i / size;
		by = y2 + (y3 - y2) * i / size;
		put_pixel(bx, by, color, cub3d);
	}
}

void	draw_map(t_data *cub3d)
{
	char	**map;
	int		map_width;
	int		map_height;
	int		wall_color;
	int		bg_color;
	int 	space_color;
	int map_padding;

	map = cub3d->map_info.map;
	map_height = 0;
	map_width = 0;
	map_padding = 0;
	while (map[map_height])
	{
		int len = 0;
		while (map[map_height][len])
			len++;
		if (len > map_width)
			map_width = len;
		map_height++;
	}
	map_width += map_padding;
	map_height += map_padding;

	bg_color = BLU;
	wall_color = GRE;
	space_color = GREY;
	// Fill background
	draw_filled_square(0, 0, map_width * BLOCK, bg_color, cub3d);
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_filled_square(x * BLOCK, y * BLOCK, BLOCK, wall_color, cub3d);
			else if (map[y][x] == '0')
				draw_filled_square(x * BLOCK, y * BLOCK, BLOCK, space_color, cub3d);
}

void	clear_image(t_data *cub3d)
{
	for (int y = 0; y < HEI; y++)
		for (int x = 0; x < WID; x++)
			put_pixel(x, y, 0, cub3d);
}
