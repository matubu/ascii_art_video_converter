/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <mberger-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:40:46 by mberger-          #+#    #+#             */
/*   Updated: 2022/12/11 21:35:27 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "video_buffer.h"

static inline t_video	load_error(const char *s)
{
	printf("\x1b[91mError\x1b[0m: %s\n", s);
	return ((t_video){
		.frames_cnt = 0,
		.frames = NULL
	});
}

static inline int	load_frame(
	int fd, t_frame *frame, t_u32 width, t_u32 height
)
{
	uint8_t	buf[4];
	t_u32	x;

	frame->len = 0;
	frame->buf = malloc(width * height * 21 + 42);
	if (frame->buf == NULL)
		return (-1);
	write_str(frame, "\x1b[");
	write_num(frame, height);
	write_str(frame, "A");
	while (height--)
	{
		x = width;
		while (x--)
		{
			read(fd, buf, 4);
			write_color(frame, buf);
			frame->buf[frame->len++] = buf[3];
		}
		frame->buf[frame->len++] = '\n';
	}
	return (0);
}

t_video	load_video(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	t_video		v;
	t_u32		cnt;
	t_u32		width;
	t_u32		height;

	read_u32(fd, &v.fps);
	read_u32(fd, &cnt);
	read_u32(fd, &width);
	read_u32(fd, &height);
	v.frames_cnt = -1;
	v.frames = malloc((cnt + 1) * sizeof(t_frame));
	if (fd < 0 || !v.frames)
		return (free(v.frames), load_error("couldn't load video"));
	while (++v.frames_cnt < cnt)
	{
		if (load_frame(fd, &v.frames[v.frames_cnt], width, height) == -1)
		{
			close(fd);
			free_video(&v);
			return (load_error("couldn't load video"));
		}
	}
	close(fd);
	return (v);
}

void	play_video(const t_video *video, int reverse)
{
	t_u32	i;

	write(1, "\ec", 2);
	if (reverse)
	{
		i = video->frames_cnt;
		while (i--)
		{
			write(1, video->frames[i].buf, video->frames[i].len);
			ft_usleep(1000000 / video->fps);
		}
	}
	else
	{
		i = 0;
		while (i < video->frames_cnt)
		{
			write(1, video->frames[i].buf, video->frames[i].len);
			ft_usleep(1000000 / video->fps);
			++i;
		}
	}
}

void	free_video(const t_video *video)
{
	t_u32	i;

	i = video->frames_cnt;
	while (i--)
		free(video->frames[i].buf);
	free(video->frames);
}
