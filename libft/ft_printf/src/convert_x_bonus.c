/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_x_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:51:44 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:21 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

void	put_sharp(int sharp_flag, char specifier, unsigned int num)
{
	if (!sharp_flag || !num)
		return ;
	if (specifier == 'x')
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
}

void	puthex(unsigned int num, char *hex_base)
{
	if (num < 16)
		write(1, &hex_base[num], 1);
	else
	{
		puthex(num / 16, hex_base);
		puthex(num % 16, hex_base);
	}
}

void	print_x(unsigned int num, t_items *item_info, char *hex_base)
{
	int		len;

	len = item_info->len;
	if (len < item_info->precision)
		len = item_info->precision;
	if (num && item_info->sharp)
		len += 2;
	if (item_info->dot)
		item_info->zero = 0;
	if (item_info->minus)
	{
		put_sharp(item_info->sharp, item_info->specifier, num);
		fill_precision(item_info);
		puthex(num, hex_base);
		fill_width(0, item_info->width - len);
		return ;
	}
	if (!item_info->zero)
		fill_width(item_info->zero, item_info->width - len);
	put_sharp(item_info->sharp, item_info->specifier, num);
	if (item_info->zero)
		fill_width(item_info->zero, item_info->width - len);
	fill_precision(item_info);
	puthex(num, hex_base);
}

int	convert_x(unsigned int num, t_items *item_info)
{
	int		print_len;
	char	*hex_base;

	if (item_info->specifier == 'x')
		hex_base = "0123456789abcdef";
	else
		hex_base = "0123456789ABCDEF";
	item_info->len = ft_hexlen(num);
	print_len = item_info->len;
	if (!num && item_info->dot && !item_info->precision)
	{
		fill_width(0, item_info->width);
		print_len--;
	}
	else
		print_x(num, item_info, hex_base);
	if (print_len < item_info->precision)
		print_len = item_info->precision;
	if (num && item_info->sharp)
		print_len += 2;
	if (item_info->width > print_len)
		return (item_info->width);
	return (print_len);
}
