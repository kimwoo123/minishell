/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:55:05 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:48:30 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf_bonus.h"

int	set_item(t_items *item_info, char c)
{
	if (is_specifier(c))
	{
		item_info->specifier = c;
		return (0);
	}
	else if (c == '-')
		item_info->minus = 1;
	else if (c == '+')
		item_info->plus = 1;
	else if (c == '#')
		item_info->sharp = 1;
	else if (c == '.')
		item_info->dot = 1;
	else if (c == ' ')
		item_info->space = 1;
	else if (item_info->dot && is_digit(c))
		item_info->precision = (item_info->precision * 10) + (c - '0');
	else if (!(item_info->width) && c == '0')
		item_info->zero = 1;
	else if (is_digit(c))
		item_info->width = (item_info->width * 10) + (c - '0');
	else
		return (0);
	return (1);
}

void	init_iteminfo(t_items *item_info)
{
	item_info->width = 0;
	item_info->space = 0;
	item_info->precision = 0;
	item_info->minus = 0;
	item_info->plus = 0;
	item_info->zero = 0;
	item_info->sharp = 0;
	item_info->dot = 0;
	item_info->len = 0;
	item_info->specifier = '\0';
}

int	convert_specifier(t_items *item_info, va_list ap)
{
	if (item_info->specifier == 'c')
		return (convert_c(va_arg(ap, int), item_info));
	else if (item_info->specifier == 's')
		return (convert_s(va_arg(ap, char *), item_info));
	else if (item_info->specifier == 'p')
		return (convert_p(va_arg(ap, void *), item_info));
	else if (item_info->specifier == 'u')
		return (convert_u(va_arg(ap, unsigned int), item_info));
	else if (item_info->specifier == 'X' || item_info->specifier == 'x')
		return (convert_x(va_arg(ap, unsigned int), item_info));
	else if (item_info->specifier == 'i' || item_info->specifier == 'd')
		return (convert_i(va_arg(ap, int), item_info));
	else if (item_info->specifier == '%')
		return (convert_c('%', item_info));
	return (0);
}

int	check_format(const char *string, va_list ap, int *total_len)
{
	int		index;
	t_items	item_info;

	index = 1;
	init_iteminfo(&item_info);
	while (set_item(&item_info, string[index]))
		index++;
	if (!is_specifier(string[index]))
		index--;
	*total_len += convert_specifier(&item_info, ap);
	return (index);
}

int	print_string(va_list ap, const char *string)
{
	int	total_len;

	total_len = 0;
	while (*string)
	{
		if (*string == '%')
			string += check_format(string, ap, &total_len);
		else
		{
			write(1, string, 1);
			total_len++;
		}
		string++;
	}
	return (total_len);
}
