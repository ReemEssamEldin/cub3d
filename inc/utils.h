/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetya <hsetya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:20 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 21:52:56 by hsetya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

//utils.c
int		destroy(t_data *cub3d);
void	terminate(t_data *cub3d, char *terminate);
char	*remove_trailing(char *str, char *c);

//cleaning.c
void	clean_all(t_data *cub3d);
void	clean_mapheader(t_map *map_info);
void	clean_mapcontent(t_map *map_info);
void	clean_textures(t_data *cub3d);

#endif
