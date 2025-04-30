/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:40:16 by reldahli          #+#    #+#             */
/*   Updated: 2025/04/30 18:10:21 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_map
{
	char		*no_tex;
	char		*so_tex;
	char		*we_tex;
	char		*ea_tex;

	char		*fl_col; //maybe array?
	char		*ce_col; //maybe array?
/* 	int			*fl_col;
	int			*ce_col; */
	char		**map;
	int			map_rows;
	int			map_cols;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	void		*img_ptr_mm; //minimap
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;

	t_player	player;
	t_map		map_info;
	t_texture	textures[4];
	//t_calcs		calculations;
}	t_data;

#endif
