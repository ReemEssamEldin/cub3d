/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:55 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 15:57:34 by hsetyamu         ###   ########.fr       */
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
void	draw_md(t_data *cub3d, int i);
int		assign_wallcol(t_player *player, t_data *cub3d);
void	prep_line(t_data *cub3d, int top, int bottom, int col);
void	draw_line(t_data *cub3d);

//maindisplay_utils.c
int		rgb_tocol(char *rgb_str, t_data *cub3d);
int		validate_col(char *component, t_data *cub3d);
bool	is_valid_rgb_format(char *str);

//raycast_engine.c
void	ray_casting(t_data *cub3d, float cam_x, float *ray_x, float *ray_y);
void	calc_deltadist(t_data *cub3d);
void	determine_hitpos(t_data *cub3d, float *ray_x, float *ray_y);
void	calc_drawparams(t_data *cub3d);
void	calc_textinfo(t_data *cub3d);

//raycast_dda.c
void	dda_setup(t_data *cub3d);
void	dda_execute(t_data *cub3d);

//display_utils.c
void	put_pixel(int x, int y, int color, t_data *cub3d);
void	clear_image(t_data *cub3d);
void	define_raydir(t_data *cub3d, float cam_x, float *ray_dirx, float *ray_diry);
bool	number_check(char *str);
char	*trim_string(char *str);

//minimap.c
void	mini_map(t_data *cub3d);
void	draw_mm(t_data *cub3d);
void	mm_bg(t_data *cub3d);
void	mm_walls(t_data *cub3d);

//minimap_rays.c
void	draw_mmcone(t_data *cub3d);
void	draw_mmray(t_data *cub3d, float ray_dirx, float ray_diry);

//minimap_utils.c
void	draw_square(t_data *cub3d);
void	blend_cols(t_calc *calc);

//draw_floceil.c
// int		rgb_tocol(char *rgb_str, t_data *cub3d);
// int		validate_col(char *component, t_data *cub3d);
// bool	number_check(char *str);
// char	*trim_string(char *str);

//textures.c
void	load_multitexs(t_data *cub3d);
int		load_singletex(t_data *cub3d, char *tex_path, int tex_idx);
void	draw_texline(t_data *cub3d, int x, int tex_x);
int		get_texcol(t_texture *texture, int x, int y);

#endif
