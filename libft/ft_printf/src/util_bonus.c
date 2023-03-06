/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:47:06 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:35 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

int	is_item(char c)
{
	char	*items;

	items = " #+-.0123456789";
	while (*items)
	{
		if (*items == c)
			return (1);
		items++;
	}
	return (0);
}

int	is_specifier(char c)
{
	char	*specifier;

	specifier = "cspdiuxX%";
	while (*specifier)
	{
		if (*specifier == c)
			return (1);
		specifier++;
	}
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	fill_precision(t_items *item_info)
{
	int	count;

	count = item_info->precision - item_info->len;
	while (count-- > 0)
		write(1, "0", 1);
}

void	fill_width(int zero_flag, int len)
{
	if (zero_flag)
	{
		while (len-- > 0)
			write(1, "0", 1);
	}
	else
	{
		while (len-- > 0)
			write(1, " ", 1);
	}
}
