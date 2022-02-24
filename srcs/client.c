/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/24 23:55:50 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static pid_t	parse_pid(char *s);
static void		sig_handler(int signum);
static void		send_char(pid_t pid, char c);
static void		send_msg(pid_t pid, char *msg);

volatile sig_atomic_t	g_sigflg;

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_printf("Error: Input Error.\n");
		ft_printf("Usage: client <PROCESS_ID> <MESSAGES>\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	pid = parse_pid(av[1]);
	if (pid < 0 || kill(pid, 0) != 0)
	{
		if (pid < 0)
			ft_printf("Error: Invalid Process ID.\n");
		else
			ft_printf("Error: Process %d is not exist.\n", pid);
		return (1);
	}
	send_msg(pid, av[2]);
	return (0);
}

static pid_t	parse_pid(char *s)
{
	int	idx;
	int	pid;

	idx = 0;
	pid = 0;
	while (s[idx] != '\0')
	{
		if (!ft_isdigit(s[idx]))
			return (-1);
		pid = pid * 10 + (s[idx] - '0');
		if (99999 < pid)
			return (-1);
		idx++;
	}
	return ((pid_t)pid);
}

static void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		g_sigflg = 1;
}

static void	send_char(pid_t pid, char c)
{
	int		res;
	int		offset;
	char	bit;

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
			ft_printf("Error: Failed to send signal to process %d.\n", pid);
			exit(1);
		}
		usleep(500);
	}
}

static void	send_msg(pid_t pid, char *msg)
{
	size_t	idx;

	idx = 0;
	g_sigflg = 0;
	while (1)
	{
		send_char(pid, msg[idx]);
		if (msg[idx] == '\0')
			break ;
		idx++;
	}
	if (!g_sigflg)
		usleep(100);
	if (g_sigflg)
		ft_printf("[ Successed to send message. ]\n");
	else
		ft_printf("[ Failed to send message. ]\n");
}
