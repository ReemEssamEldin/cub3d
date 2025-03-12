#include "../cub3d.h"

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
	// if (cos_angle > 0) // Wall facing right
	// 	color = (color >> 1) & 0x7F7F7F; // Darken the color
	// else if (cos_angle < 0) // Wall facing left
	// 	color = (color << 1) | 0x808080; // Lighten the color
	while (start_y < end)
	{
		put_pixel(i, start_y, color, cub3d);
		start_y++;
	}
}

//just a line, not a cone
/* int	draw_loop(t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);
	draw_square(cub3d->player.x, cub3d->player.y, 32, RED, cub3d);
	draw_map(cub3d);

	float	ray_x = cub3d->player.x;
	float	ray_y = cub3d->player.y;
	float	cos_angle = cos(cub3d->player.angle);
	float	sin_angle = sin(cub3d->player.angle);

	while(!touch(ray_x, ray_y, cub3d))
	{
		put_pixel(ray_x, ray_y, YEL, cub3d);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img_ptr, 0, 0);
	return(0);
} */

//top-down ,conical ray
/* int	draw_loop(t_data *cub3d)
{
	move_player(&cub3d->player);
	clear_image(cub3d);
	draw_square(cub3d->player.x, cub3d->player.y,
		32, RED, cub3d); //handles top-down view
	draw_map(cub3d); //handles top-down view

	float fraction = PI /3 / WID;
	float start_x = cub3d->player.angle - PI / 6;
	int i = 0;
	while(i < WID)
	{
		draw_line(&cub3d->player, cub3d, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img_ptr, 0, 0);
	return(0);
} */

//first person
int	draw_loop(t_data *cub3d)
{
	float	fraction;
	float	start_x;
	int		i;

	move_player(&cub3d->player);
	clear_image(cub3d);
	//top-down
	draw_square(cub3d->player.x, cub3d->player.y, BLOCK / 2, BLU, cub3d);
	draw_map(cub3d);
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

void	draw_map(t_data *cub3d)
{
	char	**map;
	int		color;

	map = cub3d->map_info.map;
	color = GRE;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, cub3d);
}

void	clear_image(t_data *cub3d)
{
	for (int y = 0; y < HEI; y++)
		for (int x = 0; x < WID; x++)
			put_pixel(x, y, 0, cub3d);
}
