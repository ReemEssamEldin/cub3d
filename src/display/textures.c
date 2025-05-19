/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:20:03 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/19 18:29:11 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_texline(t_data *cub3d, int x, int tex_x);
int		get_texcol(t_texture *texture, int x, int y);

/**
 * @brief Draws a vertical line of texture on the screen
 *
 * This draws a vertical line of texture pixels at a given x coordinate.
 * It handles texture mapping, including calculations for texture coordinates,
 * scaling, and shading effects for walls hit on different sides.
 *
 * @param cub3d    Pointer to the main game data structure
 * @param x        X coordinate where the texture line will be drawn
 * @param tex_x    X coordinate in the texture to sample from
 *
 * The function performs the following steps:
 * 1. Calculates texture step size based on line height
 * 2. Determines initial texture position
 * 3. Iterates through vertical pixels from draw_start to draw_end
 * 4. Maps texture coordinates and applies shading for side walls
 * 5. Draws each pixel of the texture line
 */
void	draw_texline(t_data *cub3d, int x, int tex_x)
{
	t_texture	*texture;

	texture = &cub3d->textures[cub3d->calc.tex_num];
	cub3d->calc.step = 1.0 * texture->height / cub3d->calc.line_height;
	cub3d->calc.tex_pos = (cub3d->calc.draw_start - HEI / 2
			+ cub3d->calc.line_height / 2) * cub3d->calc.step;
	cub3d->calc.y = cub3d->calc.draw_start;
	while (cub3d->calc.y < cub3d->calc.draw_end)
	{
		cub3d->calc.tex_y = (int)cub3d->calc.tex_pos & (texture->height - 1);
		cub3d->calc.tex_pos += cub3d->calc.step;
		cub3d->calc.color = get_texcol(texture, tex_x, cub3d->calc.tex_y);
		if (cub3d->calc.side == 1)
			cub3d->calc.color = (cub3d->calc.color >> 1) & 0x7F7F7F;
		put_pixel(x, cub3d->calc.y, cub3d->calc.color, cub3d);
		cub3d->calc.y++;
	}
}

/**
 * Get the color value from a texture at specified coordinates
 *
 * @param texture Pointer to texture structure containing image data
 * @param x X coordinate in the texture
 * @param y Y coordinate in the texture
 * @return Color value at the specified coordinates, 0 if invalid
 *
 * This calculates the memory offset for the requested pixel coordinates and
 * returns the color value stored at that location. The color is returned as an
 * unsigned integer representing the pixel data in the texture's color format.
 * Returns 0 if the coordinates are outside the texture boundaries.
 */
int	get_texcol(t_texture *texture, int x, int y)
{
	char	*dst;
	int		offset;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	offset = (y * texture->line_len + x * (texture->bpp / 8));
	dst = texture->addr + offset;
	return (*(unsigned int *)dst);
}
