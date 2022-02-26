/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:52:09 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:46:05 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define MAX_PROCESS_ID 99999

# include "minitalk.h"

volatile sig_atomic_t	g_is_successed;

pid_t	parse_pid(char *s);
void	sig_handler(int signum);
void	send_char(pid_t pid, unsigned char c);
void	send_message(pid_t pid, char *msg);

#endif
