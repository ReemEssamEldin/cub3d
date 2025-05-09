/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maindisplay_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:37:49 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/09 13:45:12 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_valid_rgb_format(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		else if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (comma_count == 2);
}

static char	**split_rgb_components(char *rgb_str, t_data *cub3d)
{
	char	**components;
	int		i;

	rgb_str = trim_string(rgb_str);
	if (!is_valid_rgb_format(rgb_str))
		err_msg(cub3d, "Error\nOnly digits, commas, and spaces are allowed");
	components = ft_split(trim_string(rgb_str), ',');
	if (!components)
		return (NULL);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
	{
		i = 0;
		while (components[i])
			free(components[i++]);
		free(components);
		return (NULL);
	}
	return (components);
}

int	rgb_tocol(char *rgb_str, t_data *cub3d)
{
	char	**components;
	int		i;
	int		r;
	int		g;
	int		b;

	components = split_rgb_components(rgb_str, cub3d);
	if (!components)
		return (-1);
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
		err_msg(cub3d, "Error\nInvalid color value: RGB values must be digits");
	val = ft_atoi(component);
	if (val < 0 || val > 255)
		err_msg(cub3d, "Error\nRGB values must be between 0 and 255");
	return (val);
}
