/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/26 17:15:08 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int signum, siginfo_t *info, void *context);
static void	store_bits(int bit, pid_t client_pid);
static void	send_signal_to_client(pid_t client_pid);

volatile sig_atomic_t	g_is_processing;

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	setup_sigaction(&sig_handler);
	g_is_processing = 0;
	while (1)
		pause();
	return (0);
}

static void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	client_pid;

	(void)context;
	if (g_is_processing)
	{
		if (client_pid != info->si_pid)
			return ;
	}
	else
	{
		g_is_processing = 1;
		client_pid = info->si_pid;
	}
	if (signum == SIGUSR1)
		store_bits(0, client_pid);
	else
		store_bits(1, client_pid);
}

static void	store_bits(int bit, pid_t client_pid)
{
	static int				idx;
	static int				offset;
	static unsigned char	buf[1024];

	buf[idx] |= (bit << offset++);
	if (CHAR_BIT <= offset)
	{
		idx++;
		if (buf[idx - 1] == '\0' || 1000 <= idx)
		{
			ft_printf("%s", buf);
			ft_bzero(buf, idx);
			if (buf[idx - 1] == '\0')
			{
				send_signal_to_client(client_pid);
				g_is_processing = 0;
			}
			idx = 0;
		}
		offset = 0;
	}
}

static void	send_signal_to_client(pid_t client_pid)
{
	if (kill(client_pid, 0) != 0)
	{
		ft_printf(NOT_EXIST_PROCESS_ERROR, client_pid);
	}
	else
	{
		if (kill(client_pid, SIGUSR1) != 0)
		{
			ft_printf(FAILED_SEND_SIGNAL_ERROR, client_pid);
		}
	}
}
