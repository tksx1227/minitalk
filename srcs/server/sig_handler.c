/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 02:48:55 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:49:05 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
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
