/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindisplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:27 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 15:34:56 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	main_display(t_data *cub3d);
void	draw_md(t_player *player, t_data *cub3d, int i);
int		assign_wallcol(t_player *player, t_data *cub3d);
void	draw_line(int top, int bot, int colour, t_data *cub3d, int i);

void	main_display(t_data *cub3d)
{
	int	i;

	i = 0;
	//cub3d->calc.start_x = cub3d->player.angle - PI / 6;
	// Calculate and store ray angles while drawing 3D view
	while (i < WID)
	{
		//cub3d->calc.ray_angles[i] = cub3d->calc.start_x; //must integrate better 4 minimap
		//cub3d->calc.start_x += cub3d->calc.fraction; //must integrate better 4 minimap
		draw_md(&cub3d->player, cub3d, i);
		i++;
	}
}

void	draw_md(t_player *player, t_data *cub3d, int i)
{
	float ray_x;
	float ray_y;
	int col_wall; //gonna be textures
	int col_ceil;
	int col_floo;

	float camera_x = 2.0 * i / (float)WID - 1.0;
	ray_casting(cub3d, camera_x, &ray_x, &ray_y);
	col_wall = assign_wallcol(player, cub3d);
	// Make y-sides darker
	if (cub3d->calc.side == 1)
		col_wall = (col_wall >> 1) & 0x7F7F7F;  // Divide RGB components by 2
	col_ceil = rgb_tocol(cub3d->map_info.ce_col, cub3d);
	col_floo = rgb_tocol(cub3d->map_info.fl_col, cub3d);
	draw_line(0, cub3d->calc.draw_start, col_ceil, cub3d, i);
	draw_line(cub3d->calc.draw_start, cub3d->calc.draw_end, col_wall, cub3d, i);
	draw_line(cub3d->calc.draw_end, HEI, col_floo, cub3d, i);
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

void	draw_line(int top, int bot, int colour, t_data *cub3d, int i)
{
	while (top < bot)
	{
		put_pixel(i, top, colour, cub3d);
		top++;
	}
}