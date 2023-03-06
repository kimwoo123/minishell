/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:39:27 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:04 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

int	ft_hexlen(unsigned long ptr)
{
	int	count;

	if (!ptr)
		return (1);
	count = 0;
	while (ptr)
	{
		ptr /= 16;
		count++;
	}
	return (count);
}

void	put_ulhex(unsigned long ptr, char *hex_base)
{
	if (ptr < 16)
		write(1, &hex_base[ptr], 1);
	else
	{
		put_ulhex(ptr / 16, hex_base);
		put_ulhex(ptr % 16, hex_base);
	}
}

void	putptr(unsigned long ptr)
{
	char	*hex_base;

	hex_base = "0123456789abcdef";
	write(1, "0x", 2);
	put_ulhex(ptr, hex_base);
}

void	print_p(unsigned long ptr, t_items *item_info)
{
	int		len;

	len = item_info->len;
	if (len < item_info->precision)
		len = item_info->precision;
	if (item_info->dot)
		item_info->zero = 0;
	if (item_info->minus)
	{
		fill_precision(item_info);
		putptr(ptr);
		fill_width(0, item_info->width - len);
	}
	else
	{
		fill_width(item_info->zero, item_info->width - len);
		fill_precision(item_info);
		putptr(ptr);
	}
}

int	convert_p(void *ptr, t_items *item_info)
{
	int	print_len;

	item_info->len = ft_hexlen((unsigned long)ptr) + 2;
	print_p((unsigned long)ptr, item_info);
	print_len = item_info->len;
	if (print_len < item_info->precision)
		print_len = item_info->precision;
	if (item_info->width > (print_len))
		return (item_info->width);
	return (print_len);
}
