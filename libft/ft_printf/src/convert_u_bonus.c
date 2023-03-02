/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:41:30 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:14 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

int	ft_unumlen(unsigned int num)
{
	int	count;

	if (!num)
		return (1);
	count = 0;
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	ft_numlen(int num)
{
	int	count;

	if (!num)
		return (1);
	count = 0;
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

void	putunbr(unsigned int num)
{
	char	temp;

	temp = 0;
	if (num < 10)
	{
		temp = num + '0';
		write(1, &temp, 1);
	}
	else
	{
		putunbr(num / 10);
		putunbr(num % 10);
	}
}

void	print_u(unsigned int num, t_items *item_info)
{
	int	len;

	len = item_info->len;
	if (len < item_info->precision)
		len = item_info->precision;
	if (item_info->dot)
		item_info->zero = 0;
	if (item_info->minus)
	{
		fill_precision(item_info);
		if (item_info->len)
			putunbr(num);
		fill_width(0, item_info->width - len);
	}
	else
	{
		fill_width(item_info->zero, item_info->width - len);
		fill_precision(item_info);
		if (item_info->len)
			putunbr(num);
	}
}

int	convert_u(unsigned int num, t_items *item_info)
{
	int	print_len;

	item_info->len = ft_unumlen(num);
	print_len = item_info->len;
	if (!num && item_info->dot && !item_info->precision)
	{
		item_info->len = 0;
		print_len--;
	}
	print_u(num, item_info);
	if (print_len < item_info->precision)
		print_len = item_info->precision;
	if (item_info->width > print_len)
		return (item_info->width);
	return (print_len);
}
