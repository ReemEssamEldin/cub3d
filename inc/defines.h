/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/05/20 13:47:40 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WID 1280
# define HEI 720
# define PI 3.14159265359
# define BLOCK 10
# define FOV (PI * 0.21)

# ifndef BONUS
#  define BONUS 0
# endif

# define AUDIO_FILE "assets/audio/horror-bg.wav"

# define ESC			0xff1b
//# define UP			0xff52
//# define DOWN			0xff54
# define LEFT			0xff51
# define RIGHT			0xff53
# define W				0x0077
# define A				0x0061
# define S				0x0073
# define D				0x0064
//# define Q			0x0071
//# define E			0x0065

#endif