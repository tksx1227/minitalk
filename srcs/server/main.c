/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:40:04 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "server.h"

static void	setup_sigaction(void (*sig_handler)(int, siginfo_t *, void *));
static void	sig_handler(int signum, siginfo_t *info, void *context);
static void	store_bits(int bit, pid_t client_pid);
static void	send_signal_to_client(pid_t client_pid);

volatile sig_atomic_t	g_is_interrupted;

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_dprintf(STDOUT_FILENO, "PID: %d\n", pid);
	g_is_interrupted = 0;
	setup_sigaction(&sig_handler);
	while (1)
		pause();
	return (0);
}

static void	setup_sigaction(void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigemptyset(&sa.sa_mask) != 0 \
			|| sigaction(SIGUSR1, &sa, NULL) != 0 \
			|| sigaction(SIGUSR2, &sa, NULL) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error: Setup sigaction failed.\n");
		exit(1);
	}
}

static void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		if (client_pid != 0)
		{
			g_is_interrupted = 1;
		}
	}
	if (signum == SIGUSR1)
		store_bits(0, client_pid);
	else
		store_bits(1, client_pid);
}

static void	store_bits(int bit, pid_t client_pid)
{
	static size_t			offset;
	static unsigned char	buf[1024];

	if (g_is_interrupted)
	{
		buf[offset / CHAR_BIT] = 0;
		offset = 0;
		g_is_interrupted = 0;
	}
	buf[offset / CHAR_BIT] |= (bit << (offset % CHAR_BIT));
	offset++;
	if ((offset % CHAR_BIT) == 0)
	{
		if (buf[(offset / CHAR_BIT) - 1] == '\0' || 1000 < (offset / CHAR_BIT))
		{
			ft_dprintf(STDOUT_FILENO, "%s", buf);
			if (buf[(offset / CHAR_BIT) - 1] == '\0')
			{
				send_signal_to_client(client_pid);
			}
			offset = 0;
		}
		buf[offset / CHAR_BIT] = 0;
	}
}

static void	send_signal_to_client(pid_t client_pid)
{
	if (kill(client_pid, 0) != 0)
	{
		ft_dprintf(STDERR_FILENO, \
				"Error: Process %d does not exist.\n", client_pid);
	}
	else
	{
		if (kill(client_pid, SIGUSR1) != 0)
		{
			ft_dprintf(STDERR_FILENO, \
					"Error: Failed to send signal to process %d.\n", client_pid);
		}
	}
}
