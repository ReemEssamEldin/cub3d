#ifndef UTILS_H
# define UTILS_H

# include "../cub3d.h"

//utils.c
void	err_msg(t_data *cub3d, char *err_msg);
char	*remove_trailing(char *str, char const *c);
void	clean_header(t_map *map_info);
#endif