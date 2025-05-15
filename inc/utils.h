/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:20 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/14 19:47:12 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

//utils.c
int		destroy(t_data *cub3d);
void	terminate(t_data *cub3d, char *msg);
char	*remove_trailing(char *str, char *c);
char	*trim_string(char *str);
void	free_split(char **arr);

//cleaning.c
void	clean_all(t_data *cub3d);
void	clean_mapheader(t_map *map_info);
void	clean_mapcontent(t_map *map_info);
void	clean_textures(t_data *cub3d);

#endif
