/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindisplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:27 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/14 16:05:00 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	main_display(t_data *cub3d);
void	draw_md(t_data *cub3d, int i);
void	prep_line(t_data *cub3d, int top, int bottom, int col);
void	draw_line(t_data *cub3d);

/**
 * @brief Main display function that renders the game view
 * @param cub3d Main data structure containing game information
 */
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

/**
 * @brief Draws a single vertical line of the display at position i
 * @param cub3d Main data structure containing game information
 * @param i Current x-position being rendered
 *
 * This function handles:
 * - Camera plane calculations
 * - Ray casting
 * - Texture coordinate calculations
 * - Ceiling and floor color conversion
 * - Drawing the ceiling, wall texture, and floor
 */
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
	cub3d->draw.x = i;
	prep_line(cub3d, 0, cub3d->calc.draw_start, cub3d->map_info.col_ceil);
	draw_line(cub3d);
	draw_texline(cub3d, i, tex_x);
	prep_line(cub3d, cub3d->calc.draw_end, HEI, cub3d->map_info.col_floo);
	draw_line(cub3d);
}

/**
 * @brief Prepares drawing parameters for a vertical line
 * @param cub3d Main data structure containing game information
 * @param top Starting y-coordinate for the line
 * @param bottom Ending y-coordinate for the line
 * @param col Color of the line
 */
void	prep_line(t_data *cub3d, int top, int bottom, int col)
{
	cub3d->draw.top = top;
	cub3d->draw.bottom = bottom;
	cub3d->draw.col = col;
}

/**
 * @brief Draws a vertical line using the prepared parameters
 * @param cub3d Main data structure containing game information
 *
 * Uses the parameters set in prep_line to draw a vertical line
 * from top to bottom with the specified color
 */
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
