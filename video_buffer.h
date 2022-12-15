/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_buffer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <mberger-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:40:40 by mberger-          #+#    #+#             */
/*   Updated: 2022/12/11 18:40:41 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIDEO_BUFFER_H
# define VIDEO_BUFFER_H

# include "video.h"

static inline int	read_u32(int fd, uint32_t *n)
{
	uint8_t	buf[4];

	*n = 0;
	if (read(fd, buf, 4) != 4)
		return (0);
	*n = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
	return (1);
}

static inline void	write_str(t_frame *frame, char *s)
{
	while (*s)
		frame->buf[frame->len++] = *s++;
}

static inline void	write_num(t_frame *frame, uint8_t n)
{
	if (n >= 100)
		frame->buf[frame->len++] = '0' + ((n / 100) % 10);
	if (n >= 10)
		frame->buf[frame->len++] = '0' + ((n / 10) % 10);
	frame->buf[frame->len++] = '0' + (n % 10);
}

static inline void	write_color(t_frame *frame, uint8_t *color)
{
	write_str(frame, "\x1b[38;2;");
	write_num(frame, color[0]);
	write_str(frame, ";");
	write_num(frame, color[1]);
	write_str(frame, ";");
	write_num(frame, color[2]);
	write_str(frame, "m");
}

#endif