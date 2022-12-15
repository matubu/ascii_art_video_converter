/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <mberger-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:40:50 by mberger-          #+#    #+#             */
/*   Updated: 2022/12/11 21:17:36 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIDEO_H
# define VIDEO_H

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <stdint.h>

# include "ft_usleep.h"

typedef uint32_t	t_u32;

typedef struct s_frame {
	t_u32	len;
	char	*buf;
}	t_frame;

typedef struct s_video {
	t_u32		fps;
	long		frames_cnt;
	t_frame		*frames;
}	t_video;

t_video	load_video(const char *filename);
void	play_video(const t_video *video, int reverse);
void	free_video(const t_video *video);

#endif
