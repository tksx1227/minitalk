/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/18 01:35:54 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_char(pid_t pid, char c)
{
	int				bit;
	int				res;
	int				offset;
	unsigned char	uc;

	offset = 7;
	uc = (unsigned char)c;
	while (0 <= offset)
	{
		usleep(50);
		bit = uc & (0x01 << offset);
		if (bit == 0x00)
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
		{
			ft_printf("kill %d failed: no such process.\n", pid);
			exit(1);
		}
		offset--;
	}
}

void	ft_send_msg(pid_t pid, char *msg)
{
	size_t	i;

	i = 0;
	while (msg[i] != '\0')
	{
		ft_send_char(pid, msg[i]);
		i++;
	}
}
