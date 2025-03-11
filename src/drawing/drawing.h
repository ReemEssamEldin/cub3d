#ifndef DRAWING_H
# define DRAWING_H

# include "../cub3d.h"

void	put_pixel(int x, int y, int color, t_data *cub3d);
void	draw_line(t_player *player, t_data *cub3d, float start_x, int i);
int		draw_loop(t_data *cub3d);
void	draw_square(int x, int y, int size, int color, t_data *cub3d);
void	draw_map(t_data *cub3d);
#endif
