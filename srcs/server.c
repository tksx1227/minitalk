/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/24 23:56:18 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	setup_sigaction(void);
static void	sig_handler(int signum, siginfo_t *info, void *context);
static void	store_bits(int bit, pid_t client_pid);
static int	get_byte_size(char c);

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
		ft_printf("Error: Setup sigaction is failed.");
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
	static int	idx;
	static int	offset;
	static int	byte_size;
	static char	c;
	static char	buf[1024];

	c += bit << offset++;
	if (CHAR_BIT <= offset)
	{
		buf[idx++] = c;
		if (byte_size == 0)
			byte_size = get_byte_size(c);
		if (c == '\0' || (1000 <= idx && byte_size-- == 1))
		{
			ft_printf("%s", buf);
			ft_bzero(buf, idx);
			idx = 0;
			if (c == '\0')
				if (kill(client_pid, SIGUSR1) != 0)
					ft_printf("Error: Failed to send signal to process %d.\n", \
							client_pid);
		}
		c = 0;
		offset = 0;
	}
}

static int	get_byte_size(char c)
{
	int	byte_size;

	if ((c & (char)MASK_1BYTE) == (char)PREFIX_1BYTE)
		byte_size = 1;
	else if ((c & (char)MASK_2BYTE) == (char)PREFIX_2BYTE)
		byte_size = 2;
	else if ((c & (char)MASK_3BYTE) == (char)PREFIX_3BYTE)
		byte_size = 3;
	else if ((c & (char)MASK_4BYTE) == (char)PREFIX_4BYTE)
		byte_size = 4;
	else if ((c & (char)MASK_5BYTE) == (char)PREFIX_5BYTE)
		byte_size = 5;
	else if ((c & (char)MASK_6BYTE) == (char)PREFIX_6BYTE)
		byte_size = 6;
	else
	{
		ft_printf("Error: Received invalid bit data.\n");
		exit(1);
	}
	return (byte_size);
}
