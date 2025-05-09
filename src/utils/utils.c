/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:41:19 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 19:20:29 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int		destroy(t_data *cub3d);
void	err_msg(t_data *cub3d, char *err_msg);
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

void	err_msg(t_data *cub3d, char *err_msg)
{
	printf("%s", err_msg);
	if (cub3d)
		destroy(cub3d);
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
