/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:59 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/19 18:29:48 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "cub3d.h"

//init.c
void		init_mlx(t_data *cub3d);
void		load_multitexs(t_data *cub3d);
int			load_singletex(t_data *cub3d, char *tex_path, int tex_idx);
void		init_player(t_data *cub3d);

//starting_loc.c
bool	put_player(t_data *cub3d);
bool	set_position(t_data *cub3d, int x, int y, int *found);
void	set_direction(t_data *cub3d, char pos);

#endif
