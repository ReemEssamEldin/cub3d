#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

bool	put_player(t_data *cub3d);
bool	set_position(t_data *cub3d, int x, int y, int *found);
void	set_direction(t_data *cub3d, char pos);
#endif
