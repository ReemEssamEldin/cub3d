#include "map.h"

int	check_header(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return(1);
	return (0);
}

void	load_header(t_data *cub3d, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (cub3d->map_info.no_tex != NULL)
			err_msg("Error\nRefilling no_tex");
		cub3d->map_info.no_tex = ft_strdup(line);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (cub3d->map_info.so_tex != NULL)
			err_msg("Error\nRefilling so_tex");
		cub3d->map_info.so_tex = ft_strdup(line);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (cub3d->map_info.ea_tex != NULL)
			err_msg("Error\nRefilling ea_tex");
		cub3d->map_info.ea_tex = ft_strdup(line);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (cub3d->map_info.we_tex != NULL)
			err_msg("Error\nRefilling we_tex");
		cub3d->map_info.we_tex = ft_strdup(line);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (cub3d->map_info.fl_col != NULL)
			err_msg("Error\nRefilling fl_col");
		cub3d->map_info.fl_col = ft_strdup(line);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (cub3d->map_info.ce_col != NULL)
			err_msg("Error\nRefilling ce_col");
		cub3d->map_info.ce_col = ft_strdup(line);
	}
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