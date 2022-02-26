/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_signal_to_client.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 02:49:58 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:50:08 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_signal_to_client(pid_t client_pid)
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
