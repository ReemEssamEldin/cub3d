/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:20:03 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 22:43:59 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_multitexs(t_data *cub3d);
int		load_singletex(t_data *cub3d, char *tex_path, int tex_idx);
int		get_texcol(t_texture *texture, int x, int y);
void	draw_texline(t_data *cub3d, int x, int tex_x);

void	load_multitexs(t_data *cub3d)
{
	if (!load_singletex(cub3d, cub3d->map_info.no_tex, 0))
		err_msg(cub3d, "Error\nFailed to load north texture");
	if (!load_singletex(cub3d, cub3d->map_info.so_tex, 1))
		err_msg(cub3d, "Error\nFailed to load south texture");
	if (!load_singletex(cub3d, cub3d->map_info.ea_tex, 2))
		err_msg(cub3d, "Error\nFailed to load east texture");
	if (!load_singletex(cub3d, cub3d->map_info.we_tex, 3))
		err_msg(cub3d, "Error\nFailed to load west texture");
}

int	load_singletex(t_data *cub3d, char *tex_path, int tex_idx)
{
	int	width;
	int	height;

	cub3d->textures[tex_idx].img = mlx_xpm_file_to_image(cub3d->mlx_ptr,
			tex_path, &width, &height);
	if (!cub3d->textures[tex_idx].img)
		return (0);
	cub3d->textures[tex_idx].addr = mlx_get_data_addr(
			cub3d->textures[tex_idx].img,
			&cub3d->textures[tex_idx].bpp,
			&cub3d->textures[tex_idx].line_len,
			&cub3d->textures[tex_idx].endian);
	cub3d->textures[tex_idx].width = width;
	cub3d->textures[tex_idx].height = height;
	return (1);
}

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

void	draw_texline(t_data *cub3d, int x, int tex_x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
	t_texture	*texture;

	texture = &cub3d->textures[cub3d->calc.tex_num];
	step = 1.0 * texture->height / cub3d->calc.line_height;
	tex_pos = (cub3d->calc.draw_start - HEI / 2 + cub3d->calc.line_height / 2) 
		* step;
	y = cub3d->calc.draw_start;
	while (y < cub3d->calc.draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_texcol(texture, tex_x, tex_y);
		if (cub3d->calc.side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(x, y, color, cub3d);
		y++;
	}
}
