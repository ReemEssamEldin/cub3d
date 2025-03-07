#include "../cub3d.h"

void	read_content(t_data *cub3d, char *cub_file);
int		check_grid(t_data *cub3d, char *cub_file);
int	save_grid(t_data *cub3d, char *cub_file);
int		valid_mapline(char *line);
int		empty_line(char *line);

void	read_content(t_data *cub3d, char *cub_file)
{
	cub3d->map_info.map_rows = check_grid(cub3d, cub_file);
	cub3d->map_info.map = malloc((cub3d->map_info.map_rows + 1) \
	* sizeof(char *));
	if (!cub3d->map_info.map)
		perror("Map allocation failed");
	cub3d->map_info.map_cols = save_grid(cub3d, cub_file);

/* 	int i;
	i = 0;
	while (cub3d->map_info.map[i] != NULL)
	{
		printf("Row %2d: [%s]\n", i, cub3d->map_info.map[i]);
		i++;
	}
	printf("# of rows in map = %d\n", cub3d->map_info.map_rows);
	printf("# of cols in map = %d\n", cub3d->map_info.map_cols); */
}

int	check_grid(t_data *cub3d, char *cub_file)
{
	int		file;
	char	*line;
	int		rows;
	int		in_map_section;

	rows = 0;
	in_map_section = 0;
	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Error\nMap opening failed");
	line = get_next_line(file);
	while (line)
	{
		if (valid_mapline(line))
		{
			in_map_section = 1;
			rows++;
		}
		else if (in_map_section)
		{
			free(line);
			close(file);
			err_msg(cub3d, "Error\nNon map line (Empty line or invalid symbol");
		}
		free(line);
		line = get_next_line(file);
	}
	close(file);
	return (rows);
}

int	save_grid(t_data *cub3d, char *cub_file)
{
	int		file;
	char	*line;
	int		i;
	int		line_len;

	i = 0;
	file = open(cub_file, O_RDONLY);
	if (file == -1)
		perror("Error\nMap opening failed");
	cub3d->map_info.map_cols = 0;
	line = get_next_line(file);
	while (line)
	{
		if (valid_mapline(line))
		{
			line = remove_trailing(line, "\n");
			cub3d->map_info.map[i++] = line;
			line_len = ft_strlen(line);
			if (line_len > cub3d->map_info.map_cols)
				cub3d->map_info.map_cols = line_len;
		}
		else
			free(line);
		line = get_next_line(file);
	}
	cub3d->map_info.map[i] = NULL;
	close(file);
	return(line_len);
}

int valid_mapline(char *line)
{
	int i = 0;
	
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && 
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '\n' || line[i] == '\0');
}