/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:39:26 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 14:08:44 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*addr;

	addr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (addr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		addr[i] = f(i, s[i]);
		i++;
	}
	addr[i] = '\0';
	return (addr);
}
