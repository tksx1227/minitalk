/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 02:44:24 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:44:38 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_char(pid_t pid, unsigned char c)
{
	int				res;
	int				offset;
	unsigned char	bit;

	offset = 0;
	while (offset < CHAR_BIT)
	{
		bit = c & (1 << offset);
		offset++;
		if (bit == 0)
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
		{
			ft_dprintf(STDERR_FILENO, \
					"Error: Failed to send signal to process %d.\n", pid);
			exit(1);
		}
		usleep(100);
	}
}
