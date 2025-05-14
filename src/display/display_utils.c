/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/14 18:48:41 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_data *cub3d);
void	clear_image(t_data *cub3d);
void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx,
			float *ray_diry);
bool	number_check(char *str);

/**
 * @brief Puts a pixel of specified color at given coordinates in the window
 *
 * This function writes a single pixel with the specified RGB color to the
 * display buffer at the given (x,y) coordinates. It performs bounds checking
 * to ensure the coordinates are within the window dimensions.
 *
 * @param x The x coordinate of the pixel (must be within window width)
 * @param y The y coordinate of the pixel (must be within window height)
 * @param color The RGB color value to set (24-bit format)
 * @param cub3d Pointer to the main data structure containing display
 * 				information
 *
 * @return void
 * @note Color is written in BGR format in memory (little endian)
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

/**
 * @brief Clears the entire image by setting all pixels to black
 *
 * This function iterates through each pixel in the image defined by WID and HEI
 * constants & sets each pixel to color value 0 (black) using put_pixel function
 *
 * @param cub3d Pointer to the main data structure containing image information
 * @return void
 */
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

/**
 * Calculates ray direction vector components for raycasting
 * based on player angle and camera position
 *
 * @param cub3d    Main game data structure containing player info
 * @param cam_x    Camera x position in screen space (-1 to 1)
 * @param ray_dirx Pointer to store calculated x component of ray direction
 * @param ray_diry Pointer to store calculated y component of ray direction
 *
 * The function:
 * 1. Calculates direction vector from player angle
 * 2. Computes camera plane vector perpendicular to direction
 * 3. Determines final ray direction by combining direction and plane vectors
 *
 * Uses 0.66 as camera plane length for ~66° FOV
 */
void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx,
			float *ray_diry)
{
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;

	dir_x = cos(cub3d->player.angle);
	dir_y = sin(cub3d->player.angle);
	plane_x = -dir_y * FOV;
	plane_y = dir_x * FOV;
	*ray_dirx = dir_x + plane_x * cam_x;
	*ray_diry = dir_y + plane_y * cam_x;
}
