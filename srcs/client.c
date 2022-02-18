/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/18 17:53:24 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_sigflg;

void	ft_send_char(pid_t pid, char c)
{
	int				bit;
	int				res;
	int				offset;
	unsigned char	uc;

	offset = 0;
	uc = (unsigned char)c;
	while (offset < 8)
	{
		usleep(500);
		bit = uc & (0x01 << (7 - offset));
		if (bit == 0x00)
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
		{
			ft_printf("Failed to send signal to process %d.\n", pid);
			exit(1);
		}
		offset++;
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

int	main(int ac, char **av)
{
	size_t	i;
	pid_t	pid;

	if (ac != 3)
	{
		ft_printf("Input Error!!\n");
		ft_printf("Usage: ./client <PROCESS_ID> <MESSAGES>\n");
		return (1);
	}
	i = 0;
	pid = 0;
	while (ft_isdigit(av[1][i]))
	{
		pid = 10 * pid + (av[1][i] - '0');
		i++;
	}
	ft_send_msg(pid, av[2]);
	return (0);
}
