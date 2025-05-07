/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindisplay_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:37:49 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/07 22:42:32 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	rgb_tocol(char *rgb_str, t_data *cub3d);
int	validate_col(char *component, t_data *cub3d);

int	rgb_tocol(char *rgb_str, t_data *cub3d)
{
	char	**components;
	int		i;
	int		r;
	int		g;
	int		b;

	components = ft_split(trim_string(rgb_str), ',');
	if (!components)
		return (-1);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
	{
		i = 0;
		while (components[i])
			free(components[i++]);
		free(components);
		return (-1);
	}
	r = validate_col(components[0], cub3d);
	g = validate_col(components[1], cub3d);
	b = validate_col(components[2], cub3d);
	i = 0;
	while (components[i])
		free(components[i++]);
	free(components);
	return ((r << 16) | (g << 8) | b);
}

int	validate_col(char *component, t_data *cub3d)
{
	int	val;

	if (!number_check(component))
		err_msg(cub3d, "Error\nInvalid color value");
	val = ft_atoi(component);
	if (val < 0 || val > 255)
		err_msg(cub3d, "Error\nInvalid color value");
	return (val);
}
