/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/22 11:21:50 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	setup_sigaction(void);
static void	sig_handler(int signum, siginfo_t *info, void *context);
static void	store_bits(int bit, pid_t client_pid);

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID: %d\n", pid);
	setup_sigaction();
	while (1)
		pause();
	return (0);
}

static void	setup_sigaction(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigemptyset(&sa.sa_mask) != 0 \
			|| sigaction(SIGUSR1, &sa, NULL) != 0 \
			|| sigaction(SIGUSR2, &sa, NULL) != 0)
	{
		ft_printf("ERROR: Setup sigaction is failed.");
		exit(1);
	}
}

static void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		store_bits(0, info->si_pid);
	else
		store_bits(1, info->si_pid);
}

static void	store_bits(int bit, pid_t client_pid)
{
	static int	i;
	static int	offset;
	static char	c;
	static char	buf[1024];

	offset++;
	c += bit << (CHAR_BIT - offset);
	if (CHAR_BIT <= offset)
	{
		buf[i++] = c;
		if (c == '\0' || 1000 <= i)
		{
			i = 0;
			ft_printf("%s", buf);
			if (kill(client_pid, SIGUSR1) != 0)
				ft_printf("Failed to send signal to process %d.\n", client_pid);
		}
		c = 0;
		offset = 0;
	}
}
