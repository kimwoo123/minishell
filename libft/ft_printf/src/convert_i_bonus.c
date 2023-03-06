/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_i_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:44:11 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:47:59 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

char	check_sign(int num, t_items *item_info)
{
	if (num < 0)
		return ('-');
	if (item_info->plus)
		return ('+');
	if (item_info->space)
		return (' ');
	return ('\0');
}

void	putnbr(int num)
{
	char	temp;

	if (num == -2147483648)
		write(1, "2147483648", 10);
	else if (num < 0)
	{
		num *= -1;
		putnbr(num);
	}
	else if (num < 10)
	{
		temp = num + '0';
		write(1, &temp, 1);
	}
	else
	{
		putnbr(num / 10);
		putnbr(num % 10);
	}
}

void	add_sign(t_items *item_info, int len, char sign)
{
	if (item_info->zero)
	{
		if (sign)
			write(1, &sign, 1);
		fill_width(item_info->zero, len);
	}
	else
	{
		fill_width(item_info->zero, len);
		if (sign)
			write(1, &sign, 1);
	}
}

void	print_i(int num, t_items *item_info, char sign)
{
	int	len;

	len = item_info->len;
	if (len < item_info->precision)
		len = item_info->precision;
	if (sign)
		len++;
	if (item_info->dot)
		item_info->zero = 0;
	if (item_info->minus)
	{
		if (sign)
			write(1, &sign, 1);
		fill_precision(item_info);
		if (item_info->len)
			putnbr(num);
		fill_width(0, item_info->width - len);
	}
	else
	{
		add_sign(item_info, item_info->width - len, sign);
		fill_precision(item_info);
		if (item_info->len)
			putnbr(num);
	}
}

int	convert_i(int num, t_items *item_info)
{
	int		print_len;
	char	sign;

	sign = check_sign(num, item_info);
	item_info->len = ft_numlen(num);
	print_len = item_info->len;
	if (!num && item_info->dot && !item_info->precision)
	{	
		item_info->len = 0;
		print_len--;
	}
	print_i(num, item_info, sign);
	if (print_len < item_info->precision)
		print_len = item_info->precision;
	if (sign)
		print_len++;
	if (item_info->width > print_len)
		return (item_info->width);
	return (print_len);
}
