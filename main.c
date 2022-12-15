/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <mberger-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:40:53 by mberger-          #+#    #+#             */
/*   Updated: 2022/12/11 21:35:48 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"

int	main(void)
{
	t_video	video;

	video = load_video("video.celine");
	system("ffplay video.mp4 -autoexit -nodisp &> /dev/null &");
	if (video.frames)
	{
		while (1)
		{
			play_video(&video, 0);
			play_video(&video, 1);
		}
	}
	free_video(&video);
}
