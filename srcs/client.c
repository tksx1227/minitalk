/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/19 12:22:59 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int signum);
static void	ft_send_char(pid_t pid, char c);
static void	ft_send_msg(pid_t pid, char *msg);

volatile sig_atomic_t	g_sigflg;

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_printf("Input Error!!\n");
		ft_printf("Usage: client <PROCESS_ID> <MESSAGES>\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	pid = (pid_t)ft_atoi(av[1]);
	ft_send_msg(pid, av[2]);
	return (0);
}

static void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		g_sigflg = 1;
}

static void	ft_send_char(pid_t pid, char c)
{
	int		res;
	int		offset;
	char	bit;

	offset = 0;
	while (offset < 8)
	{
		bit = c & (0x01 << (7 - offset));
		offset++;
		if (bit == 0x00)
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
		{
			ft_printf("Failed to send signal to process %d.\n", pid);
			exit(1);
		}
		usleep(100);
	}
}

static void	ft_send_msg(pid_t pid, char *msg)
{
	size_t	i;

	i = 0;
	g_sigflg = 0;
	while (1)
	{
		ft_send_char(pid, msg[i]);
		if (msg[i] == '\0')
			break ;
		i++;
	}
	if (g_sigflg)
		ft_printf("[ Successed to send message. ]\n");
	else
		ft_printf("[ Failed to send message. ]\n");
}
