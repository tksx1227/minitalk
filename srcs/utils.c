/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:49:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/25 15:55:50 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	setup_sigaction(void (*sig_handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigemptyset(&sa.sa_mask) != 0 \
			|| sigaction(SIGUSR1, &sa, NULL) != 0 \
			|| sigaction(SIGUSR2, &sa, NULL) != 0)
	{
		ft_printf(SETUP_SIGACTION_ERROR);
		exit(1);
	}
}
