/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindisplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:27 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 14:55:26 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	main_display(t_data *cub3d);
void	draw_md(t_data *cub3d, int i);
int		assign_wallcol(t_player *player, t_data *cub3d);
void	prep_line(t_data *cub3d, int top, int bottom, int col);
void	draw_line(t_data *cub3d);

void	main_display(t_data *cub3d)
{
	int	i;

	i = 0;
	while (i < WID)
	{
		draw_md(cub3d, i);
		i++;
	}
}

void	draw_md(t_data *cub3d, int i)
{
	float	ray_x;
	float	ray_y;
	float	cam_x;
	int		tex_x;

	cam_x = 2.0 * i / (float)WID - 1.0;
	ray_casting(cub3d, cam_x, &ray_x, &ray_y);
	tex_x = (int)(cub3d->calc.wall_x
			* cub3d->textures[cub3d->calc.tex_num].width);
	if ((cub3d->calc.side == 0 && cub3d->calc.ray_dirx > 0)
		|| (cub3d->calc.side == 1 && cub3d->calc.ray_diry < 0))
		tex_x = cub3d->textures[cub3d->calc.tex_num].width - tex_x - 1;
	cub3d->map_info.col_ceil = rgb_tocol(cub3d->map_info.ce_col, cub3d);
	cub3d->map_info.col_floo = rgb_tocol(cub3d->map_info.fl_col, cub3d);
	cub3d->draw.x = i;
	prep_line(cub3d, 0, cub3d->calc.draw_start, cub3d->map_info.col_ceil);
	draw_line(cub3d);
	draw_texline(cub3d, i, tex_x);
	prep_line(cub3d, cub3d->calc.draw_end, HEI, cub3d->map_info.col_floo);
	draw_line(cub3d);
}

int	assign_wallcol(t_player *player, t_data *cub3d)
{
	int	col_wall;

	if (cub3d->calc.side == 0)
	{
		if (cub3d->calc.map_x > player->x / BLOCK)
			col_wall = PIN;
		else
			col_wall = MAG;
	}
	else
	{
		if (cub3d->calc.map_y > player->y / BLOCK)
			col_wall = TEA;
		else
			col_wall = GRE;
	}
	return (col_wall);
}
unction has more than 25 lines
void	prep_line(t_data *cub3d, int top, int bottom, int col)
{
	cub3d->draw.top = top;
	cub3d->draw.bottom = bottom;
	cub3d->draw.col = col;
}

void	draw_line(t_data *cub3d)
{
	int	current;

	current = cub3d->draw.top;
	while (current < cub3d->draw.bottom)
	{
		put_pixel(cub3d->draw.x, current, cub3d->draw.col, cub3d);
		current++;
	}
}
