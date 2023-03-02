/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:56:32 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 14:08:13 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*addr;
	int		i;

	addr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (addr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		addr[i] = s1[i];
	addr[i] = '\0';
	return (addr);
}
