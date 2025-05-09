/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:19 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 21:52:56 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		destroy(t_data *cub3d);
void	terminate(t_data *cub3d, char *terminate);
char	*remove_trailing(char *str, char *c);

int	destroy(t_data *cub3d)
{
	if (BONUS)
		end_audio();
	clean_all(cub3d);
	if (cub3d->img_ptr)
		mlx_destroy_image(cub3d->mlx_ptr, cub3d->img_ptr);
	if (cub3d->win_ptr)
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	if (cub3d->mlx_ptr)
	{
		mlx_destroy_display(cub3d->mlx_ptr);
		free(cub3d->mlx_ptr);
	}
	exit(0);
}

void	terminate(t_data *cub3d, char *terminate)
{
	printf("%s", terminate);
	if (cub3d)
	{
		clean_mapheader(&cub3d->map_info);
		clean_mapcontent(&cub3d->map_info);
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
