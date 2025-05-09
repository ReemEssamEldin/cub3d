/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:19 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 17:43:06 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	err_msg(t_data *cub3d, char *err_msg);
char	*remove_trailing(char *str, char *c);

void	err_msg(t_data *cub3d, char *err_msg)
{
	printf("%s", err_msg);
	if (cub3d)
	{
		// clean_mapheader(&cub3d->map_info);
		// clean_mapcontent(&cub3d->map_info);
		// clean_textures(cub3d);
		clean_all(cub3d);
	}
	exit(EXIT_FAILURE);
}

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
