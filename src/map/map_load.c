#include "../cub3d.h"

void	load_map(char *cub_file, t_data *gdata);
int		read_cub(char *cub_file);
int		fill_map(char *cub_file, t_data *gdata);
char	*remove_trailing(char *c, char const *str);

void	map_load(char *cub_file, t_data *gdata)
{
	gdata->map_details.maprows = read_cub(cub_file);
	gdata->map_details.map = malloc((gdata->map_details.maprows + 1) \
	* sizeof(char *));
	if (!gdata->map_details.map)
		perror("Map allocation failed");
	gdata->map_details.mapcols = fill_map(ber_file, gdata);
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
	{
		printf("Empty map file.");
		exit(1);
	}
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(file);
	}
	close(file);
	free(line);
	if (rows < 3)
	{
		printf("Incompatible map. (rows)");
		exit(1);
	}
	return (rows);
}

int	fill_map(char *cub_file, t_data *gdata)
{
	int	file;
	int	i;
	int	cols;
	int	cols_temp;

	file = open(cub_file, O_RDONLY);
	i = 0;
	while (i < gdata->map_details.maprows)
		gdata->map_details.map[i++] = get_next_line(file);
	gdata->map_details.map[i] = NULL;
	close (file);
	i = 0;
	cols = 0
	while (i < (gdata->map_details.maprows - 1))
	{
		cols_temp = ft_strlen(gdata->map_details.map[i]);
		if(cols < cols_temp)
			cols = cols_temp;
		gdata->map_details.map[i] = \
			remove_trailing(gdata->map_details.map[i], "\n");
		i++;
	}
	if (cols < 3)
	{
		fprintf("Incompatible map (cols).");
		exit(1);
	}
	return (cols);
}

char	*remove_trailing(char *str, char const *c)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!c || !str)
		return (NULL);
	start = 0;
	while (str[start] != '\0' && ft_strchr(c, str[start]) != NULL)
		start++;
	end = ft_strlen(str + start);
	while (end > start && ft_strchr(c, str[(start + end) - 1]) != NULL)
		end--;
	trimmed = ft_calloc((end + 1), sizeof(char *));
	if (!trimmed)
		return (NULL);
	ft_strncpy(trimmed, (str + start), end);
	free(str);
	return (trimmed);
}