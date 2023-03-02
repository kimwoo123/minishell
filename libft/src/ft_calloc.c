/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:10:09 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 16:51:16 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*addr;

	bytes = count * size;
	if (count != 0 && bytes / count != size)
		return (NULL);
	addr = malloc(bytes);
	if (addr == NULL)
		return (NULL);
	ft_bzero(addr, bytes);
	return (addr);
}
