/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:42 by reldahli          #+#    #+#             */
/*   Updated: 2025/05/09 14:32:53 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include "cub3d.h"

char	*detect_audioplayer(void);
void	play_audio(char *audio);
void	end_audio(void);
#endif
