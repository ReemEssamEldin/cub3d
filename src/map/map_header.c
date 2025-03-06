#include "map.h"

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

int	check_header(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "F ", 2 || ft_strncmp(line, "C ", 2) == 0) == 0)
		return(1);
	return (0);
}

void	load_header(t_data *cub3d, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		cub3d->map_info.no_tex = ft_strdup(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		cub3d->map_info.so_tex = ft_strdup(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		cub3d->map_info.ea_tex = ft_strdup(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		cub3d->map_info.so_tex = ft_strdup(line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		cub3d->map_info.fl_col = ft_strdup(line);
	else if (ft_strncmp(line, "C ", 3) == 0)
		cub3d->map_info.ce_col = ft_strdup(line);
}

int	header_complete(t_data *cub3d)
{
	if (cub3d->map_info.no_tex != NULL &&
		cub3d->map_info.so_tex != NULL &&
		cub3d->map_info.ea_tex != NULL &&
		cub3d->map_info.we_tex != NULL &&
		cub3d->map_info.fl_col != NULL &&
		cub3d->map_info.ce_col != NULL)
		return(1);
	return(0);
}