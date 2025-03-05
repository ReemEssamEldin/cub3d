#include "../cub3d.h"

void	load_map(char *cub_file, t_data *cub3d);
int		read_cub(char *cub_file);
int		fill_map(char *cub_file, t_data *cub3d);

void	load_map(char *cub_file, t_data *cub3d)
{
	cub3d->map_info.map_rows = read_cub(cub_file);
	cub3d->map_info.map = malloc((cub3d->map_info.map_rows + 1) \
	* sizeof(char *));
	if (!cub3d->map_info.map)
		perror("Map allocation failed");
	cub3d->map_info.map_cols = fill_map(cub_file, cub3d);
}

int	read_cub(char *cub_file)
{
	int		file;
	int		rows;
	char	*line;

	rows = 0;
	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Map opening failed.");
	line = get_next_line(file);
	if (!line)
		err_msg("Error\nEmpty map file.");
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(file);
	}
	close(file);
	free(line);
	if (rows < 3)
		err_msg("Error\nIncompatible map. (rows)");
	return (rows);
}

int	fill_map(char *cub_file, t_data *cub3d)
{
	int	file;
	int	i;
	int	cols;
	int	cols_temp;

	file = open(cub_file, O_RDONLY);
	i = 0;
	while (i < cub3d->map_info.map_rows)
		cub3d->map_info.map[i++] = get_next_line(file);
	cub3d->map_info.map[i] = NULL;
	close (file);
	i = 0;
	cols = 0;
	while (i < (cub3d->map_info.map_rows - 1))
	{
		cols_temp = ft_strlen(cub3d->map_info.map[i]);
		if(cols < cols_temp)
			cols = cols_temp; //or cols_temp-1 because trailing \n is not removed yet
		cub3d->map_info.map[i] = \
			remove_trailing(cub3d->map_info.map[i], "\n");
		i++;
	}
	if (cols < 3)
		err_msg("Error\nIncompatible map. (cols)");
	return (cols);
}