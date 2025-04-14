/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:55 by reldahli          #+#    #+#             */
/*   Updated: 2025/04/14 16:28:37 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "cub3d.h"

// drawing.c
void	put_pixel(int x, int y, int color, t_data *cub3d);
void	draw_line(t_player *player, t_data *cub3d, float start_x, int i);
int		draw_loop(t_data *cub3d);
void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	draw_filled_square(int x, int y, int size, int color, t_data *cub3d);
void	draw_triangle(int x, int y, int size, int color, t_data *cub3d);
void	draw_map(t_data *cub3d);
void	clear_image(t_data *cub3d);
// math.c
bool	touch(float px, float py, t_data *cub3d);
float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d);

// draw_floceil.c
int rgb_to_colour(char *rgb_str);
#endif
