/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberger- <mberger-@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:18:14 by mberger-          #+#    #+#             */
/*   Updated: 2022/12/12 08:50:51 by mberger-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_USLEEP_H
# define FT_USLEEP_H

# include <stdio.h>
# include <time.h>
# include <unistd.h>

static inline void	ft_nop(void)
{
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}

static inline void	ft_one_cpu_clock(void)
{
	int	i;

	i = 420;
	while (i--)
		ft_nop();
}

static inline void	ft_usleep(unsigned long long usec)
{
	usec *= CLOCKS_PER_SEC;
	usec /= 1000000;
	while (usec--)
		ft_one_cpu_clock();
}

#endif