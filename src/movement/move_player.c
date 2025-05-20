/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldahli <reldahli@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:51:41 by hsetya            #+#    #+#             */
/*   Updated: 2025/05/20 14:47:29 by reldahli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_player(t_player *player, t_data *cub3d);
void	move_down(t_player *player, t_data *cub3d);
void	move_up(t_player *player, t_data *cub3d);
void	move_right(t_player *player, t_data *cub3d);
void	move_left(t_player *player, t_data *cub3d);

void	move_player(t_player *player, t_data *cub3d)
{
	cub3d->move.speed = MOVE_SPEED;
	cub3d->move.angle_speed = ANGLE_SPEED;
	cub3d->move.collision_buffer = BLOCK * COLBUF_FACTOR;
	move_rotate(player, cub3d->move.angle_speed);
	cub3d->move.cos_angle = cos(player->angle);
	cub3d->move.sin_angle = sin(player->angle);
	if (player->key_down)
		move_down(player, cub3d);
	if (player->key_up)
		move_up(player, cub3d);
	if (player->key_right)
		move_right(player, cub3d);
	if (player->key_left)
		move_left(player, cub3d);
}

void	move_down(t_player *player, t_data *cub3d)
{
	if (cub3d->move.cos_angle > 0)
		cub3d->move.dir_x = 1;
	else
		cub3d->move.dir_x = -1;
	if (cub3d->move.sin_angle > 0)
		cub3d->move.dir_y = 1;
	else
		cub3d->move.dir_y = -1;
	try_move(player, cub3d->move.cos_angle * cub3d->move.speed,
		cub3d->move.sin_angle * cub3d->move.speed, cub3d);
}

void	move_up(t_player *player, t_data *cub3d)
{
	if (cub3d->move.cos_angle < 0)
		cub3d->move.dir_x = 1;
	else
		cub3d->move.dir_x = -1;
	if (cub3d->move.sin_angle < 0)
		cub3d->move.dir_y = 1;
	else
		cub3d->move.dir_y = -1;
	try_move(player, -cub3d->move.cos_angle * cub3d->move.speed,
		-cub3d->move.sin_angle * cub3d->move.speed, cub3d);
}

void	move_right(t_player *player, t_data *cub3d)
{
	if (cub3d->move.sin_angle > 0)
		cub3d->move.dir_x = 1;
	else
		cub3d->move.dir_x = -1;
	if (cub3d->move.cos_angle < 0)
		cub3d->move.dir_y = 1;
	else
		cub3d->move.dir_y = -1;
	try_move(player, cub3d->move.sin_angle * cub3d->move.speed,
		-cub3d->move.cos_angle * cub3d->move.speed, cub3d);
}

void	move_left(t_player *player, t_data *cub3d)
{
	if (cub3d->move.sin_angle < 0)
		cub3d->move.dir_x = 1;
	else
		cub3d->move.dir_x = -1;
	if (cub3d->move.cos_angle > 0)
		cub3d->move.dir_y = 1;
	else
		cub3d->move.dir_y = -1;
	try_move(player, -cub3d->move.sin_angle * cub3d->move.speed,
		cub3d->move.cos_angle * cub3d->move.speed, cub3d);
}
