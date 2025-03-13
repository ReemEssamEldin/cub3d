/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:20 by reldahli          #+#    #+#             */
/*   Updated: 2025/03/13 11:40:20 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

//utils.c
void	err_msg(t_data *cub3d, char *err_msg);
char	*remove_trailing(char *str, char *c);
void	clean_mapheader(t_map *map_info);
void	clean_mapcontent(t_map *map_info);
#endif
