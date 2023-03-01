/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:11:59 by chajung           #+#    #+#             */
/*   Updated: 2022/11/12 13:52:50 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*addr;
	int		trim1;
	int		trim2;

	trim1 = 0;
	trim2 = ft_strlen(s1);
	while (s1[trim1] && ft_strchr(set, s1[trim1]))
		trim1++;
	while (s1[trim2 - 1] && ft_strrchr(set, s1[trim2 - 1]) && trim2 != trim1)
		trim2--;
	if (trim2 > trim1)
	{
		addr = (char *)malloc(sizeof(char) * (trim2 - trim1 + 1));
		if (addr == NULL)
			return (NULL);
		ft_strlcpy(addr, &s1[trim1], trim2 - trim1 + 1);
	}
	else
		addr = ft_calloc(1, 1);
	return (addr);
}
