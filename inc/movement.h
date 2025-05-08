#ifndef MOVEMENT_H
# define MOEVEMENT_H

# include "cub3d.h"

//starting_loc.c
bool	put_player(t_data *cub3d);
bool	set_position(t_data *cub3d, int x, int y, int *found);
void	set_direction(t_data *cub3d, char pos);

//move_player.c
void	move_player(t_player *player, t_data *cub3d);
void	move_down(t_player *player, t_data *cub3d);
void	move_up(t_player *player, t_data *cub3d);
void	move_right(t_player *player, t_data *cub3d);
void	move_left(t_player *player, t_data *cub3d);

//move_rotate.c
void	move_rotate(t_player *player, float angle_speed);

//coll_detect.c
bool	touch(float pos_x, float pos_y, t_data *cub3d);
void	try_move(t_player *player, float dx, float dy, t_data *cub3d);

#endif
