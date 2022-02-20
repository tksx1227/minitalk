/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/20 23:34:23 by ttomori          ###   ########.fr       */
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
		ft_printf("Input Error!!\n");
		ft_printf("Usage: client <PROCESS_ID> <MESSAGES>\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	pid = parse_pid(av[1]);
	if (pid < 0)
	{
		ft_printf("Invalid Process ID!!\n");
		return (1);
	}
	send_msg(pid, av[2]);
	return (0);
}

static pid_t	parse_pid(char *s)
{
	int		pid;
	size_t	i;

	i = 0;
	pid = 0;
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]) || 10 <= i)
			return (-1);
		if (INT_MAX / 10 < pid || INT_MAX - (s[i] - '0') < pid * 10)
			return (-1);
		pid = pid * 10 + (s[i] - '0');
		i++;
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
		bit = c & (1 << (CHAR_BIT - offset));
		offset++;
		if (bit == 0)
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

static void	send_msg(pid_t pid, char *msg)
{
	size_t	i;

	i = 0;
	g_sigflg = 0;
	while (1)
	{
		send_char(pid, msg[i]);
		if (msg[i] == '\0')
			break ;
		i++;
	}
	if (g_sigflg)
		ft_printf("[ Successed to send message. ]\n");
	else
		ft_printf("[ Failed to send message. ]\n");
}
