/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:36:33 by wooseoki          #+#    #+#             */
/*   Updated: 2023/02/27 13:47:53 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/ft_printf_bonus.h"

int	convert_c(int c, t_items *item_info)
{
	char	temp;

	temp = (char)c;
	if (item_info->minus)
	{
		write(1, &temp, 1);
		fill_width(0, item_info->width - 1);
	}
	else
	{
		fill_width(item_info->zero, item_info->width - 1);
		write(1, &temp, 1);
	}
	if (item_info->width)
		return (item_info->width);
	return (1);
}
