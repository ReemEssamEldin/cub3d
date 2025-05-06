/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:55 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:20 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "cub3d.h"

// drawing.c
void	put_pixel(int x, int y, int color, t_data *cub3d);
void	draw_md(t_player *player, t_data *cub3d, float start_x, int i);
void	draw_line(int top, int bot, int colour, t_data *cub3d, int i);
void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	draw_filled_square(int x, int y, int size, int color, t_data *cub3d);
void	clear_image(t_data *cub3d);

//rendering.c
int		render(t_data *cub3d);
void	init_render(t_data *cub3d);
void	main_display(t_data *cub3d);

//minimap.c
void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);
void	draw_mmrays(t_data *cub3d);

//minimap_utils.c
void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	blend_cols(t_calc *calc);

// math.c
bool	touch(float px, float py, t_data *cub3d);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d);

// draw_floceil.c
int		rgb_to_colour(char *rgb_str, t_data *cub3d);
bool	number_check(char *str);
char	*trim_string(char *str);

// textures.c
void	load_textures(t_data *cub3d);
#endif
