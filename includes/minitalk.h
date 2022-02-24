/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 18:52:09 by ttomori           #+#    #+#             */
/*   Updated: 2022/02/24 23:44:38 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include "../ft_printf/includes/ft_printf.h"

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

#endif
