/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:51:04 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 03:50:15 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_dprintf(STDERR_FILENO, "Error: Input Error.\n");
		ft_dprintf(STDERR_FILENO, "Usage: client <PROCESS_ID> <MESSAGES>\n");
		return (1);
	}
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
	{
		ft_dprintf(STDERR_FILENO, "Error: Setup signal failed.\n");
		return (1);
	}
	pid = parse_pid(av[1]);
	if (pid <= 1 || kill(pid, 0) != 0)
	{
		if (pid <= 1)
			ft_dprintf(STDERR_FILENO, "Error: Invalid Process ID.\n");
		else
			ft_dprintf(STDERR_FILENO, \
					"Error: Process %d does not exist.\n", pid);
		return (1);
	}
	send_message(pid, av[2]);
	return (0);
}
