/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:52:09 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/26 18:27:40 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include "../ft_printf/includes/ft_printf.h"

# define SETUP_SIGACTION_ERROR "Error: Setup sigaction failed.\n"
# define INVALID_BIT_ERROR "Error: Received invalid bit data.\n"
# define INPUT_ARGUMENT_ERROR "Error: Input Error.\n"
# define USAGE_MESSAGE "Usage: client <PROCESS_ID> <MESSAGES>\n"
# define INVALID_PROCESS_ERROR "Error: Invalid Process ID.\n"
# define NOT_EXIST_PROCESS_ERROR "Error: Process %d does not exist.\n"
# define FAILED_SEND_SIGNAL_ERROR "Error: Failed to send signal to process %d.\n"
# define SUCCESSED_MESSAGE "[ Successed to send message. ]\n"
# define FAILED_MESSAGE "[ Failed to send message. ]\n"

#endif
