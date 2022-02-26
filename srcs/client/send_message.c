/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 02:45:22 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:45:35 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_message(pid_t pid, char *msg)
{
	size_t	idx;

	idx = 0;
	g_is_successed = 0;
	while (1)
	{
		send_char(pid, msg[idx]);
		if (msg[idx] == '\0')
			break ;
		idx++;
	}
	if (!g_is_successed)
		usleep(500);
	if (g_is_successed)
		ft_dprintf(STDOUT_FILENO, "[ Successed to send message. ]\n");
	else
		ft_dprintf(STDOUT_FILENO, "[ Failed to send message. ]\n");
}
