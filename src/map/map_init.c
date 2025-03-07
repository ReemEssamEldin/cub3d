#include "map.h"

void	init_struct(t_data *cub3d);

void	init_map2(t_data *cub3d, char *argv)
{
	int		file;
	char	*line;

	init_struct(cub3d);
	file = open(argv, O_RDONLY);
	if (file == -1)
		perror("Map opening failed.");
	line = get_next_line(file);
	while (line)
	{
		if (check_header(line))
			load_header(cub3d, line);
		free(line);
		line = get_next_line(file);
		// if (header_complete(cub3d) && )
		// 	load_map();
	}
	free(line);
	//load_map()
	//return;
}

void	init_struct(t_data *cub3d)
{
	cub3d->map_info.no_tex = NULL;
	cub3d->map_info.so_tex = NULL;
	cub3d->map_info.ea_tex = NULL;
	cub3d->map_info.we_tex = NULL;
	cub3d->map_info.fl_col = NULL;
	cub3d->map_info.ce_col = NULL;
	cub3d->map_info.map = NULL;
	cub3d->map_info.map_rows = 0;
	cub3d->map_info.map_cols = 0;
}