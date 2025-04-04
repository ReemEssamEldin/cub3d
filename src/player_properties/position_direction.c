#include "../../inc/player.h"

bool	put_player(t_data *cub3d);
bool	set_position(t_data *cub3d, int x, int y, int *found);
void	set_direction(t_data *cub3d, char pos);

bool	put_player(t_data *cub3d)
{
	int		x;
	int		y;
	int		found;
	char	pos;
	
	found = false;
	y = 0;
	while (y < cub3d->map_info.map_rows)
	{
		x = 0;
		while (x < cub3d->map_info.map_cols)
		{
			pos = cub3d->map_info.map[y][x];
			if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
				if (!set_position(cub3d, x, y, &found))
					return (false);
			x++;
		}
		y++;
	}
	return (found);
}

bool	set_position(t_data *cub3d, int x, int y, int *found)
{
	char	pos;

	pos = cub3d->map_info.map[y][x];
	if (*found)
		return (false);
	cub3d->player.x = (x * BLOCK) + (BLOCK / 2);
	cub3d->player.y = (y * BLOCK) + (BLOCK / 2);
	set_direction(cub3d, pos);
	cub3d->map_info.map[y][x] = '0';
	*found = true;
	return (true);
}

void	set_direction(t_data *cub3d, char pos)
{
	if (pos == 'N')
		cub3d->player.angle = 3 * PI / 2;
	else if (pos == 'S')
		cub3d->player.angle = PI / 2;
	else if (pos == 'E')
		cub3d->player.angle = 0;
	else if (pos == 'W')
		cub3d->player.angle = PI;
}