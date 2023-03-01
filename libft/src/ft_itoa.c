/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:21:46 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 14:04:19 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	array_size(int number)
{
	int	size;

	size = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number /= -10;
		size += 2;
	}
	while (number > 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}

static char	*int_to_ascii(char *array, int number, size_t i)
{
	array[i] = '\0';
	if (number == 0)
		array[0] = '0';
	if (number < 0)
	{
		array[0] = '-';
		array[--i] = (number % 10) * (-1) + '0';
		number /= -10;
	}
	while (number > 0)
	{
		array[--i] = number % 10 + '0';
		number /= 10;
	}
	return (array);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*array;

	size = array_size(n);
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (array == NULL)
		return (NULL);
	array = int_to_ascii(array, n, size);
	return (array);
}
