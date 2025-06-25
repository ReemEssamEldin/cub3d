/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:27:29 by hsetyamu          #+#    #+#             */
/*   Updated: 2025/06/25 12:17:27 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef BONUS
#  define BONUS 0
# endif

# define WID 1280
# define HEI 720
# define BLOCK 10
# define PI 3.14159265359

# define MOVE_SPEED 0.7
# define ANGLE_SPEED 0.03
# define COLBUF_FACTOR 0.1

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

# define WHI		0xFFFFFF  // White
# define BLA		0x000000  // Black
# define RED		0xFF0000  // Red
# define GRE		0x00FF00  // Green
# define BLU		0x0000FF  // Blue
# define YEL		0xFFFF00  // Yellow
# define CYA		0x00FFFF  // Cyan
# define MAG		0xFF00FF  // Magenta
# define ORA		0xFFA500  // Orange
# define PUR		0x800080  // Purple
# define GRY		0x808080  // Grey
# define DGRY	0x404040  // Dark Grey
# define LGRY	0xC0C0C0  // Light Grey
# define BRO		0x8B4513  // Brown
# define PIN		0xFFC0CB  // Pink
# define GOL		0xFFD700  // Gold
# define SIL		0xC0C0C0  // Silver
# define TEA		0x008080  // Teal
# define NAV		0x000080  // Navy Blue
# define SLATE_GREY   0x708090  // Slate Grey
# define DIM_GREY     0x696969  // Dim Grey
# define LIGHT_SLATE  0x778899  // Light Slate Grey
# define GAINSBORO    0xDCDCDC  // Gainsboro
# define DARK_SLATE   0x2F4F4F  // Dark Slate Grey
# define CHARCOAL     0x36454F  // Charcoal
# define ASH_GREY     0xB2BEB5  // Ash Grey
# define PLATINUM     0xE5E4E2  // Platinum
# define SMOKE_GREY   0x738276  // Smoke Grey
# define CLOUD_GREY   0xB0C4DE  // Cloud Grey

#endif
