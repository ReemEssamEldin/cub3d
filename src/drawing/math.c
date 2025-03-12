#include "../cub3d.h"

bool	touch(float px, float py, t_data *cub3d)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (cub3d->map_info.map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_data *cub3d)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - cub3d->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle); // the correction
	return (fix_dist);
}
