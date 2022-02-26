/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:29 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:50:31 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
