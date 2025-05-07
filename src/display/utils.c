/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:26:00 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 21:01:57 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_data *cub3d);
void	clear_image(t_data *cub3d);
void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx, float *ray_diry);

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

void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx, float *ray_diry)
{
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;

	dir_x = cos(cub3d->player.angle);
	dir_y = sin(cub3d->player.angle);
	plane_x = -dir_y * 0.66;
	plane_y = dir_x * 0.66;
	*ray_dirx = dir_x + plane_x * cam_x;
	*ray_diry = dir_y + plane_y * cam_x;
}
