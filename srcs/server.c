/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/18 18:01:02 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	store_bits(int bit, pid_t client_pid)
{
	static int	i;
	static int	offset;
	static char	c;
	static char	buf[1024];

	c += bit << (7 - offset);
	offset++;
	if (8 <= offset)
	{
		buf[i++] = c;
		if (c == '\0' || 1000 <= i)
		{
			i = 0;
			ft_printf("%s", buf);
			if (kill(client_pid, SIGUSR1) != 0)
				ft_printf("Failed to send signal to process %d.\n", client_pid);
		}
		c = 0x00;
		offset = 0;
	}
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		store_bits(0x00, info->si_pid);
	else
		store_bits(0x01, info->si_pid);
}

int	main(void)
{
	return (0);
}
