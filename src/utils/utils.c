/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:19 by reldahli          #+#    #+#             */
/*   Updated: 2025/03/13 13:41:32 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	err_msg(t_data *cub3d, char *err_msg)
{
	printf("%s", err_msg);
	if (cub3d)
	{
		clean_mapheader(&cub3d->map_info);
		clean_mapcontent(&cub3d->map_info);
	}
	//frees/destroys go here;
	exit(EXIT_FAILURE);
}

void	clean_mapheader(t_map *map_info)
{
	if (map_info->no_tex)
		free(map_info->no_tex);
	if (map_info->so_tex)
		free(map_info->so_tex);
	if (map_info->ea_tex)
		free(map_info->ea_tex);
	if (map_info->we_tex)
		free(map_info->we_tex);
	if (map_info->fl_col)
		free(map_info->fl_col);
	if (map_info->ce_col)
		free(map_info->ce_col);
}

void	clean_mapcontent(t_map *map_info)
{
	int	i;

	if (map_info->map == NULL)
		return ;
	i = 0;
	while (map_info->map[i] != NULL)
	{
		free(map_info->map[i]);
		i++;
	}
	free(map_info->map);
}

/* char	*remove_trailing(char *str, char const *c)
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
} */

char	*remove_trailing(char *str, char *c)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_strchr(c, str[len - 1]) != NULL)
	{
		str[len - 1] = '\0';
		len--;
	}
	return (str);
}
