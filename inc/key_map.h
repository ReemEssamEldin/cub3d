#ifndef KEY_MAP_H
# define KEY_MAP_H

# include "cub3d.h"

int		key_press(int keysym, t_data *cub3d);
int		key_release(int keysym, t_data *cub3d);
//void	move_player(t_player *player);
void	move_player(t_player *player, t_data *cub3d);
void	key_hooks(t_data *cub3d);
#endif
