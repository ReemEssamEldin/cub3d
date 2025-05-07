/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:55 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/07 16:07:57 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "cub3d.h"

//rendering.c
int		render(t_data *cub3d);
void	init_render(t_data *cub3d);

//maindisplay.c
void	main_display(t_data *cub3d);
void	draw_md(t_player *player, t_data *cub3d, int i);
int		assign_wallcol(t_player *player, t_data *cub3d);
void	draw_line(int top, int bot, int colour, t_data *cub3d, int i);

//raycasting.c
void ray_casting(t_data *cub3d, float camera_x, float *ray_x, float *ray_y);

//render_utils.c
void	put_pixel(int x, int y, int color, t_data *cub3d);
void	clear_image(t_data *cub3d);

//minimap.c
void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);
void	draw_mmrays(t_data *cub3d);

//minimap_utils.c
void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	blend_cols(t_calc *calc);

// draw_floceil.c
bool	is_valid_rgb_format(char *str);
int		rgb_tocol(char *rgb_str, t_data *cub3d);
int		validate_col(char *component, t_data *cub3d);
bool	number_check(char *str);
char	*trim_string(char *str);

// textures.c
void	load_textures(t_data *cub3d);

#endif
