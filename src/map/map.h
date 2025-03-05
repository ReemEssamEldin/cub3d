#ifndef MAP_H
# define MAP_H

# include "../cub3d.h"

//header.c
void	init_struct(t_data *cub3d);
int		check_header(char *line);
void	load_header(t_data *cub3d, char *line);
int		header_complete(t_data *cub3d);

//map_load.c
void	load_map(char *cub_file, t_data *cub3d);
int		read_cub(char *cub_file);
int		fill_map(char *cub_file, t_data *cub3d);

#endif