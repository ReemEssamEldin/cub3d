#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

//map_init.c
void	init_map(t_data *cub3d, char *argv);
void	init_struct(t_data *cub3d);

//map_header.c
void	read_header(t_data *cub3d, char *cub_file);
int		check_header(char *line);
void	load_header(t_data *cub3d, char *line);
int		header_complete(t_data *cub3d);
char	*get_comppath(char *line);
int		verify_file(char *complete_path);

//map_content.c
void	read_content(t_data *cub3d, char *cub_file);
int		check_grid(t_data *cub3d, char *cub_file);
int		save_grid(t_data *cub3d, char *cub_file);
int		valid_mapline(char *line);
int		empty_line(char *line);
int		verify_boundaries(t_data *cub3d);

#endif
