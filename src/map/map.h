#ifndef MAP_H
# define MAP_H

# include "../cub3d.h"

//map_init.c
void	init_map2(t_data *cub3d, char *argv);
void	init_struct(t_data *cub3d);

//map_header.c
int		check_header(char *line);
void	load_header(t_data *cub3d, char *line);
int		header_complete(t_data *cub3d);

//map_content.c
void	load_map(char *cub_file, t_data *cub3d);
int		read_cub(char *cub_file);
int		fill_map(char *cub_file, t_data *cub3d);

#endif