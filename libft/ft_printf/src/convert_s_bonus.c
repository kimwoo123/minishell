/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:37:38 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:09 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (*str++)
		index++;
	return (index);
}

void	putstr(char *str, int len)
{
	while (len-- > 0)
		write(1, str++, 1);
}

void	print_s(char *str, t_items *item_info)
{
	int	len;

	len = item_info->len;
	if (item_info->dot && item_info->len > item_info->precision)
		len = item_info->precision;
	if (item_info->minus)
	{
		putstr(str, len);
		fill_width(0, item_info->width - len);
	}
	else
	{
		fill_width(item_info->zero, item_info->width - len);
		putstr(str, len);
	}
}

int	convert_s(char *str, t_items *item_info)
{
	int		print_len;
	char	*string;

	string = str;
	if (!str)
		string = "(null)";
	item_info->len = ft_strlen(string);
	print_len = item_info->len;
	print_s(string, item_info);
	if (item_info->dot && print_len > item_info->precision)
		print_len = item_info->precision;
	if (item_info->width > print_len)
		return (item_info->width);
	return (print_len);
}
