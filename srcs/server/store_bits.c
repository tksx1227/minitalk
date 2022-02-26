/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 02:49:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:49:36 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	store_bits(int bit, pid_t client_pid)
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
