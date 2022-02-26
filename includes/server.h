/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:52:09 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/27 02:50:39 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

volatile sig_atomic_t	g_is_interrupted;

void	sig_handler(int signum, siginfo_t *info, void *context);
void	setup_sigaction(void (*handler)(int, siginfo_t *, void *));
void	store_bits(int bit, pid_t client_pid);
void	send_signal_to_client(pid_t client_pid);

#endif
