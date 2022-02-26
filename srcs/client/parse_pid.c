/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 02:43:00 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:43:23 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "client.h"

pid_t	parse_pid(char *s)
{
	int		pid;
	size_t	idx;

	idx = 0;
	pid = 0;
	while (s[idx] != '\0')
	{
		if (!ft_isdigit(s[idx]))
			return (-1);
		pid = pid * 10 + (s[idx] - '0');
		if (MAX_PROCESS_ID < pid)
			return (-1);
		idx++;
	}
	return ((pid_t)pid);
}
