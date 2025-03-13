/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:59 by reldahli          #+#    #+#             */
/*   Updated: 2025/03/13 11:40:00 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "cub3d.h"

void		init_cub3d(t_data *cub3d);
void		init_mlx(t_data *cub3d);
void		init_player(t_player *player);
#endif
