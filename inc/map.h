/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:09 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/14 15:00:27 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

//map_init.c
void	init_map(t_data *cub3d, char *argv);
void	init_struct(t_data *cub3d);

//map_header.c
int		get_tex(t_data *cub3d, char *line, char **tex_field, char *code);
int		get_col(t_data *cub3d, char *line, char **col_field, char *code);
char	*get_comppath(char *line);
int		verify_file(char *complete_path);

//map_content.c
void	read_content(t_data *cub3d, char *cub_file);
int		check_grid(t_data *cub3d, char *cub_file);
int		save_grid(t_data *cub3d, char *cub_file);
int		valid_mapline(char *line);
int		empty_line(char *line);
int		verify_boundaries(t_data *cub3d);

//header_utils.c
void	read_header(t_data *cub3d, char *cub_file);
int		check_header(char *line);
void	load_header(t_data *cub3d, char *line);
int		header_complete(t_data *cub3d);

//content_utils.c
int		is_walkable(char c);
int		is_boundpos(t_data *cub3d, int i, int j);
int		check_neighbours(t_data *cub3d, int i, int j);
int		validate_position(t_data *cub3d, int i, int j);

//content_utils2.c
void	process_valline(t_data *cub3d, char *line, int *i, int *max_len);
int		open_mapfile(char *cub_file);
int		process_mapline(char *line, int *inside_map, int *rows);
void	grid_cleanup(int file, char *line, t_data *cub3d);

#endif
