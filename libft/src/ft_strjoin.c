/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:56:27 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 14:08:26 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*addr;

	addr = (char *)malloc(sizeof(char) \
		* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (addr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		addr[i++] = *s1++;
	while (*s2)
		addr[i++] = *s2++;
	addr[i] = '\0';
	return (addr);
}
