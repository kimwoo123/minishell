/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:29:31 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 18:49:47 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*addr;
	int		size;

	size = 0;
	if (ft_strlen(s) > start + len)
		size = len;
	else if (ft_strlen(s) > start)
		size = ft_strlen(s) - start;
	addr = (char *)malloc(sizeof(char) * size + 1);
	if (addr == NULL)
		return (NULL);
	i = 0;
	while (*s && i < len && (start + i) < ft_strlen(s))
	{
		addr[i] = s[start + i];
		i++;
	}
	addr[i] = '\0';
	return (addr);
}
