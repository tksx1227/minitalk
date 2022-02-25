/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:52:09 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/25 15:56:07 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include "../ft_printf/includes/ft_printf.h"

# define SETUP_SIGACTION_ERROR "Error: Setup sigaction is failed.\n"
# define INVALID_BIT_ERROR "Error: Received invalid bit data.\n"
# define INPUT_ARGUMENT_ERROR "Error: Input Error.\n"
# define USAGE_MESSAGE "Usage: client <PROCESS_ID> <MESSAGES>\n"
# define INVALID_PROCESS_ERROR "Error: Invalid Process ID.\n"
# define NOT_EXIST_PROCESS_ERROR "Error: Process %d is not exist.\n"
# define FAILED_SEND_SIGNAL_ERROR "Error: Failed to send signal to process %d.\n"
# define SUCCESSED_MESSAGE "[ Successed to send message. ]\n"
# define FAILED_MESSAGE "[ Failed to send message. ]\n"

typedef enum e_masks
{
	MASK_1BYTE = 0x80,
	MASK_2BYTE = 0xE0,
	MASK_3BYTE = 0xF0,
	MASK_4BYTE = 0xF8,
	MASK_5BYTE = 0xFC,
	MASK_6BYTE = 0xFE,
}	t_masks;

typedef enum e_prefix
{
	PREFIX_1BYTE = 0x00,
	PREFIX_2BYTE = 0xC0,
	PREFIX_3BYTE = 0xE0,
	PREFIX_4BYTE = 0xF0,
	PREFIX_5BYTE = 0xF8,
	PREFIX_6BYTE = 0xFC,
}	t_prefix;

void	setup_sigaction(void (*sig_handler)(int, siginfo_t *, void *));

#endif
